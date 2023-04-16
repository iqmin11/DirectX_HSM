#pragma once
#include "GameEngineResource.h"

class GameEngineInputLayOut : public GameEngineResource<GameEngineInputLayOut>
{
public:
	// construtor destructor
	GameEngineInputLayOut();
	~GameEngineInputLayOut();

	// delete Function
	GameEngineInputLayOut(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut(GameEngineInputLayOut&& _Other) noexcept = delete;
	GameEngineInputLayOut& operator=(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut& operator=(GameEngineInputLayOut&& _Other) noexcept = delete;

	void Releas();
	void ResCreate(std::shared_ptr<class GameEngineVertexBuffer> _Info, std::shared_ptr<class GameEngineVertexShader> _Shader);
	void Setting() override;

protected:


private:
	ID3D11InputLayout* InputLayOut = nullptr;
};

