#pragma once
#include <GameEngineCore\GameEngineFontRenderer.h>

class UIFontRenderer : public GameEngineFontRenderer
{
public:
	// construtor destructor
	UIFontRenderer();
	~UIFontRenderer();

	// delete Function
	UIFontRenderer(const UIFontRenderer& _Other) = delete;
	UIFontRenderer(UIFontRenderer&& _Other) noexcept = delete;
	UIFontRenderer& operator=(const UIFontRenderer& _Other) = delete;
	UIFontRenderer& operator=(UIFontRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

