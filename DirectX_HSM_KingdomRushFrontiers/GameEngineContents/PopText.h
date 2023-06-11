#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class PopText : public GameEngineActor
{
public:
	// construtor destructor
	PopText();
	~PopText();

	// delete Function
	PopText(const PopText& _Other) = delete;
	PopText(PopText&& _Other) noexcept = delete;
	PopText& operator=(const PopText& _Other) = delete;
	PopText& operator=(PopText&& _Other) noexcept = delete;

	static std::shared_ptr<PopText> CreatePopText(HitState _Hit, std::shared_ptr<GameEngineActor> _Actor);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> PopTextRenderer = nullptr;
	float4 RenderScale = {128,32,1};

	float EffectTime = 0.f;
	float EffectSpeed = 12.f;

	void SetTexture(HitState _Hit);
};

