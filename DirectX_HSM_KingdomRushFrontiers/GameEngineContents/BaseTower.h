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
	void Start() override;
	float4 ActorPos = float4::Zero;

protected:
	TowerData Data = {};
	std::shared_ptr<class GameEngineSpriteRenderer> TowerAreaRenderer = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> TowerRenderer = nullptr;
private:

};

