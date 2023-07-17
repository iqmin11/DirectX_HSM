#pragma once
#include "BaseShootingTower.h"

class CityTower : public BaseShootingTower
{
public:
	// construtor destructor
	CityTower();
	~CityTower();

	// delete Function
	CityTower(const CityTower& _Other) = delete;
	CityTower(CityTower&& _Other) noexcept = delete;
	CityTower& operator=(const CityTower& _Other) = delete;
	CityTower& operator=(CityTower&& _Other) noexcept = delete;

	static std::shared_ptr<CityTower> CreateTower(GameEngineActor* _Parent, const float4& _Pos);

	void ChangeTower(TowerEnum _Tower) {};

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderScale = { 128, 128, 1 };
	std::shared_ptr<class Ranged_Shooter> Shooter = nullptr;
	float Time = 100.f;

	void RangerAttack();

};

