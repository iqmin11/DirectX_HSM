#include "PrecompileHeader.h"
#include "BaseBullet.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseShooter.h"
#include "BaseMonster.h"


BaseBullet::BaseBullet()
{

}

BaseBullet::~BaseBullet()
{

}

void BaseBullet::Start()
{
	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>();
	BulletCol = CreateComponent<GameEngineCollision>(ColOrder::Bullet);
	BulletCol->GetTransform()->SetWorldScale({ 3,3 });
}

void BaseBullet::Update(float _DeltaTime)
{
	if (!IsBulletDeath)
	{
		Time += _DeltaTime;
		Ratio = Time / BulletTime; //1�ʸ��� ���ư�. ���ư��� �ð��� ������ �Ÿ��� ���� ����ü�� �ӵ��� �޶���

		if (IsBezier)
		{
			CalBezierBulletTransform(ParentPos, Mid0, Mid1, TargetPos, Ratio); // ���
		}
		else
		{
			CalLerpBulletTransform(ParentPos, TargetPos, Ratio);
		}

		if (IsThereTargetMonster() && IsHitTargetMonster())
		{
			TargetMonster->CurHP -= CalDamage();
			DeathFunc();
		}
	}

	if (Ratio >= 1 && !IsBulletDeath) // ������(��Ÿ����� ���� �ݸ����� �浹���� ����)
	{
		DeathFunc();
	}

}

void BaseBullet::CalBezierMid()
{
	//Mid = { 0,400 };

	Mid0.x = ParentPos.x + ((TargetPos.x - ParentPos.x) / 4);
	Mid0.y = max(TargetPos.y, ParentPos.y) + 150.f;

	Mid1.x = TargetPos.x - ((TargetPos.x - ParentPos.x) / 4);
	Mid1.y = max(TargetPos.y, ParentPos.y) + 150.f;
}

void BaseBullet::CalBezierBulletTransform(const float4& _P0, const float4& _P1, const float4& _P2, const float4& _P3, float _Ratio)
{
	float4 M0 = float4::LerpClamp(_P0, _P1, _Ratio);
	float4 M1 = float4::LerpClamp(_P1, _P2, _Ratio);
	float4 M2 = float4::LerpClamp(_P2, _P3, _Ratio);

	float4 B0 = float4::LerpClamp(M0, M1, _Ratio);
	float4 B1 = float4::LerpClamp(M1, M2, _Ratio);


	float4 Pos = float4::LerpClamp(B0, B1, _Ratio);
	GetTransform()->SetWorldPosition(Pos);
	if (IsRot)
	{
		CalRotBulletRot(_P0, _P3, _Ratio);
		return;
	}
	float ZDeg = atan2(B1.y - B0.y, B1.x - B0.x) * GameEngineMath::RadToDeg;
	float4 f4Deg = float4{ 0,0,ZDeg,1 };
	GetTransform()->SetWorldRotation(f4Deg);
}

void BaseBullet::CalLerpBulletTransform(const float4& _P0, const float4& _P3, float _Ratio)
{
	float4 Pos = float4::LerpClamp(_P0, _P3, _Ratio);
	float ZDeg = atan2(_P3.y - _P0.y, _P3.x - _P0.x) * GameEngineMath::RadToDeg;
	float4 f4Deg = float4{ 0,0,ZDeg,1 };
	GetTransform()->SetWorldPosition(Pos);
	GetTransform()->SetWorldRotation(f4Deg);
}

void BaseBullet::CalRotBulletRot(const float4& _P0, const float4& _P3, float _Ratio)
{
	float4 f4Deg = float4::LerpClamp({ 0.f,0.f,0.f,1 }, { 0.f,0.f,640.f,1 }, _Ratio);;
	if (_P3.x - _P0.x  > 0)
	{
		GetTransform()->SetWorldRotation(-f4Deg);
	}
	else
	{
		GetTransform()->SetWorldRotation(f4Deg);
	}
}

void BaseBullet::DeathFunc()
{
	IsBulletDeath = true;
	if (BulletDeath != nullptr)
	{
		BulletDeath();
		return;
	}
	Death();
}

int BaseBullet::CalDamage() //������ ��� ���� ���߿� �� ��������..
{
	return GameEngineRandom::MainRandom.RandomInt(Data->Damage_min, Data->Damage_MAX);
}

bool BaseBullet::IsThereTargetMonster()
{
	return TargetMonster != nullptr;
}

bool BaseBullet::IsHitTargetMonster()
{
	return BulletCol->GetTransform()->Collision({ ._OtherTrans = TargetMonster->GetMonsterCol()->GetTransform(), .ThisType = ColType::AABBBOX2D, .OtherType = ColType::AABBBOX2D });
}



