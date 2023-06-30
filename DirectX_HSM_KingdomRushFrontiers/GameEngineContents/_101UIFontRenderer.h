#pragma once
#include <GameEngineCore\GameEngineFontRenderer.h>

class _101UIFontRenderer : public GameEngineFontRenderer
{
public:
	// construtor destructor
	_101UIFontRenderer();
	~_101UIFontRenderer();

	// delete Function
	_101UIFontRenderer(const _101UIFontRenderer& _Other) = delete;
	_101UIFontRenderer(_101UIFontRenderer&& _Other) noexcept = delete;
	_101UIFontRenderer& operator=(const _101UIFontRenderer& _Other) = delete;
	_101UIFontRenderer& operator=(_101UIFontRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

