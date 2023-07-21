#include "PrecompileHeader.h"
#include "VictoryBadge.h"

#include <GameEngineCore\GameEngineLevel.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include "PlayStageLevel.h"
#include "ContinueButton.h"
#include "RetryButton.h"
#include "Effect_SpreadStar.h"
#include "_101UIRenderer.h"
#include "_101UIFontRenderer.h"
#include "PlayManager.h"
#include "WorldMapFlagManager.h"
#include "WorldMapFlag.h"

VictoryBadge::VictoryBadge()
{

}

VictoryBadge::~VictoryBadge()
{

}

void VictoryBadge::Start()
{
	GetTransform()->SetLocalPosition({0,150});
	SetBg();
	SetVictoryFont();
	SetStarAnimation();
	AcContinueButton = GetLevel()->CreateActor<ContinueButton>(ActorOrder::MainUI);
	AcContinueButton->GetTransform()->SetParent(GetTransform());
	AcContinueButton->SetEvent([this]()
		{
			Death();
			PlayStageLevel::IsPause = false;
			GameEngineCore::ChangeLevel("WorldMapLevel");
		});
	AcContinueButton->Off();

	AcRetryButton = GetLevel()->CreateActor<RetryButton>(ActorOrder::MainUI);
	AcRetryButton->GetTransform()->SetParent(GetTransform());
	AcRetryButton->GetTransform()->SetLocalPosition(RetryButtonEndLocPos);
	AcRetryButton->SetEvent([this]()
		{
			Death();
			PlayStageLevel::IsPause = false;
			GetLevel()->DynamicThis<PlayStageLevel>()->InitStage(GetLevel()->DynamicThis<PlayStageLevel>()->GetCurStage());
		});
	AcRetryButton->Off();
}

void VictoryBadge::Update(float _DeltaTime)
{
	if (State == VicBadgeState::GrowBig)
	{
		GrowBig(_DeltaTime);

	}
	else if (State == VicBadgeState::Star)
	{
		if (!StarAnimation->IsUpdate())
		{
			StarAnimation->On();
			EstimateStar();
		}

		if (StarAnimation->IsAnimationEnd())
		{
			State = VicBadgeState::FallButton1;
		}
	}
	else if (State == VicBadgeState::FallButton1)
	{
		if (!AcContinueButton->IsUpdate())
		{
			AcContinueButton->On();
		}
		FallButton1(_DeltaTime);
	}
	else if (State == VicBadgeState::FallButton2)
	{
		if (!AcRetryButton->IsUpdate())
		{
			AcRetryButton->On();
		}
		FallButton2(_DeltaTime);
	}
}

void VictoryBadge::SetBg()
{
	VictoryBadgeBg = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_6);
	VictoryBadgeBg->GetTransform()->SetWorldScale(VictoryBadgeBgScale);
	VictoryBadgeBg->GetTransform()->SetParent(GetTransform());
	VictoryBadgeBg->SetTexture("victoryBadges_0002.png");
}

void VictoryBadge::SetVictoryFont()
{
	FontRender = CreateComponent<_101UIFontRenderer>(UIRenderOrder::StageUI_7);
	FontRender->SetFont(Font);
	FontRender->SetFontFlag(FW1_CENTER);
	FontRender->SetScale(FontScale);
	FontRender->SetColor(FontColor);
	FontRender->SetText(Victory);
	FontRender->GetTransform()->SetLocalPosition(FontLocPos);
}

void VictoryBadge::SetStarAnimation()
{
	StarAnimation = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_7);
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

	StarAnimation->CreateAnimation({ .AnimationName = "1Star", .SpriteName = "StarAnimation", .FrameInter = 0.05f ,.Loop = false, .FrameIndex = OneStarAnimationIndex });
	StarAnimation->CreateAnimation({ .AnimationName = "2Star", .SpriteName = "StarAnimation", .FrameInter = 0.05f ,.Loop = false, .FrameIndex = TwoStarAnimationIndex });
	StarAnimation->CreateAnimation({ .AnimationName = "3Star", .SpriteName = "StarAnimation", .FrameInter = 0.05f ,.Loop = false, .FrameIndex = ThreeStarAnimationIndex });
	
	StarAnimation->SetAnimationStartEvent("1Star", 0, std::bind(&VictoryBadge::PlayStarSound, this));
	StarAnimation->SetAnimationStartEvent("2Star", 0, std::bind(&VictoryBadge::PlayStarSound, this));
	StarAnimation->SetAnimationStartEvent("2Star", 15, std::bind(&VictoryBadge::PlayStarSound, this));
	StarAnimation->SetAnimationStartEvent("3Star", 0, std::bind(&VictoryBadge::PlayStarSound, this));
	StarAnimation->SetAnimationStartEvent("3Star", 15, std::bind(&VictoryBadge::PlayStarSound, this));
	StarAnimation->SetAnimationStartEvent("3Star", 31, std::bind(&VictoryBadge::PlayStarSound, this));
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
			std::weak_ptr<Effect_SpreadStar> StarEffect(Effect_SpreadStar::CreateEffect(this, float4{ 0,100 }));
			DidISpreadStar = true;
		}

		if (Ratio <= 1.f)
		{
			Ratio = 1.f;
			float4 TempActorScale = float4::Lerp(float4::Zero, float4::One, Ratio);
			FontRender->SetScale(FontScale * TempActorScale.x);
			GetTransform()->SetWorldScale(TempActorScale);
			Time = 0.f;
			State = VicBadgeState::Star;
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
		State = VicBadgeState::FallButton2;
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
		State = VicBadgeState::Update;
	}
}

void VictoryBadge::EstimateStar()
{
	switch (PlayManager::MainPlayer->Life)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		StarAnimation->ChangeAnimation("1Star");
		WorldMapFlagManager::MainFlagManager->GetFlags()[PlayStageLevel::MainPalyStage->GetCurStage()]->SetClearData(1);
		WorldMapFlagManager::MainFlagManager->GetFlags()[PlayStageLevel::MainPalyStage->GetCurStage()]->SetState(FlagState::Start);
		break;
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
		StarAnimation->ChangeAnimation("2Star");
		WorldMapFlagManager::MainFlagManager->GetFlags()[PlayStageLevel::MainPalyStage->GetCurStage()]->SetClearData(2);
		WorldMapFlagManager::MainFlagManager->GetFlags()[PlayStageLevel::MainPalyStage->GetCurStage()]->SetState(FlagState::Start);
		break;
	case 18:
	case 19:
	case 20:
		StarAnimation->ChangeAnimation("3Star");
		WorldMapFlagManager::MainFlagManager->GetFlags()[PlayStageLevel::MainPalyStage->GetCurStage()]->SetClearData(3);
		WorldMapFlagManager::MainFlagManager->GetFlags()[PlayStageLevel::MainPalyStage->GetCurStage()]->SetState(FlagState::Start);
		break;
	default:
		break;
	}
}

void VictoryBadge::PlayStarSound()
{
	StarSound = GameEngineSound::Play("Sound_WinStars.ogg");
	StarSound.SetVolume(0.2f);
}

