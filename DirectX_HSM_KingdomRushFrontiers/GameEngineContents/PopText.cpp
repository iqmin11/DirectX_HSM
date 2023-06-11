#include "PrecompileHeader.h"
#include "PopText.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

PopText::PopText()
{

}

PopText::~PopText()
{

}

std::shared_ptr<PopText> PopText::CreatePopText(HitState _Hit, std::shared_ptr<GameEngineActor> _Actor)
{
	if (_Hit == HitState::Etc)
	{
		return nullptr;
	}
	std::weak_ptr<PopText> ResultPop = std::weak_ptr<PopText>(_Actor->GetLevel()->CreateActor<PopText>());
	ResultPop.lock()->GetTransform()->SetWorldPosition(_Actor->GetTransform()->GetWorldPosition() + float4{0.f,30.f});
	ResultPop.lock()->SetTexture(_Hit);
	return ResultPop.lock();
}

void PopText::Start()
{
	PopTextRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	PopTextRenderer->GetTransform()->SetWorldScale(RenderScale);
	PopTextRenderer->GetTransform()->SetParent(GetTransform());
}

void PopText::Update(float _DeltaTime)
{
	EffectTime += _DeltaTime;
	float Ratio = abs(sin(EffectTime * EffectSpeed));
	if (EffectTime * EffectSpeed >= 2*GameEngineMath::PIE)
	{
		if (EffectTime >= 1.f)
		{
			Death();
		}
		return;
	}
	GetTransform()->SetWorldScale(float4::LerpClamp(float4::One, {1.1f,1.1f,1.1f}, Ratio));
}

void PopText::SetTexture(HitState _Hit)
{
	switch (_Hit)
	{
	case HitState::Etc:
		break;
	case HitState::Arrow:
	{
		if (0 == GameEngineRandom::MainRandom.RandomInt(0, 1))
		{
			PopTextRenderer->SetTexture("PopText0008.png");
		}
		else
		{
			PopTextRenderer->SetTexture("PopText0018.png");
		}
	}
	break;
	case HitState::Melee:
	{
		int RandomInt = GameEngineRandom::MainRandom.RandomInt(0, 3);
		if (RandomInt == 0)
		{
			PopTextRenderer->SetTexture("PopText0012.png");
		}
		else if (RandomInt == 1)
		{
			PopTextRenderer->SetTexture("PopText0013.png");
		}
		else if (RandomInt == 2)
		{
			PopTextRenderer->SetTexture("PopText0014.png");
		}
		else
		{
			PopTextRenderer->SetTexture("PopText0015.png");
		}
	}
	break;
	case HitState::Bolt:
		if (0 == GameEngineRandom::MainRandom.RandomInt(0, 1))
		{
			PopTextRenderer->SetTexture("PopText0010.png");
		}
		else
		{
			PopTextRenderer->SetTexture("PopText0019.png");
		}
		break;
	case HitState::Bomb:
		PopTextRenderer->SetTexture("PopText0016.png");
		break;
	default:
		break;
	}
}
