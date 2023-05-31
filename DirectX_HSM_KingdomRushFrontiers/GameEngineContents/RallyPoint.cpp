#include "PrecompileHeader.h"
#include "RallyPoint.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "MousePointer.h"
#include "BaseMonster.h"
#include "BaseFighter.h"

RallyPoint::RallyPoint()
{

}

RallyPoint::~RallyPoint()
{

}

void RallyPoint::Start()
{
	//TestRallyRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	//TestRallyRender->SetTexture("TestRally.png");
	//TestRallyRender->GetTransform()->SetWorldScale({ 128,128,1 });

	//RangeRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	//RangeRender->SetTexture("range_circle.png");
	//RangeRender->GetTransform()->SetWorldScale({ Range*2.f,Range*2.f,0.f });
	//RangeRender->GetTransform()->SetLocalPosition({ 0.f,0.f,300.f });
	//RangeRender->GetTransform()->SetLocalRotation({ 45.f,0,0 });

	RangeCol = CreateComponent<GameEngineCollision>(ColOrder::Fighter);
	RangeCol->GetTransform()->SetWorldScale({ Range * 2.f,Range * 2.f,0.f });
	//RangeCol->GetTransform()->SetLocalRotation({ 45.f,0,0 });

	RallyPosCheckComponents.resize(3);

	for (size_t i = 0; i < RallyPosCheckComponents.size(); i++)
	{
		RallyPosCheckComponents[i] = CreateComponent<GameEngineComponent>();
	}

	RallyPosCheckComponents[0]->GetTransform()->SetLocalPosition({-25, 0, 0});
	RallyPosCheckComponents[1]->GetTransform()->SetLocalPosition({ 0, -25, -25 });
	RallyPosCheckComponents[2]->GetTransform()->SetLocalPosition({ 25, 0, 0 });

}

void RallyPoint::Update(float _DeltaTime)
{
	//if (GameEngineInput::IsUp("LeftClick") && GameEngineInput::IsPress("A"))
	//{
	//	float4 Pos = MousePointer::GetMousePosRef();
	//	Pos = Pos + float4{ 0,0,Pos.y,0 };
	//	SetRallyPos(Pos);
	//}

	for (size_t i = 0; i < Fighters.size(); i++)
	{
		if (Fighters[i] == nullptr)
		{
			continue;
		}

		if (Fighters[i]->State == FighterState::Death)
		{
			Fighters[i] = nullptr;
		}
	}

	if (IsThereTarget())
	{
		FindTarget();
	}
}

bool RallyPoint::IsThereTarget()
{
	return nullptr != RangeCol->Collision(ColOrder::Monster, ColType::SPHERE2D, ColType::AABBBOX2D);
}

void RallyPoint::SetRallyPos()
{
	for (size_t i = 0; i < Fighters.size(); i++)
	{
		Fighters[i]->SetPrevPos(Fighters[i]->GetTransform()->GetWorldPosition());
		Fighters[i]->ResetRatio();
	}
}

void RallyPoint::SetPrevTarget()
{
	for (size_t i = 0; i < Fighters.size(); i++)
	{
		if (Fighters[i] == nullptr)
		{
			continue;
		}
		Fighters[i]->PrevTarget = Fighters[i]->TargetMonster;
	}
}

