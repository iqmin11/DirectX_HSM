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

	static void ShootingBullet(GameEngineLevel* _Level, GameEngineActor* _ParentActor, TowerData* _Data);

protected:
	void Start() override;

private:

};

