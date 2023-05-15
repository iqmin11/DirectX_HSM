#pragma once
#include "BaseTower.h"

class Ranged_Tower : public BaseTower
{
public:
	// construtor destructor
	Ranged_Tower();
	~Ranged_Tower();

	// delete Function
	Ranged_Tower(const Ranged_Tower& _Other) = delete;
	Ranged_Tower(Ranged_Tower&& _Other) noexcept = delete;
	Ranged_Tower& operator=(const Ranged_Tower& _Other) = delete;
	Ranged_Tower& operator=(Ranged_Tower&& _Other) noexcept = delete;

	static std::shared_ptr<Ranged_Tower> CreateTower(GameEngineLevel* _Level, const float4& _BuildPos);

protected:
	void Start() override;

private:
	float4 RenderScale = { 128, 128 };
	float TowerRange = 160.f;

	std::shared_ptr<class Ranged_Shooter> Shooter0 = nullptr;
	std::shared_ptr<class Ranged_Shooter> Shooter1 = nullptr;


};

