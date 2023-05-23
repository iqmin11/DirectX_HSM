#include "PrecompileHeader.h"
#include "FightObjBase.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

FightObjBase::FightObjBase()
{

}

FightObjBase::~FightObjBase()
{

}

void FightObjBase::Start()
{
	TestRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	TestRenderer->GetTransform()->SetWorldScale(TestRendererScale);
	TestRenderer->CreateAnimation({.AnimationName = "Idle", .SpriteName = "FightObj_Test_Idle", .FrameInter = 0.08f});
	//TestRenderer->CreateAnimation({.AnimationName = "Move", .SpriteName = "FightObj_Test_Move", .FrameInter = 0.08f});
	//TestRenderer->CreateAnimation({.AnimationName = "Attack", .SpriteName = "FightObj_Test_Attack", .FrameInter = 0.08f});

	TestRenderer->ChangeAnimation("Idle");
}

void FightObjBase::Update(float _DeltaTime)
{
	float Speed = 100;
	if (GameEngineInput::IsPress("U"))
	{
		ActorPos += float4::Up * _DeltaTime * Speed;
		ActorPos += float4::Forward * _DeltaTime * Speed;
	}

	if (GameEngineInput::IsPress("H"))
	{
		ActorPos += float4::Left * _DeltaTime * Speed;
	}

	if (GameEngineInput::IsPress("J"))
	{
		ActorPos += float4::Down * _DeltaTime * Speed;
		ActorPos += float4::Back * _DeltaTime * Speed;
	}

	if (GameEngineInput::IsPress("K"))
	{
		ActorPos += float4::Right * _DeltaTime * Speed;
	}

	GetTransform()->SetWorldPosition(ActorPos);
}
