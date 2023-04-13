#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class WorldMapLevel : public GameEngineLevel
{
public:
	// construtor destructor
	WorldMapLevel();
	~WorldMapLevel();

	// delete Function
	WorldMapLevel(const WorldMapLevel& _Other) = delete;
	WorldMapLevel(WorldMapLevel&& _Other) noexcept = delete;
	WorldMapLevel& operator=(const WorldMapLevel& _Other) = delete;
	WorldMapLevel& operator=(WorldMapLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

