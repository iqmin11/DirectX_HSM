#include "PrecompileHeader.h"
#include "BaseMonster.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>


BaseMonster::BaseMonster()
{

}

BaseMonster::~BaseMonster()
{

}

void BaseMonster::Start()
{
	MonsterRenderer = CreateComponent<GameEngineSpriteRenderer>();
	MonsterRenderer->SetPipeLine("2DTexture");
	MonsterRenderer->SetTexture("DesertThug0000.png");
	MonsterRenderer->GetTransform()->SetWorldScale({66,56});

	GameEngineInput::CreateKey("A",'A');
	GameEngineInput::CreateKey("S",'S');
	GameEngineInput::CreateKey("D",'D');
	GameEngineInput::CreateKey("W",'W');
}

void BaseMonster::Update(float _DeltaTime)
{
	WalkToNextPoint(_DeltaTime);
	//float Speed = 100.0f;
	//if (GameEngineInput::IsPress("A"))
	//{
	//	GetTransform()->AddWorldPosition(float4::Left * Speed * _DeltaTime);
	//}
	//
	//if (GameEngineInput::IsPress("S"))
	//{
	//	GetTransform()->AddWorldPosition(float4::Down * Speed * _DeltaTime);
	//}
	//
	//if (GameEngineInput::IsPress("D"))
	//{
	//	GetTransform()->AddWorldPosition(float4::Right * Speed * _DeltaTime);
	//}
	//
	//if (GameEngineInput::IsPress("W"))
	//{
	//	GetTransform()->AddWorldPosition(float4::Up * Speed * _DeltaTime);
	//}
}

void BaseMonster::WalkToNextPoint(float _DeltaTime)
{
	
	//내가 점을 어떻게 찍던 상관 없이 속도는 일정해야한다...
	//노말라이즈???
	//일단 움직이게 먼저 해보자
	static float Time = 0;
	Time += _DeltaTime;
	float4 ActorPos = float4::LerpClamp(CurPoint, NextPoint, Time / 10);
	GetTransform()->SetWorldPosition(ActorPos);
}
