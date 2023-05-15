#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsData.h"

class BaseTower : public GameEngineActor
{
public:
	// construtor destructor
	BaseTower();
	~BaseTower();

	// delete Function
	BaseTower(const BaseTower& _Other) = delete;
	BaseTower(BaseTower&& _Other) noexcept = delete;
	BaseTower& operator=(const BaseTower& _Other) = delete;
	BaseTower& operator=(BaseTower&& _Other) noexcept = delete;

protected:
	TowerData Data = {};
	std::shared_ptr<class GameEngineSpriteRenderer> TowerRenderer = nullptr;
	float4 ActorPos = float4::Zero;
	std::shared_ptr<class GameEngineSpriteRenderer> TowerRangeRender = nullptr;

	void Start() override;

private:
	float4 TestTargetPos = { 200, 200 };
};

