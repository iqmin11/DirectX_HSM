#include "PrecompileHeader.h"
#include "Ranged_Tower.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Ranged_Shooter.h"
#include "BuildArea.h"
#include "TowerButton.h"
#include "UpgradeTowerUI.h"

const float4 Ranged_Tower::Lv1Shooter0LocalPos = { 14,47, -47 };
const float4 Ranged_Tower::Lv1Shooter1LocalPos = { -10,47, -47 };
const float4 Ranged_Tower::Lv2Shooter0LocalPos = { 14,49, -49 };;
const float4 Ranged_Tower::Lv2Shooter1LocalPos = { -10,49, -49 };
const float4 Ranged_Tower::Lv3Shooter0LocalPos = { 14,54, -54 };
const float4 Ranged_Tower::Lv3Shooter1LocalPos = { -10,54, -54 };
const float4 Ranged_Tower::Lv4Shooter0LocalPos = { 14,56, -56 };
const float4 Ranged_Tower::Lv4Shooter1LocalPos = { -10,56, -56 };

Ranged_Tower::Ranged_Tower()
{

}

Ranged_Tower::~Ranged_Tower()
{

}

std::shared_ptr<Ranged_Tower> Ranged_Tower::CreateTower(GameEngineLevel* _Level, BuildArea* _BuildArea)
{
	std::shared_ptr<Ranged_Tower> LocalAc = nullptr;
	LocalAc = _Level->CreateActor<Ranged_Tower>();
	LocalAc->ParentArea = _BuildArea;
	LocalAc->GetTransform()->SetWorldPosition(_BuildArea->GetTransform()->GetWorldPosition());
	LocalAc->Shooter0->SetTargetPos(LocalAc->TargetPos);
	LocalAc->Shooter1->SetTargetPos(LocalAc->TargetPos);
	LocalAc->Shooter0->GetTransform()->SetParent(LocalAc->GetTransform());
	LocalAc->Shooter1->GetTransform()->SetParent(LocalAc->GetTransform());
	LocalAc->UpgradeButton = TowerButton::CreateButton(LocalAc.get());
	LocalAc->UpgradeButton->Off();
	LocalAc->UpgradeUI = UpgradeTowerUI::CreateUpgradeTowerUI(LocalAc.get());
	float4 Position = LocalAc->GetTransform()->GetWorldPosition();
	LocalAc->TowerRangeRender->GetTransform()->SetWorldPosition({ Position.x, Position.y, -1000.f });
	LocalAc->NextLvRangeRender->GetTransform()->SetWorldPosition({ Position.x, Position.y, -1000.f });
	return LocalAc;
}

void Ranged_Tower::ChangeTower(TowerEnum _Tower)
{
	Data.SetData(_Tower);
	if (TowerEnum::RangedTower != Data.TowerType)
	{
		return;
	}
	ChangeTowerRender(Data.Level);
	ChangeShooter(Data.Level);
	PlayTauntSound(Data.Level);
}

void Ranged_Tower::ChangeTowerRender(int _TowerLevel)
{
	TowerRenderer->SetTexture("archer_tower_000" + std::to_string(_TowerLevel) + ".png");
	TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	if (Data.Level < 4)
	{
		NextLvRangeRender->GetTransform()->SetWorldScale({ Data.GetNextLvRange() * 2,Data.GetNextLvRange() * 2 });
	}
	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
}

