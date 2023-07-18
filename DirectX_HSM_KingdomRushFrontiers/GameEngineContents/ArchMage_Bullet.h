#pragma once
#include "BaseBullet.h"

class ArchMage_Bullet : public BaseBullet
{
public:
	// construtor destructor
	ArchMage_Bullet();
	~ArchMage_Bullet();

	// delete Function
	ArchMage_Bullet(const ArchMage_Bullet& _Other) = delete;
	ArchMage_Bullet(ArchMage_Bullet&& _Other) noexcept = delete;
	ArchMage_Bullet& operator=(const ArchMage_Bullet& _Other) = delete;
	ArchMage_Bullet& operator=(ArchMage_Bullet&& _Other) noexcept = delete;

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

