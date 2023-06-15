#include "PrecompileHeader.h"
#include "FireBallExplosion.h"

#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore\GameEngineSpriteRenderer.h>

FireBallExplosion::FireBallExplosion()
{

}

FireBallExplosion::~FireBallExplosion()
{

}

void FireBallExplosion::CreateExplosionEffect(GameEngineLevel* _Level, float4 _Pos)
{
	std::weak_ptr<FireBallExplosion> Explosion(_Level->CreateActor<FireBallExplosion>());
	Explosion.lock()->GetTransform()->SetWorldPosition(_Pos);
}

void FireBallExplosion::Start()
{
	ExplosionRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	ExplosionRenderer->GetTransform()->SetWorldScale(RenderScale);
	ExplosionRenderer->CreateAnimation({ .AnimationName = "Explosion", .SpriteName = "FireBallExplosion", .FrameInter = 0.06f, .Loop = false });
	ExplosionRenderer->SetAnimationStartEvent("Explosion", 8, [this]()
		{	
			Death();
		});
	ExplosionRenderer->ChangeAnimation("Explosion");
}