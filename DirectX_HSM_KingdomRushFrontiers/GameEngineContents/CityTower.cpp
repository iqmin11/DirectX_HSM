#include "PrecompileHeader.h"
#include "CityTower.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore\GameEngineSpriteRenderer.h>
#include <GameEngineCore\GameEngineCollision.h>
#include "Ranged_Shooter.h"
#include <GameEngineCore\GameEngineUIRenderer.h>

CityTower::CityTower()
{

}

CityTower::~CityTower()
{

}

std::shared_ptr<CityTower> CityTower::CreateTower(GameEngineActor* _Parent, const float4& _Pos)
{
	std::shared_ptr<CityTower> LocalAc = nullptr;
	LocalAc = _Parent->GetLevel()->CreateActor<CityTower>();
	LocalAc->GetTransform()->SetParent(_Parent->GetTransform());
	LocalAc->GetTransform()->SetWorldPosition(_Pos);
	LocalAc->Shooter->SetTargetPos(LocalAc->TargetPos);
	LocalAc->Shooter->GetTransform()->SetParent(LocalAc->GetTransform());
	return LocalAc;
}

void CityTower::Start()
{
	BaseShootingTower::Start();

	Construct = ConstructState::Complete;
	Data.SetData(TowerEnum::RangedTower_CityTower);

	TowerRenderer->SetTexture("city_tower.png");
	TowerRenderer->GetTransform()->SetWorldScale(RenderScale);

	Shooter = GetLevel()->CreateActor<Ranged_Shooter>();
	Shooter->GetTransform()->SetParent(GetTransform());
	Shooter->GetTransform()->SetLocalPosition({ 0,54, -54 });
	Shooter->SetParentTower(this);
	Shooter->ChangeBaseShooterAnimation("0_Idle_Down");

	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });

	BuildBarBg->Off();
	BuildBar->Off();
	TowerAreaRenderer->Off();
}

void CityTower::Update(float _DeltaTime)
{
	BaseShootingTower::Update(_DeltaTime);
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

void CityTower::RangerAttack()
{
	Shooter->StateValue = ShooterState::Attack;
}