void Ranged_Tower::ChangeShooter(int _TowerLevel)
{
	Shooter0->ChangeShooterRenderer(_TowerLevel);
	Shooter1->ChangeShooterRenderer(_TowerLevel);
	switch (_TowerLevel)
	{
	case 1:
		Shooter0->GetTransform()->SetLocalPosition(Lv1Shooter0LocalPos);
		Shooter1->GetTransform()->SetLocalPosition(Lv1Shooter1LocalPos);
		break;
	case 2:
		Shooter0->GetTransform()->SetLocalPosition(Lv2Shooter0LocalPos);
		Shooter1->GetTransform()->SetLocalPosition(Lv2Shooter1LocalPos);
		break;
	case 3:
		Shooter0->GetTransform()->SetLocalPosition(Lv3Shooter0LocalPos);
		Shooter1->GetTransform()->SetLocalPosition(Lv3Shooter1LocalPos);
		break;
	case 4:
		Shooter0->GetTransform()->SetLocalPosition(Lv4Shooter0LocalPos);
		Shooter1->GetTransform()->SetLocalPosition(Lv4Shooter1LocalPos);
		break;
	default:
		break;
	}
}

void Ranged_Tower::RangerAttack()
{
	if (AttackOrder)
	{
		Shooter0->StateValue = ShooterState::Attack;
		Shooter1->StateValue = ShooterState::Idle;
	}
	else
	{
		Shooter0->StateValue = ShooterState::Idle;
		Shooter1->StateValue = ShooterState::Attack;
	}
	AttackOrder = !AttackOrder;
}


void Ranged_Tower::Start()
{
	BaseShootingTower::Start();

	Data.SetData(TowerEnum::RangedTower_Level1);

	TowerRenderer->SetTexture("tower_constructing_0004.png");
	TowerRenderer->GetTransform()->SetWorldScale(RenderScale);

	Shooter0 = GetLevel()->CreateActor<Ranged_Shooter>();
	Shooter0->GetTransform()->SetParent(GetTransform());
	Shooter0->GetTransform()->SetLocalPosition(Lv1Shooter0LocalPos);
	//Shooter0->SetTowerData(&Data);
	Shooter0->SetParentTower(this);
	Shooter0->Off();
	Shooter1 = GetLevel()->CreateActor<Ranged_Shooter>();
	Shooter1->GetTransform()->SetParent(GetTransform());
	Shooter1->GetTransform()->SetLocalPosition(Lv1Shooter1LocalPos);
	//Shooter1->SetTowerData(&Data);
	Shooter1->SetParentTower(this);
	Shooter1->Off();

	TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	TowerRangeRender->Off();
	NextLvRangeRender->GetTransform()->SetWorldScale({ Data.GetNextLvRange() * 2,Data.GetNextLvRange() * 2 });
	NextLvRangeRender->Off();
	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	RangeCol->Off();
	//Attack = std::bind(&Ranged_Tower::RangerAttack, this);

	Lv1TauntSoundName = "Archer_Ready.ogg";
	Lv2TauntSoundName = "Archer_Taunt1.ogg";
	Lv3TauntSoundName = "Archer_Taunt2.ogg";
	Lv4TauntSoundName = "crossbow_taunt_ready.ogg";
}

void Ranged_Tower::Update(float _DeltaTime)
{
	if (Construct == ConstructState::Constructing)
	{
		Time += _DeltaTime;
		BuildBar->GetTransform()->SetWorldScale(float4::LerpClamp({0,8,1}, BuildBarScale, Time));
		BuildBar->GetTransform()->SetLocalPosition(float4::LerpClamp({-27,50}, {0,50}, Time));

		if (Time >= 1.f)
		{
			Time = 100;
			Construct = ConstructState::Complete;
			BuildBar->Off();
			BuildBarBg->Off();

			TowerRenderer->SetTexture("archer_tower_0001.png");
			Shooter0->On();
			Shooter1->On();
			RangeCol->On();
			UpgradeButton->On();

			PlayTowerCommandSound(Lv1TauntSoundName);
		}
	}
	else
	{
		BaseShootingTower::Update(_DeltaTime);
		if (GameEngineInput::IsUp("M"))
		{
			ChangeTower(TowerEnum::RangedTower_Level4);
		}
		if (IsThereTarget())
		{
			Time += _DeltaTime;
			if (Time >= Data.FireRate)
			{
				Time = 0;
				RangerAttack();
			}
		}
	}
}


