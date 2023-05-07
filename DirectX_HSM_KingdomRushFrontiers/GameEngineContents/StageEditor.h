#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include "StagePath.h"


class LinePath 
{
public:
	int Index;
	std::vector<float4> Points;
};

class MonsterSpawnData
{
public:
	int LineIndexs;
	int MonsterIndex;
	float Time;
};

class MonsterWaveData
{
public:
	std::vector<MonsterSpawnData> Monster;

	//int LineIndexs; // 0번 라인을 타고
	//int MonsterIndex; // 0번 몬스터
	//int MonsterCount; // 10 마리 내놓는데
	//float InterTime; // 2.초마다 Monster를 1마리씩 내보내고 
};

class WaveData
{
public:
	std::vector<MonsterWaveData> MonsterWaves;
};


class MonsterData
{
public:
	int Hp;
	int Speed;
};

//  Monster가 3종류가
// 0번 몬스터
// 1번 몬스터
// 2번 몬스터

class StageData
{
public:
	int StageLevel;
	std::string BackGroundName;
	// 0번 라인
	// 1번 라인
	std::vector<LinePath> Lines;

	std::vector<WaveData> Waves;

	// Monster0
	// Monster1
	// Monster2
	std::vector<MonsterData> MonsterData;
};


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
	class StageEditLevel* ParentLevel = nullptr;
	int StageCount = 6;
	int SelectedStage = 1;
	int SelectedLine = 0;
	int SelectedPoint = 0;
	std::vector<StageData> Data = {};

	void OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime) override;
	void ChangeStage(int _Selected);

	void ButtonCheck_AddPath();
	void StageMapBgTap();
	void PathEditTap();
};
	//std::function<void(int)> ChangeStageInLevel = nullptr;
	//std::function<void()> AddStageLine= nullptr;
	//const StageEnum* StageLevelPtr = nullptr;

