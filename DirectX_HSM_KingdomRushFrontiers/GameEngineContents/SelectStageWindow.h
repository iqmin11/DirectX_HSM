#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"

class SelectStageWindow : public GameEngineActor
{
public:
	static SelectStageWindow* MainSelectWindow;

	// construtor destructor
	SelectStageWindow();
	~SelectStageWindow();

	// delete Function
	SelectStageWindow(const SelectStageWindow& _Other) = delete;
	SelectStageWindow(SelectStageWindow&& _Other) noexcept = delete;
	SelectStageWindow& operator=(const SelectStageWindow& _Other) = delete;
	SelectStageWindow& operator=(SelectStageWindow&& _Other) noexcept = delete;

	void StageWindowOn();

	void SelectStage(int _Select)
	{
		SelectedStage = _Select;
	}

	int GetSelectedStage() const
	{
		return SelectedStage;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	int SelectedStage = 0;

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
	float4 LeftTitleLocPos = { -173,215 };
	float LeftTitleFontScale = 28.f;
	std::vector<std::string> LeftTitleData = std::vector<std::string>();
	
	std::shared_ptr<class _101UIFontRenderer> RightTitle = nullptr;
	float4 RightTitleLocPos = {226,228};
	float RightTitleFontScale = 28.f;

	std::shared_ptr<class _101UIFontRenderer> StageExplain = nullptr;
	std::vector<std::string> StageExplainData = std::vector<std::string>();
	float4 StageExplainLocPos = { 84,182 };
	float StageExplainFontScale = 25.f;

	float4 FontColor = { 0.392156862745098f, 0.3490196078431373f, 0.203921568627451f};

	std::shared_ptr<class ContentsButton> AcStageStartButton = nullptr;
	float4 StartButtonLocPos = {223, -134};
	
	std::shared_ptr<class ContentsButton> ExitWindowButton = nullptr;
	float4 ExitButtonLocPos = { 472, 272 };

	std::shared_ptr<class _101UIRenderer> TitleDeco_Left = nullptr;
	std::shared_ptr<class _101UIRenderer> TitleDeco_Right = nullptr;


	void SetLeftTitleData();
	void SetStageExplainData();
};

