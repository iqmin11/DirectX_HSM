#pragma once
#include <GameEngineCore\GameEngineActor.h>

class Effect_SpreadStar : public GameEngineActor
{
public:
	// construtor destructor
	Effect_SpreadStar();
	~Effect_SpreadStar();

	// delete Function
	Effect_SpreadStar(const Effect_SpreadStar& _Other) = delete;
	Effect_SpreadStar(Effect_SpreadStar&& _Other) noexcept = delete;
	Effect_SpreadStar& operator=(const Effect_SpreadStar& _Other) = delete;
	Effect_SpreadStar& operator=(Effect_SpreadStar&& _Other) noexcept = delete;

	static std::weak_ptr<Effect_SpreadStar> CreateEffect(class VictoryBadge* _Parent, float4 _EffectStartPos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	size_t StarCount = 70;
	float Rad = 0.f;
};

