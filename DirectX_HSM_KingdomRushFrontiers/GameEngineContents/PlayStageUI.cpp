#include "PrecompileHeader.h"
#include "PlayStageUI.h"

#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

#include "Button_RainOfFire.h"
#include "Button_CallReinforcement.h"
#include "BottomWaveButton.h"
#include "Hero_Portrait.h"
#include "PlayerStatus.h"

PlayStageUI* PlayStageUI::MainStageUI = nullptr;

PlayStageUI::PlayStageUI()
{
	if (MainStageUI != nullptr)
	{
		return;
	}
	MainStageUI = this;
}

PlayStageUI::~PlayStageUI()
{

}

void PlayStageUI::SetWaveButtonEvent(std::function<void()> _Click)
{
	WaveButton->SetEvent(_Click);
}

void PlayStageUI::Start()
{
	LoadTexture();

	AcPlayerStatus = GetLevel()->CreateActor<PlayerStatus>();
	AcPlayerStatus->GetTransform()->SetWorldPosition(StatusPos);

	FrameDeco = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_1);
	FrameDeco->SetTexture("FrameDeco.png");
	FrameDeco->GetTransform()->SetWorldScale(FrameDecoScale);
	FrameDeco->GetTransform()->SetWorldPosition(FrameDecoPos);

	AcHeroPortrait = GetLevel()->CreateActor<Hero_Portrait>();
	AcHeroPortrait->GetTransform()->SetWorldPosition(HeroPortraitFramePos);


	PauseButton = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_1);
	PauseButton->SetTexture("PauseButton.png");
	PauseButton->GetTransform()->SetWorldScale(PauseButtonScale);
	PauseButton->GetTransform()->SetWorldPosition(PauseButtonPos);

	PauseFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_0);
	PauseFrame->SetTexture("PauseFrame.png");
	PauseFrame->GetTransform()->SetWorldScale(PauseFrameScale);
	PauseFrame->GetTransform()->SetWorldPosition(PauseFramePos);

	RainOfFireButton = Button_RainOfFire::CreateButton(GetLevel());
	RainOfFireButton->GetTransform()->SetWorldPosition(RainOfFireButtonPos);

	ReinforcementButton = Button_CallReinforcement::CreateButton(GetLevel());
	ReinforcementButton->GetTransform()->SetWorldPosition(ReinforcementButtonPos);

	SpellButtonFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_2);
	SpellButtonFrame->SetTexture("SpellButtonFrame.png");
	SpellButtonFrame->GetTransform()->SetWorldScale(SpellButtonFrameScale);
	SpellButtonFrame->GetTransform()->SetWorldPosition(SpellButtonFramePos);

	UnderFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_0);
	UnderFrame->SetTexture("UnderFrame.png");
	UnderFrame->GetTransform()->SetWorldScale(UnderFrameScale);
	UnderFrame->GetTransform()->SetWorldPosition(UnderFramePos);

	UnderSpellFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_1);
	UnderSpellFrame->SetTexture("UnderSpellFrame.png");
	UnderSpellFrame->GetTransform()->SetWorldScale(UnderSpellFrameScale);
	UnderSpellFrame->GetTransform()->SetWorldPosition(UnderSpellFramePos);

	UnderWaveFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_1);
	UnderWaveFrame->SetTexture("UnderWaveFrame.png");
	UnderWaveFrame->GetTransform()->SetWorldScale(UnderWaveFrameScale);
	UnderWaveFrame->GetTransform()->SetWorldPosition(UnderWaveFramePos);

	WaveButton = BottomWaveButton::CreateButton(GetLevel());
	WaveButton->GetTransform()->SetWorldPosition(WaveButtonPos);

	WaveStartButtonFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_2);
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
