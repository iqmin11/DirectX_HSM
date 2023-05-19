#pragma once
#include "BaseShootingTower.h"

class Magic_Tower : public BaseShootingTower
{
public:
	// construtor destructor
	Magic_Tower();
	~Magic_Tower();

	// delete Function
	Magic_Tower(const Magic_Tower& _Other) = delete;
	Magic_Tower(Magic_Tower&& _Other) noexcept = delete;
	Magic_Tower& operator=(const Magic_Tower& _Other) = delete;
	Magic_Tower& operator=(Magic_Tower&& _Other) noexcept = delete;

	static std::shared_ptr<Magic_Tower> CreateTower(GameEngineLevel* _Level, const float4& _BuildPos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	float4 RenderScale = { 128, 128 };
	std::shared_ptr<class Magic_Shooter> Shooter = nullptr;
	float Time = 0.0f;
	void ChangeTower(TowerEnum _Tower);
	void ChangeTowerRender(int _TowerLevel);
	void ChangeShooter(int _TowerLevel);
	
	void MagicAttack();
public:
	static const float4 Lv1ShooterLocalPos;
	static const float4 Lv2ShooterLocalPos;
	static const float4 Lv3ShooterLocalPos;
	static const float4 Lv4ShooterLocalPos;

};

