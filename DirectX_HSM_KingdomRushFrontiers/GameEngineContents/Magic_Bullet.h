#pragma once
#include "BaseBullet.h"

class Magic_Bullet : public BaseBullet
{
public:
	// construtor destructor
	Magic_Bullet();
	~Magic_Bullet();

	// delete Function
	Magic_Bullet(const Magic_Bullet& _Other) = delete;
	Magic_Bullet(Magic_Bullet&& _Other) noexcept = delete;
	Magic_Bullet& operator=(const Magic_Bullet& _Other) = delete;
	Magic_Bullet& operator=(Magic_Bullet&& _Other) noexcept = delete;

	static void ShootingBullet(GameEngineLevel* _Level, GameEngineActor* _ParentActor, TowerData* _Data);

protected:
	void Start() override;

private:
	float4 BulletScale = float4::Zero;
	void BoltDeath();
};

