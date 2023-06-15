#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class PlayStageUI : public GameEngineActor
{
public:
	// construtor destructor
	PlayStageUI();
	~PlayStageUI();

	// delete Function
	PlayStageUI(const PlayStageUI& _Other) = delete;
	PlayStageUI(PlayStageUI&& _Other) noexcept = delete;
	PlayStageUI& operator=(const PlayStageUI& _Other) = delete;
	PlayStageUI& operator=(PlayStageUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> StatusBg = nullptr;
	float4 StatusBgScale = { 222,76 };
	float4 StatusBgPos = {-430, 400};

	std::shared_ptr<class GameEngineUIRenderer> PauseButton = nullptr;
	float4 PauseButtonScale = { 56,52 };
	float4 PauseButtonPos = { 540, 400 };

	std::shared_ptr<class GameEngineUIRenderer> FireBallButton = nullptr;
	float4 FireBallButtonScale = { 106,106 };
	float4 FireBallButtonPos = { -500, -380 };

	std::shared_ptr<class GameEngineUIRenderer> ReinforcementButton = nullptr;
	float4 ReinforcementButtonScale = { 106,106 };
	float4 ReinforcementButtonPos = { -370, -380 };

	void LoadTexture();
};

