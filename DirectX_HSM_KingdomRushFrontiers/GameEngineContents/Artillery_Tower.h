#pragma once
#include "BaseShootingTower.h"

class Artillery_Tower : public BaseShootingTower
{
public:
	// construtor destructor
	Artillery_Tower();
	~Artillery_Tower();

	// delete Function
	Artillery_Tower(const Artillery_Tower& _Other) = delete;
	Artillery_Tower(Artillery_Tower&& _Other) noexcept = delete;
	Artillery_Tower& operator=(const Artillery_Tower& _Other) = delete;
	Artillery_Tower& operator=(Artillery_Tower&& _Other) noexcept = delete;
	
	static std::shared_ptr<Artillery_Tower> CreateTower(GameEngineLevel* _Level, const float4& _BuildPos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	float4 RenderScale = { 256, 256 };
	float Time = 0.0f;

	void ChangeTower(TowerEnum _Tower);
	void ChangeTowerRender(int _TowerLevel);
	void ArtilleryAttack();
};
