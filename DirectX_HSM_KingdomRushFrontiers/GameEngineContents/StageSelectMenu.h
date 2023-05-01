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

	float ScaleRatio = 900.f / 640.f;

	std::shared_ptr<class GameEngineSpriteRenderer> StageSelectMenuBg = nullptr;
	float4 StageSelectMenuBgScale = {1132, 640, 0 ,1};

	std::shared_ptr<GameEngineSpriteRenderer> StageSelectLoupe = nullptr;
	float4 StageSelectLoupeScale = {532, 462, 0, 1};
	float4 StageSelectLoupePos = {-580,100};

	std::shared_ptr<GameEngineSpriteRenderer> StageStartButton = nullptr;
	float4 StageStartButtonScale = { 164, 160, 0, 1 };
	float4 StageStartButtonPos = { 485,-310 };

	std::shared_ptr<GameEngineSpriteRenderer> StageThumbnail= nullptr;
	float4 StageThumbnailScale = { 338, 340, 0, 1 };
	float4 StageThumbnailPos = { -490,85 };

	std::shared_ptr<GameEngineSpriteRenderer> CampainModeButton = nullptr;
	float4 CampainModeButtonPos = { -700,-420 };
	std::shared_ptr<GameEngineSpriteRenderer> UnlockButton1 = nullptr;
	float4 UnlockButton1Pos = { -480,-420 };
	std::shared_ptr<GameEngineSpriteRenderer> UnlockButton2 = nullptr;
	float4 UnlockButton2Pos = { -260,-420 };

	float4 ModeButtonScale = { 122, 256, 0, 1 };

	std::shared_ptr<GameEngineSpriteRenderer> BackToWorldMapButton = nullptr;
	float4 BackToWorldMapButtonScale = {80, 78, 0, 1};
	float4 BackToWorldMapButtonPos = {600, 350};

	std::shared_ptr<GameEngineSpriteRenderer> StageStarBadge1 = nullptr;
	float4 StageStarBadge1Pos = { -620,360 };
	float4 StageStarBadge1Rot = {0,0,25,1};

	std::shared_ptr<GameEngineSpriteRenderer> StageStarBadge2 = nullptr;
	float4 StageStarBadge2Pos = { -570,380 };
	float4 StageStarBadge2Rot = { 0,0,15,1 };

	std::shared_ptr<GameEngineSpriteRenderer> StageStarBadge3 = nullptr;
	float4 StageStarBadge3Pos = { -517,390 };
	float4 StageStarBadge3Rot = { 0,0,0,1 };

	float4 StageStarBadgeScale = { 38, 32, 0, 1 };


};
