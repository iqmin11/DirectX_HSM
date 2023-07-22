#pragma once
#include "BaseBullet.h"

class Ranged_Bullet : public BaseBullet
{
public:
	// construtor destructor
	Ranged_Bullet();
	~Ranged_Bullet();

	// delete Function
	Ranged_Bullet(const Ranged_Bullet& _Other) = delete;
	Ranged_Bullet(Ranged_Bullet&& _Other) noexcept = delete;
	Ranged_Bullet& operator=(const Ranged_Bullet& _Other) = delete;
	Ranged_Bullet& operator=(Ranged_Bullet&& _Other) noexcept = delete;

	static void ShootingBullet(GameEngineLevel* _Level, class BaseShooter* _ParentActor);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ArrowRenderScale = { 20,6,1 };
	float4 ArrowColScale = { 20,6,1 };
	std::shared_ptr<class GameEngineSpriteRenderer> MissArrowRenderer = nullptr;
	float4 MissArrowRenderScale = { 16,8,1 };
	float MissTime = 0.0f;

	static GameEngineSoundPlayer ArrowSound;
	std::vector<std::string> ArrowHitSoundNames = std::vector<std::string>();

	void ArrowHit();
	void ArrowMiss();
	int CalDamage() override;
	void MissUpdate(float _DeltaTime);
	void PlayArrowSound(const std::string_view& _Name);
	void PlayArrowHitSound();
};

