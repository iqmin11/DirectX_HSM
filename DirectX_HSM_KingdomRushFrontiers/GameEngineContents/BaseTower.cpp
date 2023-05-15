#include "PrecompileHeader.h"
#include "BaseTower.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "BaseShooter.h"

BaseTower::BaseTower()
{

}

BaseTower::~BaseTower()
{

}

std::shared_ptr<BaseTower> BaseTower::CreateTower(GameEngineLevel* _Level,const float4& _BuildPos)
{
	std::shared_ptr<BaseTower> LocalAc = nullptr;
	LocalAc = _Level->CreateActor<BaseTower>();
	LocalAc->ActorPos = _BuildPos;
	LocalAc->GetTransform()->SetWorldPosition(LocalAc->ActorPos);
	LocalAc->Shooter0->SetParentPos(LocalAc->GetTransform()->GetWorldPosition());
	LocalAc->Shooter1->SetParentPos(LocalAc->GetTransform()->GetWorldPosition());
	return LocalAc;
}

void BaseTower::Start()
{
	GetTransform()->SetWorldPosition(ActorPos);
	TowerRenderer = CreateComponent<GameEngineSpriteRenderer>();
	TowerRenderer->SetTexture("archer_tower_0001.png");
	TowerRenderer->GetTransform()->SetWorldScale(RenderScale);

	TowerRangeRender = CreateComponent<GameEngineSpriteRenderer>();
	TowerRangeRender->SetTexture("range_circle.png");
	TowerRangeRender->GetTransform()->SetWorldScale({ TowerRange * 2,TowerRange * 2 });

	Shooter0 = GetLevel()->CreateActor<BaseShooter>();
	Shooter0->GetTransform()->SetParent(GetTransform());
	Shooter0->GetTransform()->SetLocalPosition({14,31});
	Shooter0->SetRange(TowerRange);
	Shooter1 = GetLevel()->CreateActor<BaseShooter>();
	Shooter1->GetTransform()->SetParent(GetTransform());
	Shooter1->GetTransform()->SetLocalPosition({ -10,31 });
	Shooter1->SetRange(TowerRange);
}

void BaseTower::Update(float _DeltaTime)
{

}


