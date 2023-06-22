#include "PrecompileHeader.h"
#include "BottomWaveButton.h"

#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore\GameEngineUIRenderer.h>
#include "PlayManager.h"

bool BottomWaveButton::IsValid = true;

BottomWaveButton::BottomWaveButton()
{

}

BottomWaveButton::~BottomWaveButton()
{

}

std::shared_ptr<BottomWaveButton> BottomWaveButton::CreateButton(GameEngineLevel* _Level)
{
	std::weak_ptr<BottomWaveButton> ResultButton(_Level->CreateActor<BottomWaveButton>());
	return ResultButton.lock();
}

void BottomWaveButton::Start()
{
	ContentsButton::Start();
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_3);
	Render->GetTransform()->SetWorldScale(ButtonRenderScale);
	SetTextureName("WaveButton_Release.png", "WaveButton_Hover.png", "WaveButton_Hover.png");
}

void BottomWaveButton::Update(float _DeltaTime)
{
	if (IsValid)
	{
		ContentsButton::Update(_DeltaTime);
	}
	else
	{
		Render->SetTexture(DisableTextureName);
	}
}
