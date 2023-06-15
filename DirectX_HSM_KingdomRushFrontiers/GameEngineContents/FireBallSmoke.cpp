#include "PrecompileHeader.h"
#include "FireBallSmoke.h"

#include <GameEngineBase\GameEngineRandom.h>
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
	SmokeScales.resize(3);
	SmokeScales[0] = { 18,14,1 };
	SmokeScales[1] = { 22,10,1 };
	SmokeScales[2] = { 14,18,1 };
	int RandomIndex = GameEngineRandom::MainRandom.RandomInt(0, 2);
	SmokeRenderer->GetTransform()->SetWorldScale(SmokeScales[RandomIndex]);

	SmokeRenderer->GetTransform()->SetParent(GetTransform());
	SmokeRenderer->CreateAnimation({.AnimationName = "Particle", .SpriteName = "FireBallSmoke", .FrameInter = 0.05f, .Loop = false });
	SmokeRenderer->ChangeAnimation("Particle");
}

void FireBallSmoke::Update(float _DeltaTime)
{
	Time += _DeltaTime;
	float Ratio = Time / 0.35f;
	float4 Scale = float4::LerpClamp(float4{ 0.5,0.5,0.5,1 }, float4{3,3,3,1}, Ratio);
	SmokeRenderer->ColorOptionValue.MulColor.a  = (1.f-Ratio);
	GetTransform()->SetWorldScale(Scale);
	if (Time >= 0.35f)
	{
		Death();
	}
}

