#include "PrecompileHeader.h"
#include "Effect_OneStar.h"

#include <GameEngineCore\GameEngineLevel.h>
#include "_101UIRenderer.h"

Effect_OneStar::Effect_OneStar()
{

}

Effect_OneStar::~Effect_OneStar()
{

}

void Effect_OneStar::CreatStar(class GameEngineLevel* _Level, const float4& _StartPos, const float4& _Dir, float _Gravity, float _Speed)
{
	std::weak_ptr<Effect_OneStar> LocalStar(_Level->CreateActor<Effect_OneStar>(ActorOrder::MainUI));
	LocalStar.lock()->StartPos = _StartPos;
	LocalStar.lock()->GetTransform()->SetWorldPosition(_StartPos);
	LocalStar.lock()->Dir = _Dir;
	LocalStar.lock()->Gravity = _Gravity;
	LocalStar.lock()->Speed = _Speed;
}

void Effect_OneStar::Start()
{
	StarRender = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_9);
	StarRender->GetTransform()->SetWorldScale(RenderScale);
	StarRender->SetTexture("SpreadStar.png");
}

void Effect_OneStar::Update(float _DeltaTime)
{
	GetTransform()->AddWorldPosition(Dir * _DeltaTime * Speed);
	GetTransform()->AddWorldPosition(float4::Down * Gravity * _DeltaTime);
	Gravity += Acceleration * _DeltaTime;
	if (MaxGravity < Gravity)
	{
		Gravity = MaxGravity;
	}
	Time += _DeltaTime;
	StarRender->ColorOptionValue.MulColor.x += _DeltaTime*2;
	StarRender->ColorOptionValue.MulColor.y += _DeltaTime*2;
	StarRender->ColorOptionValue.MulColor.z += _DeltaTime*2;
	
	StarRender->ColorOptionValue.MulColor.a -= _DeltaTime * 3 / 4;
	if (StarRender->ColorOptionValue.MulColor.a <= 0.f)
	{
		StarRender->ColorOptionValue.MulColor.a = 0.0f;
	}
	
	if (Time >= 2.f)
	{
		Death();
	}
	
}
