#pragma once
#include "GameEngineResource.h"

class GameEngineDirectBuffer
{
public:
	// construtor destructor
	GameEngineDirectBuffer();
	~GameEngineDirectBuffer();

	// delete Function
	GameEngineDirectBuffer(const GameEngineDirectBuffer& _Other) = delete;
	GameEngineDirectBuffer(GameEngineDirectBuffer&& _Other) noexcept = delete;
	GameEngineDirectBuffer& operator=(const GameEngineDirectBuffer& _Other) = delete;
	GameEngineDirectBuffer& operator=(GameEngineDirectBuffer&& _Other) noexcept = delete;

protected:
	D3D11_BUFFER_DESC BufferInfo = { 0, };
	ID3D11Buffer* Buffer = nullptr;

private:

};

