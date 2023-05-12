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
	void SetStage(int _Stage);
	void ResetStage();


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class StageBg> AcStageBg = nullptr;
	//std::shared_ptr<class MonsterPath> AcMonsterPath = nullptr;
	//std::shared_ptr<class MonsterWave> AcMonsterWave = nullptr;
	std::shared_ptr<class PlayStageUI> AcPlayStageUI = nullptr;

	int CurStage = -1;
	int NextWave = -1;

	std::shared_ptr<class BaseShooter> AcTestShooter = nullptr;

	void LoadAllStageData(); //Start에서 레벨이 만들어질때 실행함. 경로와 웨이브 정보가 담겨있음.
	
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
	void LoadMonsterTexture();
	void LoadTowerTexture();
	void LoadStageBgTexture();
};

