#include "PrecompileHeader.h"
#include "Magic_Tower.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Magic_Shooter.h"

const float4 Magic_Tower::Lv1ShooterLocalPos = { 1,47, -47 };
const float4 Magic_Tower::Lv2ShooterLocalPos = { 1,49, -49 };
const float4 Magic_Tower::Lv3ShooterLocalPos = { 1,54, -54 };
const float4 Magic_Tower::Lv4ShooterLocalPos = { 1,54, -54 };

Magic_Tower::Magic_Tower()
{

}

Magic_Tower::~Magic_Tower()
{

}

std::shared_ptr<Magic_Tower> Magic_Tower::CreateTower(GameEngineLevel* _Level, const float4& _BuildPos)
{
	std::shared_ptr<Magic_Tower> LocalAc = nullptr;
	LocalAc = _Level->CreateActor<Magic_Tower>();
	LocalAc->GetTransform()->SetWorldPosition(_BuildPos);
	LocalAc->Shooter->SetTargetPos(LocalAc->TargetPos);
	LocalAc->Shooter->GetTransform()->SetParent(LocalAc->GetTransform());
	return LocalAc;
}

void Magic_Tower::Start()
{
	BaseShootingTower::Start();
	Data.SetData(TowerEnum::MagicTower_Level1);
	
	TowerRenderer->CreateAnimation({ .AnimationName = "1_Attack", .SpriteName = "MagicTower_Level1_Attack",.FrameInter = 0.15f, .Loop = false});
	TowerRenderer->CreateAnimation({ .AnimationName = "1_Idle", .SpriteName = "MagicTower_Level1_Idle", .Loop = false});
	TowerRenderer->CreateAnimation({ .AnimationName = "2_Attack", .SpriteName = "MagicTower_Level2_Attack",.FrameInter = 0.15f, .Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "2_Idle", .SpriteName = "MagicTower_Level2_Idle", .Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "3_Attack", .SpriteName = "MagicTower_Level3_Attack",.FrameInter = 0.15f, .Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "3_Idle", .SpriteName = "MagicTower_Level3_Idle", .Loop = false });

	TowerRenderer->ChangeAnimation("1_Idle");
	TowerRenderer->GetTransform()->SetWorldScale(RenderScale);

	Shooter = GetLevel()->CreateActor<Magic_Shooter>();
	Shooter->GetTransform()->SetParent(GetTransform());
	Shooter->GetTransform()->SetLocalPosition(Lv1ShooterLocalPos);
	//Shooter->SetTowerData(&Data);
	Shooter->SetParentTower(this);

	//TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
}

void Magic_Tower::Update(float _DeltaTime)
{
	BaseShootingTower::Update(_DeltaTime);

	if (GameEngineInput::IsUp("M"))
	{
		ChangeTower(TowerEnum::MagicTower_Level3);
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

void Magic_Tower::ChangeTower(TowerEnum _Tower)
{
	Data.SetData(_Tower);
	if (TowerEnum::MagicTower != Data.TowerType)
	{
		return;
	}
	ChangeTowerRender(Data.Level);
	ChangeShooter(Data.Level);
}

void Magic_Tower::ChangeTowerRender(int _TowerLevel)
{
	TowerRenderer->ChangeAnimation(std::to_string(_TowerLevel) + "_Idle");
	//TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
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
