#include "PrecompileHeader.h"
#include "Magic_Tower.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Magic_Shooter.h"

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
	LocalAc->ActorPos = _BuildPos;
	LocalAc->GetTransform()->SetWorldPosition(LocalAc->ActorPos);
	LocalAc->Shooter->SetTargetPos(LocalAc->TargetPos);
	LocalAc->Shooter->GetTransform()->SetParent(LocalAc->GetTransform());
	return LocalAc;
}

void Magic_Tower::Start()
{
	BaseShootingTower::Start();
	Data.SetData(TowerEnum::MagicTower_Level1);
	
	TowerRenderer->CreateAnimation({ .AnimationName = "1_Attack", .SpriteName = "MagicTower_Level1_Attack", .Loop = false});
	TowerRenderer->CreateAnimation({ .AnimationName = "1_Idle", .SpriteName = "MagicTower_Level1_Idle", .Loop = false});
	TowerRenderer->CreateAnimation({ .AnimationName = "2_Attack", .SpriteName = "MagicTower_Level2_Attack", .Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "2_Idle", .SpriteName = "MagicTower_Level2_Idle", .Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "3_Attack", .SpriteName = "MagicTower_Level3_Attack", .Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "3_Idle", .SpriteName = "MagicTower_Level3_Idle", .Loop = false });

	TowerRenderer->ChangeAnimation("1_Idle");
	TowerRenderer->GetTransform()->SetWorldScale(RenderScale);

	Shooter = GetLevel()->CreateActor<Magic_Shooter>();
	Shooter->GetTransform()->SetParent(GetTransform());
	Shooter->GetTransform()->SetLocalPosition(float4::Zero);
	Shooter->SetTowerData(&Data);

	//TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
}

void Magic_Tower::Update(float _DeltaTime)
{
	BaseShootingTower::Update(_DeltaTime);

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
	}
}

void Magic_Tower::MagicAttack()
{
	Shooter->StateValue = ShooterState::Attack;
}
