#pragma once
#include <GameEngineCore/GameEngineActor.h>

class TitleLogo : public GameEngineActor
{
public:
	// construtor destructor
	TitleLogo();
	~TitleLogo();

	// delete Function
	TitleLogo(const TitleLogo& _Other) = delete;
	TitleLogo(TitleLogo&& _Other) noexcept = delete;
	TitleLogo& operator=(const TitleLogo& _Other) = delete;
	TitleLogo& operator=(TitleLogo&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ActorPos = {0, 140};
	float ScaleRatio = 900.f / 720.f;

	float4 LogoRenderScale = { 480.f, 378.f };
	std::shared_ptr<class GameEngineSpriteRenderer> LogoRenderer = nullptr;
	
	float4 StartButtonRenderScale = { 328., 284.f };
	float4 StartButtonRenderPos = {0,-50};
	std::shared_ptr<class GameEngineSpriteRenderer> StartButtonRenderer = nullptr;
};

