#pragma once
class GameEngineResource
{
public:
	// construtor destructor
	GameEngineResource();
	~GameEngineResource();

	// delete Function
	GameEngineResource(const GameEngineResource& _Other) = delete;
	GameEngineResource(GameEngineResource&& _Other) noexcept = delete;
	GameEngineResource& operator=(const GameEngineResource& _Other) = delete;
	GameEngineResource& operator=(GameEngineResource&& _Other) noexcept = delete;

protected:


private:

};

