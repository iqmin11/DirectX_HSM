#include "PrecompileHeader.h"
#include "Melee_Tower.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "RallyPoint.h"

Melee_Tower::Melee_Tower()
{

}

Melee_Tower::~Melee_Tower()
{

}

std::shared_ptr<Melee_Tower> Melee_Tower::CreateTower(GameEngineLevel* _Level, const float4& _BuildPos)
{
	std::shared_ptr<Melee_Tower> LocalAc = nullptr;
	LocalAc = _Level->CreateActor<Melee_Tower>();
	LocalAc->GetTransform()->SetWorldPosition(_BuildPos);
	LocalAc->AcRallyPoint = RallyPoint::CreateRallyPoint(_Level, _BuildPos, 3);
	LocalAc->AcRallyPoint->GetTransform()->SetParent(LocalAc->GetTransform());
	LocalAc->AcRallyPoint->GetTransform()->SetLocalPosition({0,-100,0});
	return LocalAc;
}

void Melee_Tower::Start()
{
	BaseTower::Start();

	Data.SetData(TowerEnum::MeleeTower_Level1);

	TowerRenderer->SetTexture("tower_barracks_lvl1_layer1_0001.png");
	TowerRenderer->GetTransform()->SetWorldScale(RenderScale);
}

void Melee_Tower::Update(float _DeltaTime)
{

}
