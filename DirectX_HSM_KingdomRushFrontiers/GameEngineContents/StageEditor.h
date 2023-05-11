#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineBase/GameEngineSerializer.h>
#include <GameEngineBase/GameEngineFile.h>
#include "ContentsData.h"



// 설명 :
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
	void Start() override;
private:
	int StageCount = 6;
	int SelectedStage = 0;
	std::vector<StageData> Data = {};

	int SelectedLine = -1;
	//int LineSize = 0;
	std::shared_ptr<class GameEngineActor> LineActor = nullptr;

	int SelectedWave = -1;
	int SelectedWaveMonster = 0;
	int SelectedWaveLineIndex = 0;
	float StartTimeInWave = 0.0f;


	void OnGUI(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime) override;
	void ChangeStage(std::shared_ptr<class GameEngineLevel> _Level, int _Selected);

	// 배경 관련 (미완)
	void StageMapBgTap();

	// 몬스터 경로 관련
	void PathEditTap(std::shared_ptr<class GameEngineLevel> _Level);

	void Pushback_Path();
	void Popback_Path();
	void Pushback_Point();
	void Popback_Point();

	void DrawPointRenderer(std::shared_ptr<class GameEngineLevel> _Level);

	void SerializeOneLine(GameEngineSerializer& _Serializer, int _StageLevel, int _PathIndex);
	void SerializeOneStageLines(GameEngineSerializer& _Serializer, int _StageLevel);
	void SerializeAllPathData(GameEngineSerializer& _Serializer);
	void SavePathBinData();

	void LoadPathBinData();
	void LoadOneStageLines(GameEngineSerializer& _Serializer, int _StageLevel);
	void LoadOneLine(GameEngineSerializer& _Serializer, int _StageLevel, int _PathIndex);

	void PathTest(std::shared_ptr<class GameEngineLevel> _Level);
	
	//몬스터 웨이브 관련
	void WaveEditTap(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime);

	void Pushback_Wave();
	void Popback_Wave();
	void Pushback_MonsterSpawnData(MonsterEnum _Monster, int _LineIndex, float _StartTime);
	void Popback_MonsterSpawnData();

	void SerializeOneWaveData(GameEngineSerializer& _Serializer, int _StageLevel, int _WaveIndex);
	void SerializeOneStageWave(GameEngineSerializer& _Serializer, int _StageLevel);
	void SerializeAllWaveData(GameEngineSerializer& _Serializer);
	void SaveWaveBinData();

	void LoadWaveBinData();
	void LoadOneStageWave(GameEngineSerializer& _Serializer, int _StageLevel);
	void LoadOneWave(GameEngineSerializer& _Serializer, int _StageLevel, int _WaveIndex);

	void UpdateWaveTest(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime);
	bool IsValidWaveTest = false;
	float WaveTestTime = 0.f;

	std::string MonsterEnumToString(MonsterEnum _Monster);
};
	//std::function<void(int)> ChangeStageInLevel = nullptr;
	//std::function<void()> AddStageLine= nullptr;
	//const StageEnum* StageLevelPtr = nullptr;

