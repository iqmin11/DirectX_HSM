#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BaseMonster : public GameEngineActor
{
public:
	// construtor destructor
	BaseMonster();
	~BaseMonster();

	// delete Function
	BaseMonster(const BaseMonster& _Other) = delete;
	BaseMonster(BaseMonster&& _Other) noexcept = delete;
	BaseMonster& operator=(const BaseMonster& _Other) = delete;
	BaseMonster& operator=(BaseMonster&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void WalkToNextPoint(float _DeltaTime);

private:
	std::shared_ptr<class GameEngineSpriteRenderer> MonsterRenderer = nullptr;
	float4 CurPoint = {};
	float4 NextPoint = { 400,400 };
};

