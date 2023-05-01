#pragma once
#include <GameEngineCore/GameEngineActor.h>

class WorldMap : public GameEngineActor
{
public:
	// construtor destructor
	WorldMap();
	~WorldMap();

	// delete Function
	WorldMap(const WorldMap& _Other) = delete;
	WorldMap(WorldMap&& _Other) noexcept = delete;
	WorldMap& operator=(const WorldMap& _Other) = delete;
	WorldMap& operator=(WorldMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	float4 ActorPos = float4::Zero;
	
	float4 WorldMapBgScale = {1280, 1080};
	float ScaleRatio = 900.f / 1020.0f;
	//float ScaleRatio = 720.0f / 1020.0f;
	std::shared_ptr<class GameEngineSpriteRenderer> WorldMapBg = nullptr;

	std::string FlagImageName = "MapFlag0020.png";

	std::shared_ptr<GameEngineSpriteRenderer> Stage1Flag = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Stage2Flag = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Stage3Flag = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Stage4Flag = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Stage5Flag = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Stage6Flag = nullptr;

	float4 Stage1FlagPos = {-230, 255};
	float4 Stage2FlagPos = {-120, 227};
	float4 Stage3FlagPos = {-100, 120};
	float4 Stage4FlagPos = {-235, 87};
	float4 Stage5FlagPos = {-388, 5};
	float4 Stage6FlagPos = {-165, -178};

	float4 FlagScale = {256,256};

	std::shared_ptr<class GameEngineSpriteRenderer> Stage1to2Road = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Stage2to3Road = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Stage3to4Road = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Stage4to5Road = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Stage5to6Road = nullptr;
	
	float4 Stage1to2RoadPos = {-172, 185};
	float4 Stage2to3RoadPos = {-80,115};
	float4 Stage3to4RoadPos = {-160,40};
	float4 Stage4to5RoadPos = {-320, 0};
	float4 Stage5to6RoadPos = {-312, -165};
	
	float4 Stage1to2RoadScale = {72,28};	
	float4 Stage2to3RoadScale = {48,104};
	float4 Stage3to4RoadScale = {102,34};
	float4 Stage4to5RoadScale = {140,70};
	float4 Stage5to6RoadScale = {296,212};

	std::shared_ptr<GameEngineSpriteRenderer> StarContainer = nullptr;
	float4 StarContainerScale = {166, 50};
	float4 StarContainerPos = {460,400};

	std::shared_ptr<GameEngineSpriteRenderer> UpgradeButton = nullptr;
	float4 UpgradeButtonScale = {148, 116};
	float4 UpgradeButtonPos = { 470,-390 };

	std::shared_ptr<GameEngineSpriteRenderer> HomeButton = nullptr;
	float4 HomeButtonScale = {66,60};
	float4 HomeButtonPos = { -520,-410 };
};

