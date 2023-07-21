#include "PrecompileHeader.h"
#include "BottomWaveButton.h"

#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore\GameEngineUIRenderer.h>
#include "PlayManager.h"
#include "PlayStageLevel.h"

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

	UpSound = "";
}

void BottomWaveButton::Update(float _DeltaTime)
{
	if (GetLevel()->DynamicThis<PlayStageLevel>()->IsPause)
	{
		return;
	}

	if (IsValid)
	{
		if (!WaveReadySound.IsValid())
		{
			WaveReadySound = GameEngineSound::Play("Sound_NextWaveReady.ogg");
		}
		ContentsButton::Update(_DeltaTime);
	}
	else
	{
		WaveReadySound = GameEngineSoundPlayer();
		Render->SetTexture(DisableTextureName);
	}
}
