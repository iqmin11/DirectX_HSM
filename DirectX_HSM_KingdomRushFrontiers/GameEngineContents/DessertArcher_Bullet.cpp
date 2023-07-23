#include "PrecompileHeader.h"
#include "DessertArcher_Bullet.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BaseFighter.h"
#include "DessertArcher.h"

GameEngineSoundPlayer DessertArcher_Bullet::HitArrowSound;

DessertArcher_Bullet::DessertArcher_Bullet()
{

}

DessertArcher_Bullet::~DessertArcher_Bullet()
{

}

void DessertArcher_Bullet::ShootingBullet(GameEngineLevel* _Level, DessertArcher* _ParentActor)
{
	std::shared_ptr<DessertArcher_Bullet> Bullet = nullptr;
	Bullet = _Level->CreateActor<DessertArcher_Bullet>();
	Bullet->SetParentPos(_ParentActor->GetTransform()->GetWorldPosition());
	Bullet->SetTargetPos(_ParentActor->GetRangeTargetPos());
	Bullet->CalBezierMid();
	Bullet->IsBezier = true;
	Bullet->BulletTime = _ParentActor->GetBulletTime();
	Bullet->TargetFighter = _ParentActor->GetRangeTargetFighter();
	Bullet->Data = _ParentActor->GetData();
}

void DessertArcher_Bullet::Start()
{
	BaseMonsterBullet::Start();
	BulletRenderer->GetTransform()->SetWorldScale(ArrowRenderScale);
	BulletRenderer->SetTexture("arrow.png");
	BulletCol->GetTransform()->SetWorldScale(ArrowColScale);
	BulletHit = std::bind(&DessertArcher_Bullet::ArrowHit, this);
	BulletMiss = std::bind(&DessertArcher_Bullet::ArrowMiss, this);
	MissArrowRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	MissArrowRenderer->SetTexture("decal_arrow.png");
	MissArrowRenderer->GetTransform()->SetWorldScale(MissArrowRenderScale);
	MissArrowRenderer->Off();
}

void DessertArcher_Bullet::Update(float _DeltaTime)
{
	BaseMonsterBullet::Update(_DeltaTime);
	if (AmIMiss)
	{
		MissUpdate(_DeltaTime);
	}
}

void DessertArcher_Bullet::ArrowHit()
{
	Death();
	TargetFighter->CurHP -= CalDamage();

	if (HitArrowSound.IsValid())
	{
		bool Value = false;
		HitArrowSound.isPlaying(&Value);
		if (Value)
		{
			return;
		}
	}
	HitArrowSound = GameEngineSound::Play("Sound_ArrowHit2" + std::to_string(GameEngineRandom::MainRandom.RandomInt(2, 3)) + ".ogg");
	HitArrowSound.SetVolume(0.2f);
}

void DessertArcher_Bullet::ArrowMiss()
{
	BulletRenderer->Off();
	MissArrowRenderer->On();
}

int DessertArcher_Bullet::CalDamage()
{
	return BaseMonsterBullet::CalDamage();
}

void DessertArcher_Bullet::MissUpdate(float _DeltaTime)
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
