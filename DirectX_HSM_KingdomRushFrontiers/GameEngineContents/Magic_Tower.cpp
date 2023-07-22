#include "PrecompileHeader.h"
#include "Magic_Tower.h"

#include <GameEngineBase\GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Magic_Shooter.h"
#include "BuildArea.h"
#include "TowerButton.h"
#include "UpgradeTowerUI.h"

const float4 Magic_Tower::Lv1ShooterLocalPos = { 1,47, -47 };
const float4 Magic_Tower::Lv2ShooterLocalPos = { 1,49, -49 };
const float4 Magic_Tower::Lv3ShooterLocalPos = { 1,54, -54 };
const float4 Magic_Tower::Lv4ShooterLocalPos = { 1,44, -34 };

Magic_Tower::Magic_Tower()
{

}

Magic_Tower::~Magic_Tower()
{

}

std::shared_ptr<Magic_Tower> Magic_Tower::CreateTower(GameEngineLevel* _Level, BuildArea* _BuildArea)
{
	std::shared_ptr<Magic_Tower> LocalAc = nullptr;
	LocalAc = _Level->CreateActor<Magic_Tower>();
	LocalAc->ParentArea = _BuildArea;
	LocalAc->GetTransform()->SetWorldPosition(_BuildArea->GetTransform()->GetWorldPosition());
	LocalAc->Shooter->SetTargetPos(LocalAc->TargetPos);
	LocalAc->Shooter->GetTransform()->SetParent(LocalAc->GetTransform());
	LocalAc->UpgradeButton = TowerButton::CreateButton(LocalAc.get());
	LocalAc->UpgradeButton->Off();
	LocalAc->UpgradeUI = UpgradeTowerUI::CreateUpgradeTowerUI(LocalAc.get());
	float4 Position = LocalAc->GetTransform()->GetWorldPosition();
	LocalAc->TowerRangeRender->GetTransform()->SetWorldPosition({ Position.x, Position.y, -1000.f });
	LocalAc->NextLvRangeRender->GetTransform()->SetWorldPosition({ Position.x, Position.y, -1000.f });
	return LocalAc;
}

void Magic_Tower::Start()
{
	BaseShootingTower::Start();
	Data.SetData(TowerEnum::MagicTower_Level1);
	
	TowerRenderer->CreateAnimation({ .AnimationName = "Construct", .SpriteName = "MagicTower_Construct",.FrameInter = 0.15f, .Loop = false});
	TowerRenderer->CreateAnimation({ .AnimationName = "1_Attack", .SpriteName = "MagicTower_Level1_Attack",.FrameInter = 0.15f, .Loop = false});
	TowerRenderer->CreateAnimation({ .AnimationName = "1_Idle", .SpriteName = "MagicTower_Level1_Idle", .Loop = false});
	TowerRenderer->CreateAnimation({ .AnimationName = "2_Attack", .SpriteName = "MagicTower_Level2_Attack",.FrameInter = 0.15f, .Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "2_Idle", .SpriteName = "MagicTower_Level2_Idle", .Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "3_Attack", .SpriteName = "MagicTower_Level3_Attack",.FrameInter = 0.15f, .Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "3_Idle", .SpriteName = "MagicTower_Level3_Idle", .Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "4_Attack", .SpriteName = "MagicTower_Level4_Attack",.FrameInter = 0.15f, .Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "4_Idle", .SpriteName = "MagicTower_Level4_Idle", .Loop = false });

	TowerRenderer->ChangeAnimation("Construct");
	TowerRenderer->GetTransform()->SetWorldScale(RenderScale);

	Shooter = GetLevel()->CreateActor<Magic_Shooter>();
	Shooter->GetTransform()->SetParent(GetTransform());
	Shooter->GetTransform()->SetLocalPosition(Lv1ShooterLocalPos);
	Shooter->SetParentTower(this);
	Shooter->Off();

	TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	TowerRangeRender->Off();
	NextLvRangeRender->GetTransform()->SetWorldScale({ Data.GetNextLvRange() * 2,Data.GetNextLvRange() * 2 });
	NextLvRangeRender->Off();
	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	RangeCol->Off();

	TauntSoundName[0] = "Mage_Ready.ogg";
	TauntSoundName[1] = "Mage_Taunt1.ogg";
	TauntSoundName[2] = "Mage_Taunt2.ogg";
	TauntSoundName[3] = "archmage_taunt_ready.ogg";
}

void Magic_Tower::Update(float _DeltaTime)
{
	if (Construct == ConstructState::Constructing)
	{
		Time += _DeltaTime;
		BuildBar->GetTransform()->SetWorldScale(float4::LerpClamp({ 0,8,1 }, BuildBarScale, Time));
		BuildBar->GetTransform()->SetLocalPosition(float4::LerpClamp({ -27,50 }, { 0,50 }, Time));

		if (Time >= 1.f)
		{
			Time = 100;
			Construct = ConstructState::Complete;
			BuildBar->Off();
			BuildBarBg->Off();

			Shooter->On();
			RangeCol->On();
			UpgradeButton->On();
			TowerRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Idle");

			PlayTowerCommandSound(TauntSoundName[GameEngineRandom::MainRandom.RandomInt(0, 2)]);
		}
	}
	else
	{
		BaseShootingTower::Update(_DeltaTime);
		if (GameEngineInput::IsUp("M"))
		{
			ChangeTower(TowerEnum::MagicTower_Level4);
		}
		if (IsThereTarget())
		{
			Time += _DeltaTime;
			if (Time >= Data.FireRate)
			{
				Time = 0;
				MagicAttack();
			}
		}
		else
		{
			Shooter->StateValue = ShooterState::Idle;
			TowerRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Idle");
		}
	}
}

void Magic_Tower::ChangeTower(TowerEnum _Tower)
{
	Data.SetData(_Tower);
	if (TowerEnum::MagicTower != Data.TowerType)
	{
		return;
	}
	ChangeTowerRender(Data.Level);
	ChangeShooter(Data.Level);
	PlayTauntSound(Data.Level);
}

void Magic_Tower::ChangeTowerRender(int _TowerLevel)
{
	TowerRenderer->ChangeAnimation(std::to_string(_TowerLevel) + "_Idle");
	TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	if (Data.Level < 4)
	{
		NextLvRangeRender->GetTransform()->SetWorldScale({ Data.GetNextLvRange() * 2,Data.GetNextLvRange() * 2 });
	}
	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
}

void Magic_Tower::ChangeShooter(int _TowerLevel)
{
	Shooter->ChangeShooterRenderer(_TowerLevel);
	switch (_TowerLevel)
	{
	case 1:
		Shooter->GetTransform()->SetLocalPosition(Lv1ShooterLocalPos);
		break;
	case 2:
		Shooter->GetTransform()->SetLocalPosition(Lv2ShooterLocalPos);
		break;
	case 3:
		Shooter->GetTransform()->SetLocalPosition(Lv3ShooterLocalPos);
		break;
	case 4:
		Shooter->GetTransform()->SetLocalPosition(Lv4ShooterLocalPos);
		break;
	default:
		break;
	}
}

void Magic_Tower::MagicAttack()
{
	Shooter->StateValue = ShooterState::Attack;
	TowerRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Attack");
}
