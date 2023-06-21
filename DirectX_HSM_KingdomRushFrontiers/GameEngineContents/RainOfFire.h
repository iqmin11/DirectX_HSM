#pragma once
#include <GameEngineCore\GameEngineActor.h>

class RainOfFire : public GameEngineActor
{
public:
	// construtor destructor
	RainOfFire();
	~RainOfFire();

	// delete Function
	RainOfFire(const RainOfFire& _Other) = delete;
	RainOfFire(RainOfFire&& _Other) noexcept = delete;
	RainOfFire& operator=(const RainOfFire& _Other) = delete;
	RainOfFire& operator=(RainOfFire&& _Other) noexcept = delete;

	static void CastingSpell(GameEngineLevel* _Level, const float4& _Pos);

protected:
	void Update(float _DeltaTime) override;
private:
	float Time = 0.3f;
	int Count = 0;
	float4 TargetPos = float4::Zero;
};

