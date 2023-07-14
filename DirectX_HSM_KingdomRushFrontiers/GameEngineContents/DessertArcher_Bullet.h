#pragma once
#include "BaseMonsterBullet.h"

class DessertArcher_Bullet : public BaseMonsterBullet
{
public:
	// construtor destructor
	DessertArcher_Bullet();
	~DessertArcher_Bullet();

	// delete Function
	DessertArcher_Bullet(const DessertArcher_Bullet& _Other) = delete;
	DessertArcher_Bullet(DessertArcher_Bullet&& _Other) noexcept = delete;
	DessertArcher_Bullet& operator=(const DessertArcher_Bullet& _Other) = delete;
	DessertArcher_Bullet& operator=(DessertArcher_Bullet&& _Other) noexcept = delete;

	static void ShootingBullet(GameEngineLevel* _Level, class DessertArcher* _ParentActor);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ArrowRenderScale = { 20,6,1 };
	float4 ArrowColScale = { 20,6,1 };
	std::shared_ptr<class GameEngineSpriteRenderer> MissArrowRenderer = nullptr;
	float4 MissArrowRenderScale = { 16,8,1 };
	float MissTime = 0.0f;

	void ArrowHit();
	void ArrowMiss();
	int CalDamage() override;
	void MissUpdate(float _DeltaTime);
};

