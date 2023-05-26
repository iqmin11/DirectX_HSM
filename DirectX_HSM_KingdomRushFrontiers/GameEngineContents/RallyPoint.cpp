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
	TestRallyRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	TestRallyRender->SetTexture("TestRally.png");
	TestRallyRender->GetTransform()->SetWorldScale({ 128,128,1 });

	RangeRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	RangeRender->SetTexture("range_circle.png");
	RangeRender->GetTransform()->SetWorldScale({ Range*2.f,Range*2.f,0.f });
	RangeRender->GetTransform()->SetLocalPosition({ 0.f,0.f,300.f });
	//RangeRender->GetTransform()->SetLocalRotation({ 45.f,0,0 });

	RangeCol = CreateComponent<GameEngineCollision>(ColOrder::Fighter);
	RangeCol->GetTransform()->SetWorldScale({ Range * 2.f,Range * 2.f,0.f });
	//RangeCol->GetTransform()->SetLocalRotation({ 45.f,0,0 });
	
	Fighters.resize(3);
	for (size_t i = 0; i < Fighters.size(); i++)
	{
		Fighters[i] = GetLevel()->CreateActor<BaseFighter>();
		Fighters[i]->GetTransform()->SetWorldPosition(float4::Zero);
		Fighters[i]->SetParentRally(this);
		Fighters[i]->SetPrevPos(float4::Zero);
		Fighters[i]->SetRallyPos(float4::Zero);
	}

	//Fighter0RallyPos = GetTransform()->GetWorldPosition() + float4{ 0,20.f,20.f,0 };
	//Fighter0 = GetLevel()->CreateActor<BaseFighter>();
	//Fighter0->GetTransform()->SetWorldPosition(Fighter0RallyPos);
	//Fighter0->SetParentRally(this);
	//Fighter0->SetPrevPos(Fighter0RallyPos);
	//Fighter0->SetRallyPos(Fighter0RallyPos);

	//Fighter1RallyPos = GetTransform()->GetWorldPosition() + float4{ 0,-20.f,-20.f,0 };
	//Fighter1 = GetLevel()->CreateActor<BaseFighter>();
	//Fighter1->GetTransform()->SetWorldPosition(Fighter1RallyPos);
	//Fighter1->SetParentRally(this);
	//Fighter1->SetPrevPos(Fighter1RallyPos);
	//Fighter1->SetRallyPos(Fighter1RallyPos);
}

void RallyPoint::Update(float _DeltaTime)
{
	if (GameEngineInput::IsUp("LeftClick") && GameEngineInput::IsPress("V"))
	{
		float4 Pos = MousePointer::GetMousePosRef();
		Pos = Pos + float4{ 0,0,Pos.y,0 };
		SetRallyPos(Pos);
	}

	if (IsThereTarget()) 
	{
		// 1. ���͵� �� ��������Ʈ�κ��� ���� ����� ���͵��� �Ÿ������� ��� ����. �̶� ���͵��� FightState�� false�ξֵ��� �켱, FightState�� �ֵ��� ������ �ȴ� .
		// 2. Rally�� �������ִ� Fighter�� ��, ��� ���Ͱ� nullptr�̸� �켱�������� �־��ش�.��� ������ ���ľ� �ҵ�.
		RangeCol->CollisionAll(ColOrder::Monster, ColMonsters, ColType::SPHERE2D, ColType::AABBBOX2D);
		if (ColMonsters.size() > Fighters.size())
		{
			ColMonsters.resize(Fighters.size());
		}
		
		for (size_t i = 0; i < ColMonsters.size(); i++)
		{
			std::shared_ptr<BaseMonster> Monster = ColMonsters[i]->GetActor()->DynamicThis<BaseMonster>();
			for (size_t j = 0; j < Fighters.size(); j++)
			{
				if (Fighters[j]->TargetMonster == nullptr)
				{
					Fighters[j]->TargetMonster = Monster;
				}
				/*else if(j > 0)
				{
					if (Fighters[j]->TargetMonster == Fighters[j-1]->TargetMonster && Fighters[j]->TargetMonster != Monster)
					{
						Fighters[j]->TargetMonster = Monster;
					}
				}*/
			}
			//if (Fighter0->TargetMonster == nullptr)
			//{
			//	
			//	if (Fighter1->TargetMonster == nullptr)
			//	{
			//		Fighter1->TargetMonster = ColMonsters[i]->GetActor()->DynamicThis<BaseMonster>();
			//	}
			//}
			
			//if (Fighter1->TargetMonster == Fighter0->TargetMonster && Fighter1->TargetMonster != ColMonsters[i]->GetActor()->DynamicThis<BaseMonster>())
			//{
			//	Fighter1->TargetMonster = ColMonsters[i]->GetActor()->DynamicThis<BaseMonster>();
			//}
		}

		//if (ColMonsters.size() == 1)
		//{
		//	TargetMonster0 = TargetMonster1 = TargetMonster2 = ColMonsters[0]->GetActor()->DynamicThis<BaseMonster>();
		//}
		//else if(ColMonsters.size() == 2)
		//{
		//	TargetMonster0 = TargetMonster1 = ColMonsters[0]->GetActor()->DynamicThis<BaseMonster>();
		//	TargetMonster2 = ColMonsters[1]->GetActor()->DynamicThis<BaseMonster>();
		//}
		//else if (ColMonsters.size() >= 3)
		//{
		//	std::sort(ColMonsters.begin(), ColMonsters.end(),
		//		[this](std::shared_ptr<GameEngineCollision> _Left, std::shared_ptr<GameEngineCollision> _Right)
		//		{
		//			return CalDistance(_Left) > CalDistance(_Right);
		//		});
		//
		//	TargetMonster0 = ColMonsters[0]->GetActor()->DynamicThis<BaseMonster>();
		//	TargetMonster1 = ColMonsters[1]->GetActor()->DynamicThis<BaseMonster>();
		//	TargetMonster2 = ColMonsters[2]->GetActor()->DynamicThis<BaseMonster>();
		//}
		//Sort
		//if (ColMonsters.size() >= 2)
		//{
		//	std::sort(ColMonsters.begin(), ColMonsters.end(),
		//		[this](std::shared_ptr<GameEngineCollision> _Left, std::shared_ptr<GameEngineCollision> _Right)
		//		{
		//			return CalDistance(_Left) > CalDistance(_Right);
		//		});
		//}
		//
		////�켱������ ���� ���ͺ��� ���ʷ� �ο� ���̱�
		//if (TargetMonster0 == nullptr)
		//{
		//	TargetMonster0 = ColMonsters[0]->GetActor()->DynamicThis<BaseMonster>();
		//
		//}
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

void RallyPoint::SetRallyPos(float4 _Pos)
{
	GetTransform()->SetWorldPosition(_Pos);
	float4 LocalRallyPos = GetTransform()->GetWorldPosition();
	for (size_t i = 0; i < Fighters.size(); i++)
	{
		Fighters[i]->SetRallyPos(LocalRallyPos);
		Fighters[i]->SetPrevPos(Fighters[i]->GetTransform()->GetWorldPosition());
		Fighters[i]->ResetRatio();
	}
}

float RallyPoint::CalDistance(std::shared_ptr<class GameEngineCollision> _Monster)
{
	return (GetTransform()->GetWorldPosition() - _Monster->GetTransform()->GetWorldPosition()).Size();
}


