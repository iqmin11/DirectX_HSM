#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class BaseFighter : public GameEngineActor
{
public:
	// construtor destructor
	BaseFighter();
	~BaseFighter();

	// delete Function
	BaseFighter(const BaseFighter& _Other) = delete;
	BaseFighter(BaseFighter&& _Other) noexcept = delete;
	BaseFighter& operator=(const BaseFighter& _Other) = delete;
	BaseFighter& operator=(BaseFighter&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;
	std::shared_ptr<class GameEngineSpriteRenderer> FighterRenderer = nullptr;
	float4 FighterRendererScale = {64,64,1};
	//std::shared_ptr<class GameEngineCollision> BodyCollision = nullptr;
	//std::shared_ptr<class GameEngineCollision> RangeCollision = nullptr;
};

