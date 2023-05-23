#include "PrecompileHeader.h"
#include "PlayStageUI.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

PlayStageUI::PlayStageUI()
{

}

PlayStageUI::~PlayStageUI()
{

}

void PlayStageUI::Start()
{
	LoadTexture();

	StatusBg = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::UI);
	StatusBg->SetTexture("hud_background.png");
	StatusBg->GetTransform()->SetWorldScale(StatusBgScale);
	StatusBg->GetTransform()->SetWorldPosition(StatusBgPos);

	PauseButton = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::UI);
	PauseButton->SetTexture("hud_buttons_0001.png");
	PauseButton->GetTransform()->SetWorldScale(PauseButtonScale);
	PauseButton->GetTransform()->SetWorldPosition(PauseButtonPos);

	FireBallButton = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::UI);
	FireBallButton->SetTexture("power_portrait_fireball_0001.png");
	FireBallButton->GetTransform()->SetWorldScale(FireBallButtonScale);
	FireBallButton->GetTransform()->SetWorldPosition(FireBallButtonPos);

	ReinforcementButton = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::UI);
	ReinforcementButton->SetTexture("power_portrait_reinforcement_0001.png");
	ReinforcementButton->GetTransform()->SetWorldScale(ReinforcementButtonScale);
	ReinforcementButton->GetTransform()->SetWorldPosition(ReinforcementButtonPos);
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
