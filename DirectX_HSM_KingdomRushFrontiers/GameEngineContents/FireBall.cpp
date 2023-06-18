#include "PrecompileHeader.h"
#include "FireBall.h"

#include <GameEngineBase\GameEngineRandom.h>
#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore\GameEngineSpriteRenderer.h>
#include <GameEngineCore\GameEngineCollision.h>
#include "BaseMonster.h"
#include "FireBallSmoke.h"
#include "FireBallExplosion.h"

FireBall::FireBall()
{

}

FireBall::~FireBall()
{
	float4 LocTargetPos = TargetPos;
}

void FireBall::SummonFireBall(GameEngineLevel* _Level, float4 _TargetPos)
{
	std::weak_ptr<FireBall> LocFireBall(_Level->CreateActor<FireBall>());
	LocFireBall.lock()->TargetPos = LocFireBall.lock()->RandomTargetPos(_TargetPos);
	LocFireBall.lock()->StartPos = LocFireBall.lock()->TargetPos - float4{0, LocFireBall.lock()->TargetPos.y - 500.f, 0, 0};
}

void FireBall::Start()
{
	FireBallRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	FireBallRenderer->GetTransform()->SetWorldScale(RenderScale);
	FireBallRenderer->CreateAnimation({.AnimationName = "FireBall", .SpriteName = "FireBall", .FrameInter = 0.06f, .Loop = true });
	FireBallRenderer->ChangeAnimation("FireBall");

	FireBallCols.resize(4);
	for (size_t i = 0; i < FireBallCols.size(); i++)
	{
		FireBallCols[i] = CreateComponent<GameEngineCollision>(ColOrder::Bullet);
		FireBallCols[i]->GetTransform()->SetWorldScale(ColScale * (static_cast<const float>(i) + 1.f)); // 2020 4040 6060 8080
	}

	Damage.resize(4);
	for (size_t i = 0; i < Damage.size(); i++)
	{
		if (i == 3)
		{
			Damage[i] = 30;
		}
		else
		{
			Damage[i] = 10;
		}
	}


}

void FireBall::Update(float _DeltaTime)
{
	Time += _DeltaTime;
	SmokeTime += _DeltaTime;
	float Ratio = Time * (Speed / (StartPos - TargetPos).Size());
	float4 Pos = float4::LerpClamp(StartPos, TargetPos, Ratio);
	GetTransform()->SetWorldPosition(Pos);
	
	if (SmokeTime >= 0.025f)
	{
		SmokeTime = 0.f;
		FireBallSmoke::CreateSmoke(GetLevel(), GetTransform()->GetWorldPosition());
	}

	if (Ratio >= 1.f)
	{
		Attack();
	}
}

void FireBall::Attack()
{
	std::vector<std::shared_ptr<GameEngineCollision>> HitMonsters = std::vector<std::shared_ptr<GameEngineCollision>>();
	for (size_t i = 0; i < FireBallCols.size(); i++)
	{
		if (FireBallCols[i]->CollisionAll(ColOrder::Monster, HitMonsters, ColType::SPHERE2D, ColType::SPHERE2D))
		{
			for (size_t j = 0; j < HitMonsters.size(); j++)
			{
				dynamic_cast<BaseMonster*>(HitMonsters[j]->GetActor())->CurHP -= Damage[j];
			}
		}
	}
	FireBallExplosion::CreateExplosionEffect(GetLevel(), TargetPos);
	Death();
}

float4 FireBall::RandomTargetPos(const float4& _RealTargetPos)
{
	float4 ActorPos = _RealTargetPos;
	float x = GameEngineRandom::MainRandom.RandomFloat(ActorPos.x - 10000.f, ActorPos.x + 10000.f);
	float y = GameEngineRandom::MainRandom.RandomFloat(ActorPos.y - 10000.f, ActorPos.y + 10000.f);
	float4 LocRandomPos = { x,y,y };
	float RandomRange = GameEngineRandom::MainRandom.RandomFloat(0, Range);
	float4 ResultValue = ActorPos + (ActorPos - LocRandomPos).NormalizeReturn() * RandomRange;
	return ResultValue;
}
