#pragma once
#include <GameEngineCore\GameEngineSpriteRenderer.h>

class _101UIRenderer : public GameEngineSpriteRenderer
{
public:
	// construtor destructor
	_101UIRenderer();
	~_101UIRenderer();

	// delete Function
	_101UIRenderer(const _101UIRenderer& _Other) = delete;
	_101UIRenderer(_101UIRenderer&& _Other) noexcept = delete;
	_101UIRenderer& operator=(const _101UIRenderer& _Other) = delete;
	_101UIRenderer& operator=(_101UIRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

