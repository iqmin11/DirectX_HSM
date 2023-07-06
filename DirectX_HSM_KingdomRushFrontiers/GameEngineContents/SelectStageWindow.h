#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"

class SelectStageWindow : public GameEngineActor
{
public:
	// construtor destructor
	SelectStageWindow();
	~SelectStageWindow();

	// delete Function
	SelectStageWindow(const SelectStageWindow& _Other) = delete;
	SelectStageWindow(SelectStageWindow&& _Other) noexcept = delete;
	SelectStageWindow& operator=(const SelectStageWindow& _Other) = delete;
	SelectStageWindow& operator=(SelectStageWindow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class _101UIRenderer> WindowBg = nullptr;
	float4 BgScale = { 987,586,1 };
	std::shared_ptr<class _101UIRenderer> StagePreview = nullptr;
	float4 PreviewScale = { 285,205,1 };
	std::shared_ptr<class _101UIRenderer> WornOutEffect = nullptr;
	float4 EffectScale = { 308,226,1 };
	float4 PreviewLocPos = { -180,44 };
	std::vector<std::shared_ptr<class _101UIRenderer>> ClearStar = std::vector<std::shared_ptr<class _101UIRenderer>>();
	std::vector<std::shared_ptr<class _101UIRenderer>> ClearInfoBg = std::vector<std::shared_ptr<class _101UIRenderer>>();

	std::shared_ptr<class _101UIFontRenderer> LeftTitle = nullptr;
	std::shared_ptr<class _101UIFontRenderer> RightTitle = nullptr;
	std::shared_ptr<class _101UIFontRenderer> StageExplain = nullptr;

	std::shared_ptr<class ContentsButton> StageStartButton = nullptr;
	float4 StartButtonLocPos = {223, -134};
	std::shared_ptr<class ContentsButton> ExitWindowButton = nullptr;

};

