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
		// 1. ���͵� �� ��������Ʈ�κ��� ���� ����� ���͵��� �Ÿ������� ��� ����. �̶� ���͵��� FightState�� false�ξֵ��� �켱, FightState�� �ֵ��� ������ �ȴ� .
		// 2. Rally�� �������ִ� Fighter�� ��, ��� ���Ͱ� nullptr�̸� �켱�������� �־��ش�.��� ������ ���ľ� �ҵ�.
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


