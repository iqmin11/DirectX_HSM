#include "PrecompileHeader.h"
#include "FireBallSmoke.h"

#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore\GameEngineSpriteRenderer.h>

FireBallSmoke::FireBallSmoke()
{

}

FireBallSmoke::~FireBallSmoke()
{

}

void FireBallSmoke::CreateSmoke(GameEngineLevel* _Level, const float4& _Pos)
{
	std::weak_ptr<FireBallSmoke> ResultEffect(_Level->CreateActor<FireBallSmoke>());
	ResultEffect.lock()->GetTransform()->SetWorldPosition(_Pos + float4{0,0,1,0});
}

void FireBallSmoke::Start()
{
	SmokeRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	SmokeRenderer->GetTransform()->SetWorldScale(SmokeScale);
	SmokeRenderer->CreateAnimation({.AnimationName = "Particle", .SpriteName = "FireBallSmoke", .FrameInter = 0.1f, .Loop = false });
	SmokeRenderer->SetAnimationStartEvent("Particle", 3, [this]()
		{
			Death();
		});
	SmokeRenderer->ChangeAnimation("Particle");
}

void FireBallSmoke::Update(float _DeltaTime)
{
	Time += _DeltaTime;
	SmokeRenderer->ColorOptionValue.MulColor.a -= _DeltaTime;
}

