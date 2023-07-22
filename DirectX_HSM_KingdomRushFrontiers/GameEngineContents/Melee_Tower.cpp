#include "PrecompileHeader.h"
#include "Melee_Tower.h"

#include <GameEngineBase\GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "Melee_RallyPoint.h"
#include "BuildArea.h"
#include "TowerButton.h"
#include "UpgradeTowerUI_ex.h"
#include "RallyButton.h"
#include "MousePointer.h"
#include "PlayStageLevel.h"
#include "DeciedRallyPointEffect.h"

Melee_Tower::Melee_Tower()
{

}

Melee_Tower::~Melee_Tower()
{

}

std::shared_ptr<Melee_Tower> Melee_Tower::CreateTower(GameEngineLevel* _Level, BuildArea* _BuildArea)
{
	std::shared_ptr<Melee_Tower> LocalAc = nullptr;
	LocalAc = _Level->CreateActor<Melee_Tower>();
	LocalAc->ParentArea = _BuildArea;
	LocalAc->GetTransform()->SetWorldPosition(_BuildArea->GetTransform()->GetWorldPosition());
	LocalAc->UpgradeButton = TowerButton::CreateButton(LocalAc.get());
	LocalAc->UpgradeButton->Off();
	LocalAc->UpgradeUI = UpgradeTowerUI_ex::CreateUpgradeTowerUI(LocalAc.get());
	float4 Position = LocalAc->GetTransform()->GetWorldPosition();
	LocalAc->TowerRangeRender->GetTransform()->SetWorldPosition({ Position.x, Position.y, -1000.f });
	LocalAc->NextLvRangeRender->GetTransform()->SetWorldPosition({ Position.x, Position.y, -1000.f });
	return LocalAc;
}

void Melee_Tower::Start()
{
	BaseTower::Start();

	Data.SetData(TowerEnum::MeleeTower_Level1);

	TowerRangeRender->SetTexture("rally_circle.png");
	TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	TowerRangeRender->Off();
	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	NextLvRangeRender->SetTexture("rally_circle.png");
	NextLvRangeRender->GetTransform()->SetWorldScale({ Data.GetNextLvRange() * 2,Data.GetNextLvRange() * 2 });
	NextLvRangeRender->Off();
	TowerRenderer->SetTexture("tower_constructing_0002.png");
	TowerRenderer->GetTransform()->SetWorldScale(RenderScale);

	TauntSoundName[0] = "Barrack_Ready.ogg";
	TauntSoundName[1] = "Barrack_Taunt1.ogg";
	TauntSoundName[2] = "Barrack_Taunt2.ogg";
	TauntSoundName[3] = "assassin_taunt_ready.ogg";
}

void Melee_Tower::Update(float _DeltaTime)
{
	BaseTower::Update(_DeltaTime);
	if (Construct == ConstructState::Constructing)
	{
		Time += _DeltaTime;
		BuildBar->GetTransform()->SetWorldScale(float4::LerpClamp({ 0,8,1 }, BuildBarScale, Time));
		BuildBar->GetTransform()->SetLocalPosition(float4::LerpClamp({ -27,50 }, { 0,50 }, Time));

		if (Time >= 1.f)
		{
			Time = 0;
			Construct = ConstructState::Complete;
			BuildBar->Off();
			BuildBarBg->Off();

			TowerRenderer->SetTexture("tower_barracks_lvl1.png");
			UpgradeButton->On();

			AcRallyPoint = Melee_RallyPoint::CreateRallyPoint(GetLevel(), ParentArea->GetTransform()->GetWorldPosition(), 3);
			AcRallyPoint->GetTransform()->SetParent(GetTransform());
			AcRallyPoint->GetTransform()->SetWorldPosition(ParentArea->GetRallyPos());
			AcRallyPoint->SetTowerData(&Data);
			
			PlayTowerCommandSound(TauntSoundName[GameEngineRandom::MainRandom.RandomInt(0,2)]);
		}
	}
	else
	{
		if (GameEngineInput::IsUp("M"))
		{
			ChangeTower(TowerEnum::MeleeTower_Level4);
		}
		ButtonState RallyButtonState = UpgradeUI->DynamicThis<UpgradeTowerUI_ex>()->AcRallyButton->GetState();
		if (ButtonState::Release != RallyButtonState || SetRallyMod)
		{
			TowerRangeRender->On();
		}
		else
		{
			TowerRangeRender->Off();
		}
	}

	//if (SetRallyMod 
	//	&& GameEngineInput::IsUp("EngineMouseLeft"))
	//{
	//	SetRally();
	//}
}

void Melee_Tower::ChangeTower(TowerEnum _Tower)
{
	Data.SetData(_Tower);
	if (TowerEnum::MeleeTower != Data.TowerType)
	{
		return;
	}
	ChangeTowerRender(Data.Level);
	ChangeFighter(Data.Level);
	PlayTauntSound(Data.Level);
}

void Melee_Tower::ChangeTowerRender(int _TowerLevel)
{
	TowerRenderer->SetTexture("tower_barracks_lvl" + std::to_string(_TowerLevel) + ".png");
	TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	if (Data.Level < 4)
	{
		NextLvRangeRender->GetTransform()->SetWorldScale({ Data.GetNextLvRange() * 2,Data.GetNextLvRange() * 2 });
	}
	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
}

void Melee_Tower::ChangeFighter(int _TowerLevel)
{
	if (AcRallyPoint == nullptr)
	{
		MsgAssert("랠리포인트가 nullptr입니다")
	}
	AcRallyPoint->ChangeFighters(_TowerLevel);
}

void Melee_Tower::SetRally()
{
	if (!MousePointer::MainMouse->IsThereMouseOntheColMap()
		&& RangeCol->Collision(ColOrder::MousePointer, ColType::SPHERE2D, ColType::AABBBOX2D))
	{
		float4 Pos = MousePointer::GetMousePosRef();
		Pos = Pos + float4{ 0, 0, Pos.y, 0 };
		AcRallyPoint->SetRallyPos(Pos);
		SetRallyMod = false;
		DeciedRallyPointEffect::CreateRallyEffect(this, Pos);
	}
	else
	{
		SetRallyMod = false;
	}
}
