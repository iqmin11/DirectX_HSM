#include "PrecompileHeader.h"
#include "Ranged_Tower.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Ranged_Shooter.h"

Ranged_Tower::Ranged_Tower()
{

}

Ranged_Tower::~Ranged_Tower()
{

}

std::shared_ptr<Ranged_Tower> Ranged_Tower::CreateTower(GameEngineLevel* _Level, const float4& _BuildPos)
{
	std::shared_ptr<Ranged_Tower> LocalAc = nullptr;
	LocalAc = _Level->CreateActor<Ranged_Tower>();
	LocalAc->ActorPos = _BuildPos;
	LocalAc->GetTransform()->SetWorldPosition(LocalAc->ActorPos);
	LocalAc->Shooter0->SetTargetPos(LocalAc->TargetPos);
	LocalAc->Shooter1->SetTargetPos(LocalAc->TargetPos);
	return LocalAc;
}

void Ranged_Tower::ChangeTower(TowerEnum _Tower)
{
	if (0 > static_cast<int>(_Tower) || 3 <= static_cast<int>(_Tower))
	{
		return;
	}
	Data.SetData(_Tower);
	ChangeTowerRender(_Tower);
	ChangeShooter(_Tower);
}

void Ranged_Tower::ChangeTowerRender(TowerEnum _Tower)
{
	TowerRenderer->SetTexture("archer_tower_000" + std::to_string(static_cast<int>(_Tower) + 1) + ".png");
	TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
}

void Ranged_Tower::ChangeShooter(TowerEnum _Tower)
{
	Shooter0->ChangeShooterRenderer(_Tower);
	Shooter1->ChangeShooterRenderer(_Tower);
}

void Ranged_Tower::RangerAttack()
{
	if (AttackOrder)
	{
		Shooter0->Attack();
	}
	else
	{
		Shooter1->Attack();
	}
	AttackOrder = !AttackOrder;
}



void Ranged_Tower::Start()
{
	BaseTower::Start();

	Data.SetData(TowerEnum::RangedTower_Level1);

	TowerRenderer->SetTexture("archer_tower_0001.png");
	TowerRenderer->GetTransform()->SetWorldScale(RenderScale);

	Shooter0 = GetLevel()->CreateActor<Ranged_Shooter>();
	Shooter0->GetTransform()->SetParent(GetTransform());
	Shooter0->GetTransform()->SetLocalPosition({ 14,31 });
	Shooter0->SetTowerData(&Data);
	Shooter1 = GetLevel()->CreateActor<Ranged_Shooter>();
	Shooter1->GetTransform()->SetParent(GetTransform());
	Shooter1->GetTransform()->SetLocalPosition({ -10,31 });
	Shooter1->SetTowerData(&Data);

	TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });

	//Test
	TestTargetRender = CreateComponent<GameEngineSpriteRenderer>();
	TestTargetCol = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::Monster));
	TestTargetCol->GetTransform()->SetParent(TestTargetRender->GetTransform());
	TestTargetRender->GetTransform()->SetWorldScale({ 5,5 });
}

void Ranged_Tower::Update(float _DeltaTime)
{
	BaseTower::Update(_DeltaTime);

	if (GameEngineInput::IsUp("Space"))
	{
		ChangeTower(TowerEnum::RangedTower_Level2);
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

	//Test
	if (GameEngineInput::IsPress("LeftArrow"))
	{
		TargetPos += float4::Left;
	}

	if (GameEngineInput::IsPress("RightArrow"))
	{
		TargetPos += float4::Right;
	}

	if (GameEngineInput::IsPress("DownArrow"))
	{
		TargetPos += float4::Down;
	}

	if (GameEngineInput::IsPress("UpArrow"))
	{
		TargetPos += float4::Up;
	}

	TestTargetRender->GetTransform()->SetWorldPosition(TargetPos);
}


