#include "PrecompileHeader.h"
#include "PlayStageUI.h"
#include <GameEngineCore/GameEngineUIRenderer.h>

PlayStageUI::PlayStageUI()
{

}

PlayStageUI::~PlayStageUI()
{

}

void PlayStageUI::Start()
{
	LoadTexture();

	StatusBg = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI);
	StatusBg->SetTexture("DisplayPlayerState.png");
	StatusBg->GetTransform()->SetWorldScale(StatusBgScale);
	StatusBg->GetTransform()->SetWorldPosition(StatusBgPos);

	FrameDeco = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI);
	FrameDeco->SetTexture("FrameDeco.png");
	FrameDeco->GetTransform()->SetWorldScale(FrameDecoScale);
	FrameDeco->GetTransform()->SetWorldPosition(FrameDecoPos);

	HeroPortrateFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI);
	HeroPortrateFrame->SetTexture("HeroPortrateFrame.png");
	HeroPortrateFrame->GetTransform()->SetWorldScale(HeroPortrateFrameScale);
	HeroPortrateFrame->GetTransform()->SetWorldPosition(HeroPortrateFramePos);

	PauseButton = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI);
	PauseButton->SetTexture("PauseButton.png");
	PauseButton->GetTransform()->SetWorldScale(PauseButtonScale);
	PauseButton->GetTransform()->SetWorldPosition(PauseButtonPos);

	PauseFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_Frame0);
	PauseFrame->SetTexture("PauseFrame.png");
	PauseFrame->GetTransform()->SetWorldScale(PauseFrameScale);
	PauseFrame->GetTransform()->SetWorldPosition(PauseFramePos);

	RainOfFireButton = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI);
	RainOfFireButton->SetTexture("RainOfFireButton.png");
	RainOfFireButton->GetTransform()->SetWorldScale(RainOfFireButtonScale);
	RainOfFireButton->GetTransform()->SetWorldPosition(RainOfFireButtonPos);

	ReinforcementButton = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI);
	ReinforcementButton->SetTexture("ReinforcementButton.png");
	ReinforcementButton->GetTransform()->SetWorldScale(ReinforcementButtonScale);
	ReinforcementButton->GetTransform()->SetWorldPosition(ReinforcementButtonPos);

	SpellButtonFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_Frame2);
	SpellButtonFrame->SetTexture("SpellButtonFrame.png");
	SpellButtonFrame->GetTransform()->SetWorldScale(SpellButtonFrameScale);
	SpellButtonFrame->GetTransform()->SetWorldPosition(SpellButtonFramePos);

	UnderFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_Frame0);
	UnderFrame->SetTexture("UnderFrame.png");
	UnderFrame->GetTransform()->SetWorldScale(UnderFrameScale);
	UnderFrame->GetTransform()->SetWorldPosition(UnderFramePos);

	UnderSpellFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_Frame1);
	UnderSpellFrame->SetTexture("UnderSpellFrame.png");
	UnderSpellFrame->GetTransform()->SetWorldScale(UnderSpellFrameScale);
	UnderSpellFrame->GetTransform()->SetWorldPosition(UnderSpellFramePos);

	UnderWaveFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_Frame1);
	UnderWaveFrame->SetTexture("UnderWaveFrame.png");
	UnderWaveFrame->GetTransform()->SetWorldScale(UnderWaveFrameScale);
	UnderWaveFrame->GetTransform()->SetWorldPosition(UnderWaveFramePos);

	WaveButton = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI);
	WaveButton->SetTexture("WaveButton.png");
	WaveButton->GetTransform()->SetWorldScale(WaveButtonScale);
	WaveButton->GetTransform()->SetWorldPosition(WaveButtonPos);

	WaveStartButtonFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_Frame2);
	WaveStartButtonFrame->SetTexture("WaveStartButtonFrame.png");
	WaveStartButtonFrame->GetTransform()->SetWorldScale(WaveStartButtonFrameScale);
	WaveStartButtonFrame->GetTransform()->SetWorldPosition(WaveStartButtonFramePos);

}

void PlayStageUI::Update(float _DeltaTime)
{
}

void PlayStageUI::LoadTexture()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("3.PLAY STAGE LEVEL");
	Dir.Move("GUI");

	std::vector<GameEngineFile> File = Dir.GetAllFile({ ".png" });
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineTexture::Load(File[i].GetFullPath());
	}
}
