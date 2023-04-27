#pragma once
#include "GameEngineRenderer.h"

class GameEngineSpriteRenderer : public GameEngineRenderer
{
public:
	// construtor destructor
	GameEngineSpriteRenderer();
	~GameEngineSpriteRenderer();

	// delete Function
	GameEngineSpriteRenderer(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer(GameEngineSpriteRenderer&& _Other) noexcept = delete;
	GameEngineSpriteRenderer& operator=(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer& operator=(GameEngineSpriteRenderer&& _Other) noexcept = delete;

	void SetTexture(const std::string_view& _Name);

	void SetFlipX();
	void SetFlipY();

protected:


private:
	void Start() override;
};
