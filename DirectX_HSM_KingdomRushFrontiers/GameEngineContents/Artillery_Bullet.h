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
	std::shared_ptr<class GameEngineCollision> BombCol0 = nullptr;
	std::shared_ptr<class GameEngineCollision> BombCol1 = nullptr;
	std::shared_ptr<class GameEngineCollision> BombCol2 = nullptr;
	float4 ColScale0 = { 20,20,1 };
	float4 ColScale1 = { 40,40,1 };
	float4 ColScale2 = { 60,60,1 };

	void BombHit();
	void BombMiss();
	void Boom();
	int CalDamage() override;
	//void BombDeath();
};

