#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class PlayStageUI : public GameEngineActor
{
public:
	static PlayStageUI* MainStageUI;
	// construtor destructor
	PlayStageUI();
	~PlayStageUI();

	// delete Function
	PlayStageUI(const PlayStageUI& _Other) = delete;
	PlayStageUI(PlayStageUI&& _Other) noexcept = delete;
	PlayStageUI& operator=(const PlayStageUI& _Other) = delete;
	PlayStageUI& operator=(PlayStageUI&& _Other) noexcept = delete;

	void SetWaveButtonEvent(std::function<void()> _Click);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class PlayerStatus> AcPlayerStatus = nullptr;
	float4 StatusPos = { -604, 436 };

	std::shared_ptr<class GameEngineUIRenderer> FrameDeco = nullptr;
	float4 FrameDecoScale = { 69,33,1 };
	float4 FrameDecoPos = { 171, -434 };

	std::shared_ptr<class Hero_Portrait> AcHeroPortrait = nullptr;
	float4 HeroPortraitFramePos = { -722, -393 };

	std::shared_ptr<class GameEngineUIRenderer> PauseButton = nullptr;
	float4 PauseButtonScale = { 41,38,1 };
	float4 PauseButtonPos = { 696, 428 };

	std::shared_ptr<class GameEngineUIRenderer> PauseFrame = nullptr;
	float4 PauseFrameScale = { 117,62,1 };
	float4 PauseFramePos = { 697, 441 };

	std::shared_ptr<class Button_RainOfFire> RainOfFireButton = nullptr;
	float4 RainOfFireButtonPos = { -570, -407 };

	std::shared_ptr<class Button_CallReinforcement> ReinforcementButton = nullptr;
	float4 ReinforcementButtonScale = { 68,68,1 };
	float4 ReinforcementButtonPos = { -493, -407 };

	std::shared_ptr<class GameEngineUIRenderer> SpellButtonFrame = nullptr;
	float4 SpellButtonFrameScale = { 240,75,1 };
	float4 SpellButtonFramePos = { -531, -414 };

	std::shared_ptr<class GameEngineUIRenderer> UnderFrame = nullptr;
	float4 UnderFrameScale = { 1632,17,1 };
	float4 UnderFramePos = { -12, -444};

	std::shared_ptr<class GameEngineUIRenderer> UnderSpellFrame = nullptr;
	float4 UnderSpellFrameScale = { 296,43,1 };
	float4 UnderSpellFramePos = { -530, -431 };

	std::shared_ptr<class GameEngineUIRenderer> UnderWaveFrame = nullptr;
	float4 UnderWaveFrameScale = { 145,43,1 };
	float4 UnderWaveFramePos = { 738, -431 };

	std::shared_ptr<class BottomWaveButton> WaveButton = nullptr;
	float4 WaveButtonScale = { 60,60,1 };
	float4 WaveButtonPos = { 738, -414 };

	std::shared_ptr<class GameEngineUIRenderer> WaveStartButtonFrame = nullptr;
	float4 WaveStartButtonFrameScale = { 114,64,1 };
	float4 WaveStartButtonFramePos = { 736, -420};

	void LoadTexture();
};

