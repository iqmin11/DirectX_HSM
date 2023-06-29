#include "PrecompileHeader.h"
#include "VictoryBadge.h"

#include <GameEngineCore\GameEngineLevel.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEngineCore\GameEngineUIRenderer.h>
#include "ContinueButton.h"
#include "RetryButton.h"
#include "UIFontRenderer.h"
#include "Effect_SpreadStar.h"

VictoryBadge::VictoryBadge()
{

}

VictoryBadge::~VictoryBadge()
{

}

void VictoryBadge::Start()
{
	SetBg();
	SetVictoryFont();
	SetStarAnimation();
	AcContinueButton = GetLevel()->CreateActor<ContinueButton>();
	AcContinueButton->GetTransform()->SetParent(GetTransform());
	AcContinueButton->Off();

	AcRetryButton = GetLevel()->CreateActor<RetryButton>();
	AcRetryButton->GetTransform()->SetParent(GetTransform());
	AcRetryButton->GetTransform()->SetLocalPosition(RetryButtonEndLocPos);
	AcRetryButton->Off();
}

void VictoryBadge::Update(float _DeltaTime)
{
	if (State == BadgeState::GrowBig)
	{
		GrowBig(_DeltaTime);

	}
	else if (State == BadgeState::Star)
	{
		if (!StarAnimation->IsUpdate())
		{
			StarAnimation->On();
			StarAnimation->ChangeAnimation("3Star");
		}

		if (StarAnimation->IsAnimationEnd())
		{
			State = BadgeState::FallButton1;
		}
	}
	else if(State == BadgeState::FallButton1)
	{
		if (!AcContinueButton->IsUpdate())
		{
			AcContinueButton->On();
		}
		FallButton1(_DeltaTime);
	}
	else if (State == BadgeState::FallButton2)
	{
		if (!AcRetryButton->IsUpdate())
		{
			AcRetryButton->On();
		}
		FallButton2(_DeltaTime);
	}

	if (GameEngineInput::IsDown("Z"))
	{
		State = BadgeState::GrowBig;
		Time = 0.f;
	}
}

void VictoryBadge::SetBg()
{
	VictoryBadgeBg = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_6);
	VictoryBadgeBg->GetTransform()->SetWorldScale(VictoryBadgeBgScale);
	VictoryBadgeBg->GetTransform()->SetParent(GetTransform());
	VictoryBadgeBg->SetTexture("victoryBadges_0002.png");
}

void VictoryBadge::SetVictoryFont()
{
	FontRender = CreateComponent<UIFontRenderer>(UIRenderOrder::StageUI_7);
	FontRender->SetFont(Font);
	FontRender->SetFontFlag(FW1_CENTER);
	FontRender->SetScale(FontScale);
	FontRender->SetColor(FontColor);
	FontRender->SetText(Victory);
	FontRender->GetTransform()->SetLocalPosition(FontLocPos);
}

void VictoryBadge::SetStarAnimation()
{
	StarAnimation = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_7);
	StarAnimation->GetTransform()->SetWorldScale(StarAnimationScale);
	StarAnimation->GetTransform()->SetLocalPosition(StarAnimationLocPos);
	std::vector<size_t> OneStarAnimationIndex = std::vector<size_t>();
	std::vector<size_t> TwoStarAnimationIndex = std::vector<size_t>();
	std::vector<size_t> ThreeStarAnimationIndex = std::vector<size_t>();
	OneStarAnimationIndex.resize(15);
	TwoStarAnimationIndex.resize(31);
	ThreeStarAnimationIndex.resize(47);
	for (size_t i = 0; i < OneStarAnimationIndex.size(); i++)
	{
		OneStarAnimationIndex[i] = i;
	}

	for (size_t i = 0; i < TwoStarAnimationIndex.size(); i++)
	{
		TwoStarAnimationIndex[i] = i;
	}

	for (size_t i = 0; i < ThreeStarAnimationIndex.size(); i++)
	{
		ThreeStarAnimationIndex[i] = i;
	}

	StarAnimation->CreateAnimation({ .AnimationName = "1Star", .SpriteName = "StarAnimation", .FrameInter = 0.05f ,.Loop = false, .FrameIndex = OneStarAnimationIndex});
	StarAnimation->CreateAnimation({ .AnimationName = "2Star", .SpriteName = "StarAnimation", .FrameInter = 0.05f ,.Loop = false, .FrameIndex = TwoStarAnimationIndex });
	StarAnimation->CreateAnimation({ .AnimationName = "3Star", .SpriteName = "StarAnimation", .FrameInter = 0.05f ,.Loop = false, .FrameIndex = ThreeStarAnimationIndex });
	StarAnimation->Off();
}

void VictoryBadge::GrowBig(float _DeltaTime)
{
	Time += _DeltaTime;
	float x = 3 * Time;
	Ratio = sin(x) + 0.1f;
	float4 TempActorScale = float4::Lerp(float4::Zero, float4::One, Ratio);
	FontRender->SetScale(FontScale * TempActorScale.x);
	GetTransform()->SetWorldScale(TempActorScale);

	if (x >= GameEngineMath::PIE / 2)
	{
		if (DidISpreadStar == false)
		{
			std::weak_ptr<Effect_SpreadStar> StarEffect(Effect_SpreadStar::CreateEffect(this, float4{0,100}));
			DidISpreadStar = true;
		}
		
		if (Ratio <= 1.f)
		{
			Ratio = 1.f;
			float4 TempActorScale = float4::Lerp(float4::Zero, float4::One, Ratio);
			FontRender->SetScale(FontScale * TempActorScale.x);
			GetTransform()->SetWorldScale(TempActorScale);
			Time = 0.f;
			State = BadgeState::Star;
		}
	}


}

void VictoryBadge::FallButton1(float _DeltaTime)
{
	Time += _DeltaTime;
	float x = 3 * Time;
	Ratio = sin(x) + 0.1f;
	float4 TempActorLocPos = float4::Lerp(float4::Zero, ContinueButtonEndLocPos, Ratio);
	AcContinueButton->GetTransform()->SetLocalPosition(TempActorLocPos);

	if (x >= GameEngineMath::PIE / 2 && Ratio <= 1.f)
	{
		Ratio = 1.f;
		float4 TempActorLocPos = float4::Lerp(float4::Zero, ContinueButtonEndLocPos, Ratio);
		AcContinueButton->GetTransform()->SetLocalPosition(TempActorLocPos);
		Time = 0.f;
		State = BadgeState::FallButton2;
	}
}

void VictoryBadge::FallButton2(float _DeltaTime)
{
	Time += _DeltaTime;
	float x = 3 * Time;
	Ratio = sin(x) + 0.1f;
	float4 TempActorLocPos = float4::Lerp(ContinueButtonEndLocPos, RetryButtonEndLocPos, Ratio);
	AcRetryButton->GetTransform()->SetLocalPosition(TempActorLocPos);

	if (x >= GameEngineMath::PIE / 2 && Ratio <= 1.f)
	{
		Ratio = 1.f;
		float4 TempActorLocPos = float4::Lerp(ContinueButtonEndLocPos, RetryButtonEndLocPos, Ratio);
		AcRetryButton->GetTransform()->SetLocalPosition(TempActorLocPos);
		Time = 0.f;
		State = BadgeState::Update;
	}
}

