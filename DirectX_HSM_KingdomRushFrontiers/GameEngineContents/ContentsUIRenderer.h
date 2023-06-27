#pragma once
#include <GameEngineCore\GameEngineUIRenderer.h>

class ProgressCircleBuffer
{
public:
	float4 OutColor = float4::Zero;
	float Progress = 0.0f;
};

class ContentsUIRenderer : public GameEngineUIRenderer
{
public:
	// construtor destructor
	ContentsUIRenderer();
	~ContentsUIRenderer();

	// delete Function
	ContentsUIRenderer(const ContentsUIRenderer& _Other) = delete;
	ContentsUIRenderer(ContentsUIRenderer&& _Other) noexcept = delete;
	ContentsUIRenderer& operator=(const ContentsUIRenderer& _Other) = delete;
	ContentsUIRenderer& operator=(ContentsUIRenderer&& _Other) noexcept = delete;

	void SetProgress(float _Ratio);

protected:
	void Start() override;

private:
	ProgressCircleBuffer Buffer;

};

