#include "PrecompileHeader.h"
#include "DeciedHeroPositionEffect.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

DeciedHeroPositionEffect::DeciedHeroPositionEffect()
{

}

DeciedHeroPositionEffect::~DeciedHeroPositionEffect()
{

}

std::shared_ptr<DeciedHeroPositionEffect> DeciedHeroPositionEffect::CreateEffect(GameEngineLevel* _Level, const float4& _Pos)
{
	std::weak_ptr<DeciedHeroPositionEffect> ResultEffect(_Level->CreateActor<DeciedHeroPositionEffect>());
	ResultEffect.lock()->GetTransform()->SetWorldPosition(_Pos);
	return ResultEffect.lock();
}

void DeciedHeroPositionEffect::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	Renderer->GetTransform()->SetWorldScale(RenderScale);
	Renderer->CreateAnimation({ .AnimationName = "Effect",.SpriteName = "HeroPositionAnimation", .FrameInter = 0.035f, .Loop = false });
	Renderer->SetAnimationStartEvent("Effect", 11, [this]()
		{
			Death();
		});

	Renderer->ChangeAnimation("Effect");
}

