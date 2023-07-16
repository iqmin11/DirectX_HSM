#pragma once
#include "BaseMonsterBullet.h"
class SandWraith_Bullet : public BaseMonsterBullet
{
public:
	// construtor destructor
	SandWraith_Bullet();
	~SandWraith_Bullet();

	// delete Function
	SandWraith_Bullet(const SandWraith_Bullet& _Other) = delete;
	SandWraith_Bullet(SandWraith_Bullet&& _Other) noexcept = delete;
	SandWraith_Bullet& operator=(const SandWraith_Bullet& _Other) = delete;
	SandWraith_Bullet& operator=(SandWraith_Bullet&& _Other) noexcept = delete;

	static void ShootingBullet(GameEngineLevel* _Level, class SandWraith* _ParentActor);

protected:
	void Start() override;

private:
	float4 BoltRenderScale = { 64,64,1 };
	float4 BoltColScale = { 6,6 };

	void BoltHit();
	void BoltMiss();
	int CalDamage() override;
};

