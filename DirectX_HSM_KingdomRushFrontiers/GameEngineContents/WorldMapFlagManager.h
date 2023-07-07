#pragma once
#include <GameEngineCore\GameEngineActor.h>

class WorldMapFlagManager : public GameEngineActor
{
public:
	static WorldMapFlagManager* MainFlagManager;

	// construtor destructor
	WorldMapFlagManager();
	~WorldMapFlagManager();

	// delete Function
	WorldMapFlagManager(const WorldMapFlagManager& _Other) = delete;
	WorldMapFlagManager(WorldMapFlagManager&& _Other) noexcept = delete;
	WorldMapFlagManager& operator=(const WorldMapFlagManager& _Other) = delete;
	WorldMapFlagManager& operator=(WorldMapFlagManager&& _Other) noexcept = delete;

	void OnStage(int _Index);

	std::vector<std::shared_ptr<class WorldMapFlag>>& GetFlags()
	{
		return Flags;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

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

