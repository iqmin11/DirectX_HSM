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
	void Update(float _DeltaTime) override;

private:
	float4 BulletRenderScale = {26,18,1};
	float4 BulletColScale = {0,0,0};
	std::shared_ptr<class GameEngineCollision> BombCol0 = nullptr;
	std::shared_ptr<class GameEngineCollision> BombCol1 = nullptr;
	std::shared_ptr<class GameEngineCollision> BombCol2 = nullptr;
	float4 ColScale0 = { 20,20,1 };
	float4 ColScale1 = { 40,40,1 };
	float4 ColScale2 = { 60,60,1 };

	std::shared_ptr<class GameEngineSpriteRenderer> ExplosionSmokeRender = nullptr;
	float4 ExplosionSmokeRenderScale = { 256,256,1 };
	std::shared_ptr<class GameEngineSpriteRenderer> BombDecalRender = nullptr;
	float4 BombDecalRenderScale = { 52, 26, 1 };

	bool IsBoom = false;
	float BoomTime = 0.0f;

	void BombHit();
	void BombMiss();
	void Boom();
	void BoomUpdate(float _DeltaTime);
	int CalDamage() override;
	//void BombDeath();
};

