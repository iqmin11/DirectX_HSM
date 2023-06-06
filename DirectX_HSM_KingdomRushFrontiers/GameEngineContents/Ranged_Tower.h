#pragma once
#include "BaseShootingTower.h"

class Ranged_Tower : public BaseShootingTower
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
	void ChangeTower(TowerEnum _Tower) override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderScale = { 128, 128, 1 };

	std::shared_ptr<class Ranged_Shooter> Shooter0 = nullptr;
	std::shared_ptr<class Ranged_Shooter> Shooter1 = nullptr;
	
	bool AttackOrder = false;

	float Time = 0.0f;
	void ChangeTowerRender(int _TowerLevel);
	void ChangeShooter(int _TowerLevel);

	void RangerAttack();

public:
	static const float4 Lv1Shooter0LocalPos;
	static const float4 Lv1Shooter1LocalPos;
	static const float4 Lv2Shooter0LocalPos;
	static const float4 Lv2Shooter1LocalPos;
	static const float4 Lv3Shooter0LocalPos;
	static const float4 Lv3Shooter1LocalPos;
	static const float4 Lv4Shooter0LocalPos;
	static const float4 Lv4Shooter1LocalPos;
};
