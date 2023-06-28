#include "PrecompileHeader.h"
#include "UpgradeTowerButton.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "UpgradeTowerUI.h"
#include "BaseTower.h"
#include "PriceTag.h"
#include "PlayManager.h"

UpgradeTowerButton::UpgradeTowerButton()
{

}

UpgradeTowerButton::~UpgradeTowerButton()
{

}

std::shared_ptr<UpgradeTowerButton> UpgradeTowerButton::CreateButton(UpgradeTowerUI* _UI)
{
	std::weak_ptr<UpgradeTowerButton> ResultButton(_UI->GetLevel()->CreateActor<UpgradeTowerButton>());
	float4 UIPos = _UI->GetTransform()->GetWorldPosition();
	ResultButton.lock()->GetTransform()->SetWorldPosition({ UIPos .x, UIPos .y, 0});
	ResultButton.lock()->GetTransform()->SetParent(_UI->GetTransform());
	ResultButton.lock()->SetParentActor(_UI);
	ResultButton.lock()->SetEvent([ResultButton]()
		{
			UpgradeTowerUI* ParentUI = dynamic_cast<UpgradeTowerUI*>(ResultButton.lock()->GetParentActor());
			if (ParentUI->GetState() == BaseTowerUIState::Start || !PlayManager::MainPlayer->DoIHaveEnoughGold(ResultButton.lock()->Price))
			{
				return;
			}
			ParentUI->OffUI();
			ParentUI->GetParentTower()->ChangeTower(ResultButton.lock()->ReturnNextTowerEnum());
			PlayManager::MainPlayer->Gold -= ResultButton.lock()->Price;
		});
	return ResultButton.lock();
}

void UpgradeTowerButton::SetPrice(TowerEnum _UpgTower)
{
	TowerData LocData;
	LocData.SetData(_UpgTower);
	Price = LocData.BuildCost;
	AcPriceTag->SetPrice(Price);
}

void UpgradeTowerButton::Start()
{
	ContentsButton::Start();
	ButtonGlow = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::TowerUIButton);
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::TowerUIButton);
	GetTransform()->SetWorldScale(Scale);
	ReleaseTextureName = "main_icons_0005.png";
	HoverTextureName = "main_icons_0005.png";
	PressTextureName = "main_icons_0005.png";
	InvalidTextureName = "main_icons_disabled_0005.png";

	ButtonGlow->SetTexture("ButtonsGlow.png");
	ButtonGlow->GetTransform()->SetWorldScale(GlowScale);
	ButtonGlow->Off();

	AcPriceTag = GetLevel()->CreateActor<PriceTag>();
	AcPriceTag->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4{0, -30});
	AcPriceTag->GetTransform()->SetParent(GetTransform());
}

void UpgradeTowerButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
	SetPrice(ReturnNextTowerEnum());
	if (!PlayManager::MainPlayer->DoIHaveEnoughGold(Price) && InvalidTextureName != "")
	{
		SetInvalid();
	}
	else
	{
		AcPriceTag->SetColor(PriceTag::ValidFontColor);
	}

	if (State == ButtonState::Release)
	{
		if (ButtonGlow->IsUpdate())
		{
			ButtonGlow->Off();
		}
	}
	else
	{
		if (!ButtonGlow->IsUpdate())
		{
			ButtonGlow->On();
		}
	}
}

TowerData UpgradeTowerButton::ReturnNextTowerData()
{
	if (nullptr == GetParentActor())
	{
		MsgAssert("ParentUI가 nullptr입니다")
	}

	TowerData Data = dynamic_cast<UpgradeTowerUI*>(GetParentActor())->GetParentTower()->GetData();
	return Data.GetNextTowerData();
}

TowerEnum UpgradeTowerButton::ReturnNextTowerEnum()
{
	TowerData LocalData = ReturnNextTowerData();
	return static_cast<TowerEnum>(static_cast<int>(LocalData.TowerType) + LocalData.Level);
}

void UpgradeTowerButton::SetInvalid()
{
	Render->SetTexture(InvalidTextureName);
	AcPriceTag->SetColor(PriceTag::InvalidFontColor);
}
