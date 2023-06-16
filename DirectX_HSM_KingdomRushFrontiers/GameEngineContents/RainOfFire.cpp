#include "PrecompileHeader.h"
#include "RainOfFire.h"

#include <GameEngineCore\GameEngineLevel.h>
#include "FireBall.h"

RainOfFire::RainOfFire()
{

}

RainOfFire::~RainOfFire()
{

}

void RainOfFire::CastingSpell(GameEngineLevel* _Level, const float4& _Pos)
{
	std::weak_ptr<RainOfFire> LocSpell(_Level->CreateActor<RainOfFire>());
	LocSpell.lock()->TargetPos = _Pos;
}

void RainOfFire::Update(float _DeltaTime)
{
	Time += _DeltaTime;
	if (Time >= .3f)
	{
		FireBall::SummonFireBall(GetLevel(), TargetPos);
		Time = 0.f;
		if (++Count == 3)
		{
			Death();
		}
	}
}

