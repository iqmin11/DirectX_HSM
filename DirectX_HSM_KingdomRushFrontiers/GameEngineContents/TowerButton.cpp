#include "PrecompileHeader.h"
#include "TowerButton.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BaseTower.h"
#include "UpgradeTowerUI.h"
#include "PlayStageLevel.h"

TowerButton::TowerButton()
{

}

TowerButton::~TowerButton()
{

}

std::shared_ptr<TowerButton> TowerButton::CreateButton(BaseTower* _ParentTower)
{
	std::shared_ptr<TowerButton> ResultTowerButton = _ParentTower->GetLevel()->CreateActor<TowerButton>();
	float4 ParentPos = _ParentTower->GetTransform()->GetWorldPosition();
	ResultTowerButton->GetTransform()->SetWorldPosition({ ParentPos.x, ParentPos.y, 0.f });
	ResultTowerButton->SetParentActor(_ParentTower);
	ResultTowerButton->SetEvent(
		[_ParentTower]()
		{
			_ParentTower->UpgradeUI->OnUI();
		});
	return ResultTowerButton;
}

void TowerButton::Start()
{
	ContentsButton::Start();
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::TowerButton);
	GetTransform()->SetWorldScale(Scale);
	ReleaseTextureName = "InvisibleTexture.png";
	HoverTextureName = "InvisibleTexture.png";
	PressTextureName = "InvisibleTexture.png";

	UpSound = "Sound_GUIOpenTowerMenu.ogg";
	HoverSound = "Sound_GUIMouseOverTowerIcon.ogg";
}

void TowerButton::Update(float _DeltaTime)
{
	if (GetLevel()->DynamicThis<PlayStageLevel>()->IsPause)
	{
		return;
	}

	ContentsButton::Update(_DeltaTime);
}
