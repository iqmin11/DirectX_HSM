#include "PrecompileHeader.h"
#include "DeciedRallyPointEffect.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "Melee_Tower.h"


DeciedRallyPointEffect::DeciedRallyPointEffect()
{

}

DeciedRallyPointEffect::~DeciedRallyPointEffect()
{

}

std::shared_ptr<DeciedRallyPointEffect> DeciedRallyPointEffect::CreateRallyEffect(Melee_Tower* _Parent, const float4& _Pos)
{
	std::weak_ptr<DeciedRallyPointEffect> ResultEffect(_Parent->GetLevel()->CreateActor<DeciedRallyPointEffect>());
	ResultEffect.lock()->GetTransform()->SetWorldPosition(_Pos);
	return ResultEffect.lock();
}

void DeciedRallyPointEffect::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	Renderer->GetTransform()->SetWorldScale(RenderScale);
	Renderer->CreateAnimation({ .AnimationName = "Effect",.SpriteName = "RallyPointEffectAnimation", .FrameInter = 0.04f, .Loop = false });
	Renderer->SetAnimationStartEvent("Effect", 19, [this]()
		{
			Death();
		});

	Renderer->ChangeAnimation("Effect");
}

void DeciedRallyPointEffect::Update(float _DeltaTime)
{

}
