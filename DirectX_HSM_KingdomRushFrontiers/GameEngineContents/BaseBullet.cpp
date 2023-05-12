#include "PrecompileHeader.h"
#include "BaseBullet.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include <GameEngineCore/GameEngineLevel.h>


BaseBullet::BaseBullet()
{

}

BaseBullet::~BaseBullet()
{
	int a = 0; // DeathCheck
}

void BaseBullet::ShootingBullet(GameEngineLevel* _Level, GameEngineActor* _ParentActor, float4& _TargetPos)
{
	std::shared_ptr<BaseBullet> Local = nullptr;
	Local = _Level->CreateActor<BaseBullet>();
	Local->SetParentPos(_ParentActor->GetTransform()->GetWorldPosition());
	Local->SetTargetPos(_TargetPos);
}

void BaseBullet::Start()
{
	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>();
	BulletRenderer->GetTransform()->SetWorldScale({10,10});
}

void BaseBullet::Update(float _DeltaTime)
{
	Time += _DeltaTime;
	Ratio = Time; //1초만에 날아감. 날아가는 시간이 고정됨 거리에 따라 투사체의 속도가 달라짐
	GetTransform()->SetWorldPosition(float4::LerpClamp(ParentPos, TargetPos, Ratio)); // 직사


	if (Ratio >= 1)
	{
		Death();
	}
}
