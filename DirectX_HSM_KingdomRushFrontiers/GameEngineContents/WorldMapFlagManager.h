#pragma once
#include <GameEngineCore\GameEngineActor.h>

class WorldMapFlagManager : public GameEngineActor
{
public:
	// construtor destructor
	WorldMapFlagManager();
	~WorldMapFlagManager();

	// delete Function
	WorldMapFlagManager(const WorldMapFlagManager& _Other) = delete;
	WorldMapFlagManager(WorldMapFlagManager&& _Other) noexcept = delete;
	WorldMapFlagManager& operator=(const WorldMapFlagManager& _Other) = delete;
	WorldMapFlagManager& operator=(WorldMapFlagManager&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::vector<float4> FlagPosData = std::vector<float4>();
	std::vector<std::vector<float4>> PathDotPosData = std::vector<std::vector<float4>>(); //Stage, Dot
	std::vector<std::shared_ptr<class WorldMapFlag>> Flags = std::vector<std::shared_ptr<class WorldMapFlag>>();
	std::vector<std::vector<std::shared_ptr<class PathDot>>> WorldMapPath = std::vector<std::vector<std::shared_ptr<class PathDot>>>();

	float4 WinToDec(const float4& _Win);
	void SetFlagPosData();
	void SetFlag();
	void SetPathPosData();
	void SetPathDot();
	void SetOnePathDot(int _Index);
};

