#include "PrecompileHeader.h"
#include "BaseTowerUI.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include "PlayStageLevel.h"

int BaseTowerUI::UpdateCount = 0;
BaseTowerUI* BaseTowerUI::UpdatedUI = nullptr;

BaseTowerUI::BaseTowerUI()
{

}

BaseTowerUI::~BaseTowerUI()
{

}

void BaseTowerUI::OnUI()
{
	On();
	UpdateStart();
}

void BaseTowerUI::OffUI()
{
	Off();
	UpdateEnd();
}

void BaseTowerUI::Start()
{
	RingRender = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::TowerUI);
	RingRender->SetTexture("gui_ring.png");
	RingRender->GetTransform()->SetWorldScale(RingRenderScale);
	RingRender->GetTransform()->SetParent(GetTransform());
	RingRender->GetTransform()->SetLocalPosition({0,0,0});
}

void BaseTowerUI::Update(float _DeltaTime)
{
	if (GetLevel()->DynamicThis<PlayStageLevel>()->IsPause)
	{
		return;
	}

	if (State == BaseTowerUIState::Start)
	{
		Time += _DeltaTime;
		float Ratio = Time * 10;
		GetTransform()->SetWorldScale(float4::LerpClamp(StartActorScale, float4::One, Ratio));
		if (Ratio >= 1.f)
		{
			Time = 0.0f;
			State = BaseTowerUIState::Update;
		}
	}
}

void BaseTowerUI::UpdateStart()
{
	UpdatedUI = this;
	++UpdateCount;
}

void BaseTowerUI::UpdateEnd()
{
	State = BaseTowerUIState::Start;
	Time = 0.0f;
	--UpdateCount;
	if (UpdateCount == 0)
	{
		UpdatedUI = nullptr;
	}
}

