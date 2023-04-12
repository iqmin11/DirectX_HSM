#pragma once
#include "GameEngineResource.h"
#include "GameEngineShader.h"

class GameEngineVertexShader : public GameEngineResource<GameEngineVertexShader>, public GameEngineShader
{
public:
	// construtor destructor
	GameEngineVertexShader();
	~GameEngineVertexShader();

	// delete Function
	GameEngineVertexShader(const GameEngineVertexShader& _Other) = delete;
	GameEngineVertexShader(GameEngineVertexShader&& _Other) noexcept = delete;
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _Other) = delete;
	GameEngineVertexShader& operator=(GameEngineVertexShader&& _Other) noexcept = delete;

protected:


private:


};

