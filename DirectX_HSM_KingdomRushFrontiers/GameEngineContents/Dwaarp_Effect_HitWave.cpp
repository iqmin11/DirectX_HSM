#include "PrecompileHeader.h"
#include "Dwaarp_Effect_HitWave.h"

#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore\GameEngineSpriteRenderer.h>

Dwaarp_Effect_HitWave::Dwaarp_Effect_HitWave()
{

}

Dwaarp_Effect_HitWave::~Dwaarp_Effect_HitWave()
{

}

void Dwaarp_Effect_HitWave::CreateEffect(GameEngineActor* _Parent)
{
	std::weak_ptr<Dwaarp_Effect_HitWave> TempEffect(_Parent->GetLevel()->CreateActor<Dwaarp_Effect_HitWave>());
	float4 ParentPos = _Parent->GetTransform()->GetWorldPosition();
	TempEffect.lock()->GetTransform()->SetWorldPosition({ ParentPos.x, ParentPos.y, -1000 });
}

void Dwaarp_Effect_HitWave::Start()
{
	HitWave = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	HitWave->SetTexture("EarthquakeTower_HitDecal3.png");
}

void Dwaarp_Effect_HitWave::Update(float _DeltaTime)
{
	Time += _DeltaTime;
	Ratio = Time*3;
	CurScale = float4::LerpClamp(float4::Zero, EndScale, Ratio);
	HitWave->ColorOptionValue.MulColor.a = 1-Ratio;
	GetTransform()->SetWorldScale(CurScale);
	if (Ratio >= 1)
	{
		Death();
	}
}
