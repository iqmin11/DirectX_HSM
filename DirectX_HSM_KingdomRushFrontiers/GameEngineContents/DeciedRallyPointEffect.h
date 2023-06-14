#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"

class DeciedRallyPointEffect : public GameEngineActor
{
public:
	// construtor destructor
	DeciedRallyPointEffect();
	~DeciedRallyPointEffect();

	// delete Function
	DeciedRallyPointEffect(const DeciedRallyPointEffect& _Other) = delete;
	DeciedRallyPointEffect(DeciedRallyPointEffect&& _Other) noexcept = delete;
	DeciedRallyPointEffect& operator=(const DeciedRallyPointEffect& _Other) = delete;
	DeciedRallyPointEffect& operator=(DeciedRallyPointEffect&& _Other) noexcept = delete;

	static std::shared_ptr<DeciedRallyPointEffect> CreateRallyEffect(class Melee_Tower* _Parent, const float4& _Pos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> PopTextRenderer = nullptr;
	float4 RenderScale = { 128,128,1 };
	float EffectTime = 0.f;

};

