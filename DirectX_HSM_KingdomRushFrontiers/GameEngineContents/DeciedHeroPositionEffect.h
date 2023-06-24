#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"

class DeciedHeroPositionEffect : public GameEngineActor
{
public:
	// construtor destructor
	DeciedHeroPositionEffect();
	~DeciedHeroPositionEffect();

	// delete Function
	DeciedHeroPositionEffect(const DeciedHeroPositionEffect& _Other) = delete;
	DeciedHeroPositionEffect(DeciedHeroPositionEffect&& _Other) noexcept = delete;
	DeciedHeroPositionEffect& operator=(const DeciedHeroPositionEffect& _Other) = delete;
	DeciedHeroPositionEffect& operator=(DeciedHeroPositionEffect&& _Other) noexcept = delete;
	
	static std::shared_ptr<DeciedHeroPositionEffect> CreateEffect(class GameEngineLevel* _Level, const float4& _Pos);

protected:
	void Start() override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer = nullptr;
	float4 RenderScale = { 77,38,1 };
	float EffectTime = 0.f;
};

