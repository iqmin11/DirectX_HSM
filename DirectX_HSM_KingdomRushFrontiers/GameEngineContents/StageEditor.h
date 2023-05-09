#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineBase/GameEngineSerializer.h>
#include <GameEngineBase/GameEngineFile.h>
#include "ContentsEnum.h"

class LinePath 
{
public:
	LinePath()
		:Index(0), Points(std::vector<float4>()) {}

	LinePath(int _Index)
		:Index(_Index), Points(std::vector<float4>()) {}
	
	int Index;
	std::vector<float4> Points;
};

class MonsterSpawnData
{
public:
	MonsterSpawnData(MonsterEnum _Monster, int _LineIndex, float _StartTime)
		: Monster(_Monster), LineIndex(_LineIndex), StartTime(_StartTime) {}
public:
	MonsterEnum Monster = MonsterEnum::Null;
	int LineIndex = 0;
	float StartTime = 0;
};

class WaveData
{
public:
	std::vector<MonsterSpawnData> MonsterSpawn;
};


class MonsterData
{
public:
	MonsterEnum Monster = MonsterEnum::Null;
	int Hp = 0;
	int Speed = 0;
};

//  Monster�� 3������
// 0�� ����
// 1�� ����
// 2�� ����

class StageData
{
public:
	int StageLevel = 0;
	std::string BackGroundName = "\0";
	// 0�� ����
	// 1�� ����
	std::vector<LinePath> Lines = std::vector<LinePath>();

	std::vector<WaveData> Waves = std::vector<WaveData>();

	// Monster0
	// Monster1
	// Monster2
	std::vector<MonsterData> MonsterData;
};


// ���� :
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
	int LineSize = 0;
	GameEngineSerializer PathsSavedBinData = GameEngineSerializer();
	GameEngineSerializer PathsLoadedBinData = GameEngineSerializer();
	std::shared_ptr<class GameEngineActor> LineActor = nullptr;

	int SelectedWave = -1;
	int SelectedWaveMonster = 0;
	int SelectedWaveLineIndex = 0;
	float StartTimeInWave = 0.0f;

	void OnGUI(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime) override;
	void ChangeStage(std::shared_ptr<class GameEngineLevel> _Level, int _Selected);

	// ��� ���� (�̿�)
	void StageMapBgTap();

	// ���� ��� ����
	void PathEditTap(std::shared_ptr<class GameEngineLevel> _Level);

	void Pushback_Path();
	void Popback_Path();
	void Pushback_Point();
	void Popback_Point();

	void DrawPointRenderer(std::shared_ptr<class GameEngineLevel> _Level);

	void SerializeOneLine(int _StageLevel, int _PathIndex);
	void SerializeOneStageLines(int _StageLevel);
	void SerializeAllPathData();
	void SavePathBinData();

	void LoadPathBinData();
	void LoadOneStageLines(int _StageLevel);
	void LoadOneLine(int _StageLevel, int _PathIndex);

	void PathTest(std::shared_ptr<class GameEngineLevel> _Level);
	
	//���� ���̺� ����
	void WaveEditTap();
	void Pushback_Wave();
	void Popback_Wave();
	void Pushback_MonsterSpawnData(MonsterEnum _Monster, int _LineIndex, float _StartTime);
	void Popback_MonsterSpawnData();

	//void SerializeOneWaveData(int _StageLevel, int _Wave);

	std::string MonsterEnumToString(MonsterEnum _Monster);
};
	//std::function<void(int)> ChangeStageInLevel = nullptr;
	//std::function<void()> AddStageLine= nullptr;
	//const StageEnum* StageLevelPtr = nullptr;

