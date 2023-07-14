#include "PrecompileHeader.h"
#include "BaseMonsterBullet.h"

#include <GameEngineCore\GameEngineSpriteRenderer.h>
#include <GameEngineCore\GameEngineCollision.h>
#include "BaseFighter.h"

BaseMonsterBullet::BaseMonsterBullet()
{

}

BaseMonsterBullet::~BaseMonsterBullet()
{

}

void BaseMonsterBullet::CalBezierMid()
{
	Mid0.x = ParentPos.x + ((TargetPos.x - ParentPos.x) / 4);
	Mid0.y = max(TargetPos.y, ParentPos.y) + 150.f;
	Mid0.z = ParentPos.z + ((TargetPos.z - ParentPos.z) / 4);

	Mid1.x = TargetPos.x - ((TargetPos.x - ParentPos.x) / 4);
	Mid1.y = max(TargetPos.y, ParentPos.y) + 150.f;
	Mid1.z = ParentPos.z + ((TargetPos.z - ParentPos.z) / 4);
}

void BaseMonsterBullet::Start()
{
	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	BulletCol = CreateComponent<GameEngineCollision>(ColOrder::Bullet);
}

void BaseMonsterBullet::Update(float _DeltaTime)
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
			CalLerpBulletTransform(ParentPos, TargetPos, Ratio); // ����
		}

		if (IsThereTargetFighter() && IsHitTargetFighter()) // ����
		{
			HitFunc();
		}
	}

	if (IsMissTargetFighter()) // ������
	{
		MissFunc();
		AmIMiss = true;
	}
}

void BaseMonsterBullet::CalBezierBulletTransform(const float4& _P0, const float4& _P1, const float4& _P2, const float4& _P3, float _Ratio)
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

void BaseMonsterBullet::CalLerpBulletTransform(const float4& _P0, const float4& _P3, float _Ratio)
{
	float4 Pos = float4::LerpClamp(_P0, _P3, _Ratio);
	float ZDeg = atan2(_P3.y - _P0.y, _P3.x - _P0.x) * GameEngineMath::RadToDeg;
	float4 f4Deg = float4{ 0,0,ZDeg,1 };
	GetTransform()->SetWorldPosition(Pos);
	GetTransform()->SetWorldRotation(f4Deg);
}

void BaseMonsterBullet::CalRotBulletRot(const float4& _P0, const float4& _P3, float _Ratio)
{
	float4 f4Deg = float4::LerpClamp({ 0.f,0.f,0.f,1 }, { 0.f,0.f,640.f,1 }, _Ratio);
	if (_P3.x - _P0.x > 0)
	{
		GetTransform()->SetWorldRotation(-f4Deg);
	}
	else
	{
		GetTransform()->SetWorldRotation(f4Deg);
	}
}

void BaseMonsterBullet::MissFunc()
{
	IsBulletDeath = true;
	if (BulletMiss != nullptr)
	{
		BulletMiss();
		return;
	}
	Death();
}

void BaseMonsterBullet::HitFunc()
{
	IsBulletDeath = true;
	if (BulletHit != nullptr)
	{
		BulletHit();
		return;
	}
	Death();
}

bool BaseMonsterBullet::IsThereTargetFighter()
{
	return TargetFighter != nullptr;
}

bool BaseMonsterBullet::IsHitTargetFighter()
{
	return Ratio >= 1 && BulletCol->GetTransform()->Collision({ ._OtherTrans = TargetFighter->GetFighterCol()->GetTransform(), .ThisType = ColType::AABBBOX2D, .OtherType = ColType::SPHERE2D });
}

bool BaseMonsterBullet::IsMissTargetFighter()
{
	return Ratio >= 1 && !IsBulletDeath;
}
