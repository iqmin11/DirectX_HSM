#include "PrecompileHeader.h"
#include "Ranged_Tower.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
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
	LocalAc->Shooter0->SetParentPos(LocalAc->GetTransform()->GetWorldPosition());
	LocalAc->Shooter1->SetParentPos(LocalAc->GetTransform()->GetWorldPosition());
	return LocalAc;
}

void Ranged_Tower::Start()
{
	BaseTower::Start();
	TowerRenderer->SetTexture("archer_tower_0001.png");
	TowerRenderer->GetTransform()->SetWorldScale(RenderScale);

	Shooter0 = GetLevel()->CreateActor<Ranged_Shooter>();
	Shooter0->GetTransform()->SetParent(GetTransform());
	Shooter0->GetTransform()->SetLocalPosition({ 14,31 });
	Shooter0->SetRange(TowerRange);
	Shooter1 = GetLevel()->CreateActor<Ranged_Shooter>();
	Shooter1->GetTransform()->SetParent(GetTransform());
	Shooter1->GetTransform()->SetLocalPosition({ -10,31 });
	Shooter1->SetRange(TowerRange);

	TowerRangeRender->GetTransform()->SetWorldScale({ TowerRange * 2,TowerRange * 2 });
}
