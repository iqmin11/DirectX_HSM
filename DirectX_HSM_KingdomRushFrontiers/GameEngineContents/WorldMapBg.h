#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"

class WorldMapBg : public GameEngineActor
{
public:
	// construtor destructor
	WorldMapBg();
	~WorldMapBg();

	// delete Function
	WorldMapBg(const WorldMapBg& _Other) = delete;
	WorldMapBg(WorldMapBg&& _Other) noexcept = delete;
	WorldMapBg& operator=(const WorldMapBg& _Other) = delete;
	WorldMapBg& operator=(WorldMapBg&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<class GameEngineUIRenderer> BgRenderer = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> EdgeFade = nullptr;
	float4 Scale = {1600,900,1};
	float4 EdgeFadeScale = {1620,911,1};
};

