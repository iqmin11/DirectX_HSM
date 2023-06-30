#include "PrecompileHeader.h"
#include "DefeatBadge.h"

#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEngineCore\GameEngineLevel.h>
#include "_101UIRenderer.h"
#include "Defeat_RetryButton.h"
#include "Defeat_ExitButton.h"
#include "PlayStageLevel.h"
#include "_101UIFontRenderer.h"
#include <GameEngineBase\GameEngineRandom.h>

DefeatBadge::DefeatBadge()
{

}

DefeatBadge::~DefeatBadge()
{

}

void DefeatBadge::Start()
{
	BadgeRenderer = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_0);
	BadgeRenderer->SetTexture("defeatBadges_0002.png");
	BadgeRenderer->GetTransform()->SetWorldScale(RenderScale);
	AcRetryButton = GetLevel()->CreateActor<Defeat_RetryButton>(ActorOrder::MainUI);
	AcRetryButton->GetTransform()->SetParent(GetTransform());
	AcRetryButton->GetTransform()->SetLocalPosition(AcRetryButtonLocPos);
	AcRetryButton->SetEvent([this]()
		{
			Death();
			PlayStageLevel::IsPause = false;
			GetLevel()->DynamicThis<PlayStageLevel>()->InitStage(GetLevel()->DynamicThis<PlayStageLevel>()->GetCurStage());
		});

	AcExitButton = GetLevel()->CreateActor<Defeat_ExitButton>(ActorOrder::MainUI);
	AcExitButton->GetTransform()->SetParent(GetTransform());
	AcExitButton->GetTransform()->SetLocalPosition(AcExitButtonLocPos);
	AcExitButton->SetEvent([this]()
		{
			Death();
			PlayStageLevel::IsPause = false;
			GameEngineCore::ChangeLevel("WorldMapLevel");
		});

	SetTips();
	TipRender = CreateComponent<_101UIFontRenderer>(UIRenderOrder::StageUI_1);
	TipRender->SetFont(Font);
	TipRender->SetScale(FontScale);
	TipRender->SetFontFlag(FW1_CENTER);
	TipRender->SetColor(FontColor);
	TipRender->SetText(Tips[GameEngineRandom::MainRandom.RandomInt(0,6)]);
	TipRender->GetTransform()->SetLocalPosition(FontLocPos);
}

void DefeatBadge::Update(float _DeltaTime)
{
	if (State == DefeatBadgeState::Fall)
	{
		FallBadge(_DeltaTime);
	}

	if (GameEngineInput::IsDown("Z"))
	{
		State = DefeatBadgeState::Fall;
	}
}

void DefeatBadge::FallBadge(float _DeltaTime)
{
	Time += _DeltaTime;
	float x = 5 * Time;
	Ratio = sin(x) + 0.1f;
	float4 TempActorPos = float4::Lerp(StartPos, EndPos, Ratio);
	GetTransform()->SetWorldPosition(TempActorPos);

	if (x >= GameEngineMath::PIE / 2)
	{
		if (Ratio <= 1.f)
		{
			Ratio = 1.f;
			float4 TempActorPos = float4::Lerp(StartPos, EndPos, Ratio);
			GetTransform()->SetWorldPosition(TempActorPos);
			Time = 0.f;
			State = DefeatBadgeState::Update;
		}
	}
}

void DefeatBadge::SetTips()
{
	Tips.reserve(20);
	Tips.push_back("삶이 있는 한 희망은 있다\n-키케로");
	Tips.push_back("산다는것 그것은 치열한 전투이다\n -로망로랑");
	Tips.push_back("하루에 3시간을 걸으면 7년 후에\n 지구를 한바퀴 돌 수 있다 -사무엘존슨");
	Tips.push_back("언제나 현재에 집중할수 있다면\n 행복할것이다 -파울로 코엘료");
	Tips.push_back("신은 용기있는자를 결코 버리지\n 않는다 -켄러");
	Tips.push_back("한번의 실패와 영원한 실패를\n 혼동하지 마라 -F.스콧 핏제랄드");
	Tips.push_back("행복은 습관이다,그것을 몸에\n 지니라 -허버드");
}

void DefeatBadge::RenderTips(int _Index)
{
}
