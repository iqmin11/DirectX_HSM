#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class TitleBackground : public GameEngineActor
{
public:
	// construtor destructor
	TitleBackground();
	~TitleBackground();

	// delete Function
	TitleBackground(const TitleBackground& _Other) = delete;
	TitleBackground(TitleBackground&& _Other) noexcept = delete;
	TitleBackground& operator=(const TitleBackground& _Other) = delete;
	TitleBackground& operator=(TitleBackground&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;
	float4 RenderScale = { 1600, 900 };
	std::shared_ptr<class GameEngineSpriteRenderer> BackgroundRenderer = nullptr;
};

