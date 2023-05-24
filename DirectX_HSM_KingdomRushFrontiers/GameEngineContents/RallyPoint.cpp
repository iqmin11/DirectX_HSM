#include "PrecompileHeader.h"
#include "RallyPoint.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "MousePointer.h"
#include "BaseMonster.h"

RallyPoint::RallyPoint()
{

}

RallyPoint::~RallyPoint()
{

}

void RallyPoint::Start()
{
	TestRallyRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	TestRallyRender->SetTexture("TestRally.png");
	TestRallyRender->GetTransform()->SetWorldScale({ 128,128,1 });

	RangeRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	RangeRender->SetTexture("range_circle.png");
	RangeRender->GetTransform()->SetWorldScale({ Range*2.f,Range*2.f,0.f });
	RangeRender->GetTransform()->SetLocalPosition({ 0,0,1 });
	//RangeRender->GetTransform()->SetLocalRotation({ 45.f,0,0 });

	RangeCol = CreateComponent<GameEngineCollision>(ColOrder::Fighter);
	RangeCol->GetTransform()->SetWorldScale({ Range * 2.f,Range * 2.f,0.f });
	//RangeCol->GetTransform()->SetLocalRotation({ 45.f,0,0 });
}

void RallyPoint::Update(float _DeltaTime)
{
	if (GameEngineInput::IsUp("LeftClick") && GameEngineInput::IsPress("V"))
	{
		float4 Pos = MousePointer::GetMousePosRef();
		Pos = Pos + float4{ 0,0,Pos.y,0 };
		GetTransform()->SetWorldPosition(Pos);
	}

	if (IsThereTarget()) 
	{
		// 1. 몬스터들 중 랠리포인트로부터 가장 가까운 몬스터들을 거리순으로 계속 정렬. 이때 몬스터들은 FightState가 false인애들이 우선, FightState인 애들은 차선이 된다 .
		// 2. Rally가 가지고있는 Fighter들 중, 상대 몬스터가 nullptr이면 우선순위별로 넣어준다.라는 과정을 거쳐야 할듯.
		RangeCol->CollisionAll(ColOrder::Monster, ColMonsters, ColType::SPHERE2D, ColType::AABBBOX2D);
	}
}

std::shared_ptr<class BaseMonster> RallyPoint::FindTargetMonster()
{
	return std::shared_ptr<class BaseMonster>();
}

bool RallyPoint::IsThereTarget()
{
	return nullptr != RangeCol->Collision(ColOrder::Monster, ColType::SPHERE2D, ColType::AABBBOX2D);
}

float RallyPoint::CalDistance(std::shared_ptr<class GameEngineCollision> _Monster)
{
	return (GetTransform()->GetWorldPosition() - _Monster->GetTransform()->GetWorldPosition()).Size();
}


