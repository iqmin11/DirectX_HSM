#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"

class Dwaarp_Effect_HitWave : public GameEngineActor
{
public:
	// construtor destructor
	Dwaarp_Effect_HitWave();
	~Dwaarp_Effect_HitWave();

	// delete Function
	Dwaarp_Effect_HitWave(const Dwaarp_Effect_HitWave& _Other) = delete;
	Dwaarp_Effect_HitWave(Dwaarp_Effect_HitWave&& _Other) noexcept = delete;
	Dwaarp_Effect_HitWave& operator=(const Dwaarp_Effect_HitWave& _Other) = delete;
	Dwaarp_Effect_HitWave& operator=(Dwaarp_Effect_HitWave&& _Other) noexcept = delete;

	static void CreateEffect(class GameEngineActor* _Parent);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> HitWave = nullptr;
	float4 CurScale = float4::Zero;
	float4 EndScale = { 360.f,206.f };
	float Time = 0.f;
	float Ratio = 0.f;
};

