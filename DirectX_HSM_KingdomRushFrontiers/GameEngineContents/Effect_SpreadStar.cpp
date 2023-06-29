#include "PrecompileHeader.h"
#include "Effect_SpreadStar.h"

#include <GameEngineBase\GameEngineRandom.h>
#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore\GameEngineUIRenderer.h>
#include "Effect_OneStar.h"
#include "VictoryBadge.h"

Effect_SpreadStar::Effect_SpreadStar()
{

}

Effect_SpreadStar::~Effect_SpreadStar()
{

}

std::weak_ptr<Effect_SpreadStar> Effect_SpreadStar::CreateEffect(VictoryBadge* _Parent, float4 _EffectStartPos)
{
	std::weak_ptr<Effect_SpreadStar> ResultEffect(_Parent->GetLevel()->CreateActor<Effect_SpreadStar>(ActorOrder::VictoryBadge));
	ResultEffect.lock()->GetTransform()->SetWorldPosition(_Parent->GetTransform()->GetWorldPosition() + _EffectStartPos);
	ResultEffect.lock()->GetTransform()->SetParent(_Parent->GetTransform(), false);
	float4 Position = ResultEffect.lock()->GetTransform()->GetWorldPosition();
	for (size_t i = 0; i < ResultEffect.lock()->StarCount; i++)
	{
		float RandGravity = GameEngineRandom::MainRandom.RandomFloat(-600.f, -300.f);
		float RandSpeed = GameEngineRandom::MainRandom.RandomFloat(300.f, 600.f);
		float4 Dir = { cos(ResultEffect.lock()->Rad * i),sin(ResultEffect.lock()->Rad * i), 0, 0 };
		Effect_OneStar::CreatStar(ResultEffect.lock()->GetLevel(), Position, Dir, RandGravity, RandSpeed);
	}
	return ResultEffect;
}

void Effect_SpreadStar::Start()
{
	Rad = GameEngineMath::PIE2 / StarCount;
}

void Effect_SpreadStar::Update(float _DeltaTime)
{

}
