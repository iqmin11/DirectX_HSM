#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class StageEditor : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	StageEditor();
	~StageEditor();

	// delete Function
	StageEditor(const StageEditor& _Other) = delete;
	StageEditor(StageEditor&& _Other) noexcept = delete;
	StageEditor& operator=(const StageEditor& _Other) = delete;
	StageEditor& operator=(StageEditor&& _Other) noexcept = delete;

protected:

private:
	void OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime) override;
};

