#include "PrecompileHeader.h"
#include "Ranged_Tower.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Ranged_Shooter.h"

const float4 Ranged_Tower::Lv1Shooter0LocalPos = { 14,47 };
const float4 Ranged_Tower::Lv1Shooter1LocalPos = { -10,47 };
const float4 Ranged_Tower::Lv2Shooter0LocalPos = { 14,49 };;
const float4 Ranged_Tower::Lv2Shooter1LocalPos = { -10,49 };
const float4 Ranged_Tower::Lv3Shooter0LocalPos = { 14,54 };
const float4 Ranged_Tower::Lv3Shooter1LocalPos = { -10,54 };
const float4 Ranged_Tower::Lv4Shooter0LocalPos = { 14,54 };
const float4 Ranged_Tower::Lv4Shooter1LocalPos = { -10,54 };

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
	LocalAc->Shooter0->GetTransform()->SetParent(LocalAc->GetTransform());
	LocalAc->Shooter1->GetTransform()->SetParent(LocalAc->GetTransform());
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
	//TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
}

void Ranged_Tower::ChangeShooter(TowerEnum _Tower)
{
	Shooter0->ChangeShooterRenderer(_Tower);
	Shooter1->ChangeShooterRenderer(_Tower);
	switch (_Tower)
	{
	case TowerEnum::RangedTower_Level1:
		Shooter0->GetTransform()->SetLocalPosition(Lv1Shooter0LocalPos);
		Shooter1->GetTransform()->SetLocalPosition(Lv1Shooter1LocalPos);
		break;
	case TowerEnum::RangedTower_Level2:
		Shooter0->GetTransform()->SetLocalPosition(Lv2Shooter0LocalPos);
		Shooter1->GetTransform()->SetLocalPosition(Lv2Shooter1LocalPos);
		break;
	case TowerEnum::RangedTower_Level3:
		Shooter0->GetTransform()->SetLocalPosition(Lv3Shooter0LocalPos);
		Shooter1->GetTransform()->SetLocalPosition(Lv3Shooter1LocalPos);
		break;
	case TowerEnum::RangedTower_Level4:
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
	BaseShootingTower::Start();

	Data.SetData(TowerEnum::RangedTower_Level1);

	TowerRenderer->SetTexture("archer_tower_0001.png");
	TowerRenderer->GetTransform()->SetWorldScale(RenderScale);

	Shooter0 = GetLevel()->CreateActor<Ranged_Shooter>();
	Shooter0->GetTransform()->SetParent(GetTransform());
	Shooter0->GetTransform()->SetLocalPosition({ 14,47 });
	Shooter0->SetTowerData(&Data);
	Shooter1 = GetLevel()->CreateActor<Ranged_Shooter>();
	Shooter1->GetTransform()->SetParent(GetTransform());
	Shooter1->GetTransform()->SetLocalPosition({ -10,47 });
	Shooter1->SetTowerData(&Data);

	//TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	Attack = std::bind(&Ranged_Tower::RangerAttack, this);
}

void Ranged_Tower::Update(float _DeltaTime)
{
	BaseShootingTower::Update(_DeltaTime);
	if (GameEngineInput::IsUp("Space"))
	{
		ChangeTower(TowerEnum::RangedTower_Level3);
	}
}


