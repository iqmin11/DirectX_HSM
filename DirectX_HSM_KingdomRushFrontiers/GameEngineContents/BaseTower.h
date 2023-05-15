#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

	static std::shared_ptr<BaseTower> CreateTower(GameEngineLevel* _Level , const float4& _BuildPos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;
	std::shared_ptr<class GameEngineSpriteRenderer> TowerRenderer = nullptr;
	float4 RenderScale = {128, 128};
	float4 TestTargetPos = { 200, 200 };

	float TowerRange = 160.f;
	
	std::shared_ptr<class GameEngineSpriteRenderer> TowerRangeRender = nullptr;

	std::shared_ptr<class BaseShooter> Shooter0 = nullptr;
	std::shared_ptr<class BaseShooter> Shooter1 = nullptr;

};

