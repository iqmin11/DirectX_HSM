#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineTimeEvent.h>
#include "ContentsData.h"

class PlayStageLevel : public GameEngineLevel
{
public:
	static std::vector<StageData> AllStageData;

	// construtor destructor
	PlayStageLevel();
	~PlayStageLevel();

	// delete Function
	PlayStageLevel(const PlayStageLevel& _Other) = delete;
	PlayStageLevel(PlayStageLevel&& _Other) noexcept = delete;
	PlayStageLevel& operator=(const PlayStageLevel& _Other) = delete;
	PlayStageLevel& operator=(PlayStageLevel&& _Other) noexcept = delete;

	//월드맵에서 스테이지를 선택하면 이 PlayStageLevel에서 해당 단계 스테이지를 로드해야함

	void InitStage(int _Stage);
	void ClearStage();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class StageBg> AcStageBg = nullptr;
	std::shared_ptr<class PlayStageUI> AcPlayStageUI = nullptr;
	std::vector<std::shared_ptr<class BuildArea>> AcBuildAreas = std::vector<std::shared_ptr<class BuildArea>>();
	std::shared_ptr<class MousePointer> AcMousePointer = nullptr;

	int CurStage = -1;
	int NextWave = -1;

	void LoadAllStageData(); 
	
	void LoadPathBinData();
	void LoadOneStageLines(GameEngineSerializer& _Serializer, int _StageLevel);
	void LoadOneLine(GameEngineSerializer& _Serializer, int _StageLevel, int _PathIndex);
	
	void LoadWaveBinData();
	void LoadOneStageWave(GameEngineSerializer& _Serializer, int _StageLevel);
	void LoadOneWave(GameEngineSerializer& _Serializer, int _StageLevel, int _WaveIndex);

	void LoadAreaBinData();
	void LoadOneStageAreas(GameEngineSerializer& _Serializer, int _StageLevel);
	
	void LoadRallyBinData();
	void LoadOneStageRally(GameEngineSerializer& _Serializer, int _StageLevel);

	void KeySet();
	
	void SetStageBg(int _Stage);
	void SetStagePaths(int _Stage);
	void SetStageBuildArea(int _Stage);
	void ClearStageBg();
	void ClearStagePaths();
	void ClearStageBuildArea();

	void StartNextWave();
	void LoadPlayLevelTexture(std::string_view _Folder);
	void LoadPlayLevelAnimation();
};

