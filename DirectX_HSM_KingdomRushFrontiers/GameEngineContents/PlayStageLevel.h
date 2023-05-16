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

	//����ʿ��� ���������� �����ϸ� �� PlayStageLevel���� �ش� �ܰ� ���������� �ε��ؾ���

	void SetStage(int _Stage);
	void InitStage();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class StageBg> AcStageBg = nullptr;
	std::shared_ptr<class PlayStageUI> AcPlayStageUI = nullptr;
	std::shared_ptr<class BaseTower> AcTestTower0 = nullptr;
	//std::shared_ptr<class BaseTower> AcTestTower1 = nullptr;
	std::list<std::shared_ptr<class BuildArea>> AcBuildArea = std::list<std::shared_ptr<class BuildArea>>();


	int CurStage = -1;
	int NextWave = -1;

	void LoadAllStageData(); //Start���� ������ ��������� ������. ��ο� ���̺� ������ �������.
	
	void LoadPathBinData();
	void LoadOneStageLines(GameEngineSerializer& _Serializer, int _StageLevel);
	void LoadOneLine(GameEngineSerializer& _Serializer, int _StageLevel, int _PathIndex);
	
	void LoadWaveBinData();
	void LoadOneStageWave(GameEngineSerializer& _Serializer, int _StageLevel);
	void LoadOneWave(GameEngineSerializer& _Serializer, int _StageLevel, int _WaveIndex);

	void KeySet();
	
	void SetStageBg(int _Stage);
	void SetStagePaths(int _Stage);
	void ResetStageBg();
	void ResetStagePaths();

	void StartNextWave();
	void LoadPlayLevelTexture(std::string_view _Folder);
};

