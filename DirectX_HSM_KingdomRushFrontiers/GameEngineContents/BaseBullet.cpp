#include "PrecompileHeader.h"
#include "BaseBullet.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include <GameEngineCore/GameEngineLevel.h>
#include "BaseShooter.h"


BaseBullet::BaseBullet()
{

}

BaseBullet::~BaseBullet()
{

}

void BaseBullet::ShootingBullet(GameEngineLevel* _Level, GameEngineActor* _ParentActor)
{
	std::shared_ptr<BaseBullet> Bullet = nullptr;
	Bullet = _Level->CreateActor<BaseBullet>();
	Bullet->SetParentPos(_ParentActor->GetTransform()->GetWorldPosition());
	Bullet->SetTargetPos(dynamic_cast<BaseShooter*>(_ParentActor)->GetTargetPos());
	Bullet->CalBezierMid();
}

void BaseBullet::Start()
{
	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>();
}

void BaseBullet::Update(float _DeltaTime)
{
	Time += _DeltaTime;
	Ratio = Time; //1초만에 날아감. 날아가는 시간이 고정됨 거리에 따라 투사체의 속도가 달라짐
	
	//GetTransform()->SetWorldPosition(float4::LerpClamp(ParentPos, TargetPos, Ratio)); // 직사
	CalBezierBulletTransform(ParentPos, Mid0, Mid1, TargetPos, Ratio); // 곡사
	if (Ratio >= 1)
	{
		Death();
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

void BaseBullet::CalBezierBulletTransform(float4& _P0, float4& _P1, float4& _P2, float4& _P3, float _Ratio)
{
	float4 M0 = float4::LerpClamp(_P0, _P1, _Ratio);
	float4 M1 = float4::LerpClamp(_P1, _P2, _Ratio);
	float4 M2 = float4::LerpClamp(_P2, _P3, _Ratio);

	float4 B0 = float4::LerpClamp(M0, M1, _Ratio);
	float4 B1 = float4::LerpClamp(M1, M2, _Ratio);

	float4 Pos = float4::LerpClamp(B0, B1, _Ratio);
	float ZDeg = atan2(B1.y - B0.y, B1.x - B0.x) * GameEngineMath::RadToDeg;
	float4 f4Deg = float4{ 0,0,ZDeg,1 };
	GetTransform()->SetWorldPosition(Pos);
	GetTransform()->SetWorldRotation(f4Deg);
}
