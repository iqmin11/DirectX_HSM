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

	std::shared_ptr<class Hero_RallyPoint> GetHero() const 
	{
		return AcHero;
	}

	void InitStage(int _Stage);
	void ClearStage();
	void StartNextWave();
	void SubLife(int _LivesTaken);

	const std::vector<std::shared_ptr<class WaveButtons>> GetWaveButtons() const
	{
		return AcWaveButtons;
	}

	int GetNextWave() const
	{
		return NextWave;
	}

	std::shared_ptr<class StageBg> GetStageBg() const
	{
		return AcStageBg;
	}

	int GetCurStage() const 
	{
		return CurStage;
	}

	int GetMaxWave()
	{
		return static_cast<int>(AllStageData[CurStage].Waves.size());
	}

	const int* GetNextWavePtr() const
	{
		return &NextWave;
	}

	const int* GetMaxWavePtr() const
	{
		return &MaxWave;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class StageBg> AcStageBg = nullptr;
	std::shared_ptr<class PlayStageUI> AcPlayStageUI = nullptr;
	std::vector<std::shared_ptr<class BuildArea>> AcBuildAreas = std::vector<std::shared_ptr<class BuildArea>>();
	std::shared_ptr<class MousePointer> AcMousePointer = nullptr;
	std::vector<std::shared_ptr<class WaveButtons>> AcWaveButtons = std::vector<std::shared_ptr<class WaveButtons>>();
	std::shared_ptr<class Hero_RallyPoint> AcHero = nullptr;
	std::shared_ptr<class PlayManager> MainPlayer = nullptr;
	std::shared_ptr<class VictoryBadge> AcVictoryBadge = nullptr;


	int CurStage = -1;
	int NextWave = -1; // �ε��� ����
	int MaxWave = -1;

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

	void LoadWaveButtonPos();
	void LoadStageStartGold();
	void LoadStageHeroStartPos();

	void KeySet();
	
	void SetStageBg(int _Stage);
	void SetStagePaths(int _Stage);
	void SetStageBuildArea(int _Stage);
	void SetStageWaveButtons(int _Stage);
	void SetStageGold(int _Stage);
	void SetHero(int _Stage);

	void ClearStageBg();
	void ClearStagePaths();
	void ClearStageBuildArea();
	void ClearStageWaveButtons();
	void ClearStageGold();
	void ClearHero();
	void ClearLiveWave();
	void ClearLiveMonster();

	void LoadPlayLevelTexture(std::string_view _Folder);
	void LoadPlayLevelAnimation();
	void LoadFont();

	void Defeat();
	void Victory();
	
	bool IsDefeat();
	bool IsVictory();
	bool IsLastWave();
};

