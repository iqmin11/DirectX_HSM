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

	static void ShootingBullet(GameEngineLevel* _Level, class BaseShooter* _ParentShooter);

protected:
	void Start() override;

private:
	float4 BoltRenderScale = { 64,64,1 };
	float4 BoltColScale = { 6,6 };
	void BoltHit();
	void BoltMiss();

	int CalDamage() override;
};

