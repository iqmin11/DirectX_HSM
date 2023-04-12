#pragma once
#include "GameEngineResource.h"

class GameEngineRenderingPipeLine : public GameEngineResource<GameEngineRenderingPipeLine>
{
public:
	// construtor destructor
	GameEngineRenderingPipeLine();
	~GameEngineRenderingPipeLine();

	// delete Function
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _Other) noexcept = delete;
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine& operator=(GameEngineRenderingPipeLine&& _Other) noexcept = delete;

	void InputAssembler1();
	void VertexShader();
	void InputAssembler2();
	void Rasterizer();
	void PixelShader();
	void OutputMerger();

	void SetVertexBuffer(const std::string_view& _Value);

protected:


private:
	std::shared_ptr<class GameEngineVertexBuffer> VertexBuffer;
};

