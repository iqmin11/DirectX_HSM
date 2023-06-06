#include "PrecompileHeader.h"
#include "BaseTowerUI.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

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
	RingRender = CreateComponent<GameEngineUIRenderer>();
	RingRender->SetTexture("gui_ring.png");
	RingRender->GetTransform()->SetWorldScale(RingRenderScale);
	RingRender->GetTransform()->SetLocalPosition({0,0,-1000});
}

void BaseTowerUI::Update(float _DeltaTime)
{

}

void BaseTowerUI::UpdateStart()
{
	UpdatedUI = this;
	++UpdateCount;
}

void BaseTowerUI::UpdateEnd()
{
	--UpdateCount;
	if (UpdateCount == 0)
	{
		UpdatedUI = nullptr;
	}
}