void RallyPoint::FindTarget()
{
	SetPrevTarget();

	size_t ColCount = ColMonsters.size();

	RangeCol->CollisionAll(ColOrder::Monster, ColMonsters, ColType::SPHERE2D, ColType::AABBBOX2D);
	if (ColMonsters.size() > Fighters.size())
	{
		ColMonsters.resize(Fighters.size());
	}

	if (ColCount != ColMonsters.size())
	{
		ColCount = ColMonsters.size();
		IsChangeColCount = true;
	}
	else
	{
		IsChangeColCount = false;
	}

	if (ColCount == 1)
	{
		if (IsChangeColCount)
			ResetTargetMonster();

		if (Fighters[0] != nullptr && !Fighters[0]->HaveITarget())
			Fighters[0]->SetTarget(ColMonsters[0]->GetActor()->DynamicThis<BaseMonster>());
		if (Fighters[1] != nullptr && !Fighters[1]->HaveITarget())
			Fighters[1]->SetTarget(ColMonsters[0]->GetActor()->DynamicThis<BaseMonster>());
		if (Fighters[2] != nullptr && !Fighters[2]->HaveITarget())
			Fighters[2]->SetTarget(ColMonsters[0]->GetActor()->DynamicThis<BaseMonster>());
	}
	else if (ColCount == 2)
	{
		if (IsChangeColCount)
			ResetTargetMonster();

		if (Fighters[0] != nullptr && !Fighters[0]->HaveITarget())
			Fighters[0]->SetTarget(ColMonsters[0]->GetActor()->DynamicThis<BaseMonster>());

		if (Fighters[1] != nullptr && (!Fighters[1]->HaveITarget() || Fighters[1]->TargetMonster == ColMonsters[0]->GetActor()->DynamicThis<BaseMonster>()))
			Fighters[1]->SetTarget(ColMonsters[1]->GetActor()->DynamicThis<BaseMonster>());

		if (Fighters[2] != nullptr && !Fighters[2]->HaveITarget())
			Fighters[2]->SetTarget(ColMonsters[0]->GetActor()->DynamicThis<BaseMonster>());
	}
	else if (ColCount == 3)
	{
		if (IsChangeColCount)
			ResetTargetMonster();

		if (Fighters[0] && !Fighters[0]->HaveITarget())
			Fighters[0]->SetTarget(ColMonsters[0]->GetActor()->DynamicThis<BaseMonster>());
		if (Fighters[1] != nullptr && (!Fighters[1]->HaveITarget() || Fighters[1]->TargetMonster == ColMonsters[0]->GetActor()->DynamicThis<BaseMonster>()))
			Fighters[1]->SetTarget(ColMonsters[1]->GetActor()->DynamicThis<BaseMonster>());
		if (Fighters[2] != nullptr && (!Fighters[2]->HaveITarget() || Fighters[2]->TargetMonster == ColMonsters[0]->GetActor()->DynamicThis<BaseMonster>()))
			Fighters[2]->SetTarget(ColMonsters[2]->GetActor()->DynamicThis<BaseMonster>());
	}

	SetBoolChangeTarget();
}

void RallyPoint::SetBoolChangeTarget()
{
	for (size_t i = 0; i < Fighters.size(); i++)
	{
		if (Fighters[i] == nullptr)
		{
			continue;
		}

		if (Fighters[i]->PrevTarget != Fighters[i]->TargetMonster)
		{
			Fighters[i]->IsChangeTarget = true;
		}
		else
		{
			Fighters[i]->IsChangeTarget = false;
		}
	}
}

void RallyPoint::ResetTargetMonster()
{
	for (size_t i = 0; i < Fighters.size(); i++)
	{
		if (Fighters[i] == nullptr)
		{
			continue;
		}

		if (Fighters[i]->TargetMonster != nullptr)
		{
			if (Fighters[i]->TargetMonster->TargetFighter != nullptr)
			{
				Fighters[i]->TargetMonster->TargetFighter = nullptr;
			}
			Fighters[i]->TargetMonster = nullptr;
		}
	}
}

//void RallyPoint::SetFighter(int _Count)
//{
//	Fighters.resize(_Count);
//	FighterMaxCount = _Count;
//	for (size_t i = 0; i < Fighters.size(); i++)
//	{
//		Fighters[i] = GetLevel()->CreateActor<BaseFighter>();
//		Fighters[i]->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
//		Fighters[i]->SetParentRally(this);
//		Fighters[i]->SetPrevPos(GetTransform()->GetWorldPosition());
//		Fighters[i]->SetRallyTransform(RallyPosCheckComponents[i]->GetTransform());
//	}
//}

float RallyPoint::CalDistance(std::shared_ptr<class GameEngineCollision> _Monster)
{
	return (GetTransform()->GetWorldPosition() - _Monster->GetTransform()->GetWorldPosition()).Size();
}


