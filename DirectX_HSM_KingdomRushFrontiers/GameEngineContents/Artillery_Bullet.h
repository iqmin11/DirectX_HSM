#pragma once
#include "BaseBullet.h"

class Artillery_Bullet : public BaseBullet
{
public:
	// construtor destructor
	Artillery_Bullet();
	~Artillery_Bullet();

	// delete Function
	Artillery_Bullet(const Artillery_Bullet& _Other) = delete;
	Artillery_Bullet(Artillery_Bullet&& _Other) noexcept = delete;
	Artillery_Bullet& operator=(const Artillery_Bullet& _Other) = delete;
	Artillery_Bullet& operator=(Artillery_Bullet&& _Other) noexcept = delete;
	
	static void ShootingBullet(GameEngineLevel* _Level, class BaseShootingTower* _ParentTower);

protected:
	void Start() override;

private:
	float4 BulletRenderScale = {26,18};
	float4 BulletColScale = {26,18};

	void BombHit();
	void BombMiss();
	int CalDamage() override;
	//void BombDeath();
};

