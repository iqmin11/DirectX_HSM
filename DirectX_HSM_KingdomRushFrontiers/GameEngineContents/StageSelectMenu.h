#pragma once
#include <GameEngineCore/GameEngineActor.h>

class StageSelectMenu : public GameEngineActor
{
public:
	// construtor destructor
	StageSelectMenu();
	~StageSelectMenu();

	// delete Function
	StageSelectMenu(const StageSelectMenu& _Other) = delete;
	StageSelectMenu(StageSelectMenu&& _Other) noexcept = delete;
	StageSelectMenu& operator=(const StageSelectMenu& _Other) = delete;
	StageSelectMenu& operator=(StageSelectMenu&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;

	float ScaleRatio = 720.f / 640.f;

	std::shared_ptr<class GameEngineSpriteRenderer> StageSelectMenuBg = nullptr;
	float4 StageSelectMenuBgScale = {1132, 640, 0 ,1};

	std::shared_ptr<GameEngineSpriteRenderer> StageSelectLoupe = nullptr;
	float4 StageSelectLoupeScale = {532, 462, 0, 1};
	float4 StageSelectLoupePos = {-385,80};

	std::shared_ptr<GameEngineSpriteRenderer> StageStartButton = nullptr;
	float4 StageStartButtonScale = { 164, 160, 0, 1 };
	float4 StageStartButtonPos = { 385,-260 };

	std::shared_ptr<GameEngineSpriteRenderer> StageThumbnail= nullptr;
	float4 StageThumbnailScale = { 338, 340, 0, 1 };
	float4 StageThumbnailPos = { -310,75 };

	std::shared_ptr<GameEngineSpriteRenderer> CampainModeButton = nullptr;
	float4 CampainModeButtonPos = { -550,-320 };
	std::shared_ptr<GameEngineSpriteRenderer> UnlockButton1 = nullptr;
	float4 UnlockButton1Pos = { -370,-320 };
	std::shared_ptr<GameEngineSpriteRenderer> UnlockButton2 = nullptr;
	float4 UnlockButton2Pos = { -190,-320 };

	float4 ModeButtonScale = { 122, 256, 0, 1 };

	std::shared_ptr<GameEngineSpriteRenderer> BackToWorldMapButton = nullptr;
	float4 BackToWorldMapButtonScale = {80, 78, 0, 1};
	float4 BackToWorldMapButtonPos = {460, 270};

	std::shared_ptr<GameEngineSpriteRenderer> StageStarBadge1 = nullptr;
	float4 StageStarBadge1Pos = { -420,287 };
	float4 StageStarBadge1Rot = {0,0,30,1};

	std::shared_ptr<GameEngineSpriteRenderer> StageStarBadge2 = nullptr;
	float4 StageStarBadge2Pos = { -380,305 };
	float4 StageStarBadge2Rot = { 0,0,15,1 };

	std::shared_ptr<GameEngineSpriteRenderer> StageStarBadge3 = nullptr;
	float4 StageStarBadge3Pos = { -337,314 };
	float4 StageStarBadge3Rot = { 0,0,0,1 };

	float4 StageStarBadgeScale = { 38, 32, 0, 1 };


};
