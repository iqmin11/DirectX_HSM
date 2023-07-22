#include "PrecompileHeader.h"
#include "Ranged_Bullet.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BaseMonster.h"
#include "BaseShootingTower.h"
#include "Ranged_Shooter.h"

GameEngineSoundPlayer Ranged_Bullet::ArrowSound = GameEngineSoundPlayer();

Ranged_Bullet::Ranged_Bullet()
{

}

Ranged_Bullet::~Ranged_Bullet()
{

}

void Ranged_Bullet::Start()
{
	BaseBullet::Start();
	BulletRenderer->GetTransform()->SetWorldScale(ArrowRenderScale);
	BulletRenderer->SetTexture("arrow.png");
	BulletCol->GetTransform()->SetWorldScale(ArrowColScale);
	BulletHit = std::bind(&Ranged_Bullet::ArrowHit, this);
	BulletMiss = std::bind(&Ranged_Bullet::ArrowMiss, this);
	MissArrowRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	MissArrowRenderer->SetTexture("decal_arrow.png");
	MissArrowRenderer->GetTransform()->SetWorldScale(MissArrowRenderScale);
	MissArrowRenderer->Off();

	ArrowHitSoundNames.resize(2);
	ArrowHitSoundNames[0] = "Sound_ArrowHit2.ogg";
	ArrowHitSoundNames[1] = "Sound_ArrowHit3.ogg";
}

void Ranged_Bullet::Update(float _DeltaTime)
{
	BaseBullet::Update(_DeltaTime);
	if (AmIMiss)
	{
		MissUpdate(_DeltaTime);
	}
}

void Ranged_Bullet::ArrowHit()
{
	Death();
	TargetMonster->Hit = HitState::Arrow;
	TargetMonster->CurHP -= CalDamage();
	PlayArrowHitSound();
}

void Ranged_Bullet::ArrowMiss()
{
	BulletRenderer->Off();
	MissArrowRenderer->On();
}

int Ranged_Bullet::CalDamage()
{
	return BaseBullet::CalDamage();
}

void Ranged_Bullet::MissUpdate(float _DeltaTime)
{
	MissTime += _DeltaTime;
	if (2.f >= MissTime)
	{
		MissArrowRenderer->ColorOptionValue.MulColor.a -= _DeltaTime / 2;
	}
	else
	{
		Death();
	}
}

void Ranged_Bullet::PlayArrowSound(const std::string_view& _Name)
{
	if (ArrowSound.IsValid())
	{
		bool BoolValue = false;
		ArrowSound.isPlaying(&BoolValue);
		if (BoolValue)
		{
			return;
		}
	}
	ArrowSound = GameEngineSound::Play(_Name);
	ArrowSound.SetVolume(0.1f);
}

void Ranged_Bullet::PlayArrowHitSound()
{
	PlayArrowSound(ArrowHitSoundNames[GameEngineRandom::MainRandom.RandomInt(0, 1)]);
}

void Ranged_Bullet::ShootingBullet(GameEngineLevel* _Level, BaseShooter* _ParentShooter)
{
	std::shared_ptr<Ranged_Bullet> Bullet = nullptr;
	Bullet = _Level->CreateActor<Ranged_Bullet>();
	Bullet->SetParentPos(_ParentShooter->GetTransform()->GetWorldPosition());
	Bullet->SetTargetPos(_ParentShooter->GetTargetPos());
	Bullet->CalBezierMid();
	Bullet->IsBezier = true;
	Bullet->BulletTime = _ParentShooter->GetParentTower()->GetData().BulletTime;
	Bullet->TargetMonster = _ParentShooter->GetParentTower()->GetTargetMonster();
	Bullet->Data = _ParentShooter->GetParentTower()->GetData();
}