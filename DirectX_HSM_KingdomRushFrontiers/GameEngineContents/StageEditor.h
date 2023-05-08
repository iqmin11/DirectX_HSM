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
	MonsterEnum Monster = MonsterEnum::Null;
	int Hp = 0;
	int Speed = 0;
};

//  Monster가 3종류가
// 0번 몬스터
// 1번 몬스터
// 2번 몬스터

class StageData
{
public:
	int StageLevel = 0;
	std::string BackGroundName = "\0";
	// 0번 라인
	// 1번 라인
	std::vector<LinePath> Lines = std::vector<LinePath>();

	std::vector<WaveData> Waves = std::vector<WaveData>();

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
	int StageCount = 6;
	int SelectedStage = 0;
	std::vector<StageData> Data = {};

	int SelectedLine = -1;
	int LineSize = 0;
	GameEngineSerializer PathsSavedBinData = GameEngineSerializer();
	GameEngineSerializer PathsLoadedBinData = GameEngineSerializer();
	std::shared_ptr<class GameEngineActor> LineActor = nullptr;

	int SelectedWave = -1;

	void OnGUI(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime) override;
	void ChangeStage(std::shared_ptr<class GameEngineLevel> _Level, int _Selected);

	// 배경 관련 (미완)
	void StageMapBgTap();

	// 몬스터 경로 관련
	void PathEditTap();

	void Pushback_Path();
	void Popback_Path();
	void Pushback_Point();
	void Popback_Point();

	void DrawPointRenderer(std::shared_ptr<class GameEngineLevel> _Level); //릴리즈 완성되면 수정 예정
	void SerializeOneLine(int _StageLevel, int _PathIndex);
	void SerializeOneStageLines(int _StageLevel);
	void SerializeAllPathData();
	void SavePathBinData();

	void LoadPathBinData();
	void LoadOneStageLines(int _StageLevel);
	void LoadOneLine(int _StageLevel, int _PathIndex);

	//몬스터 웨이브 관련
	void WaveEditTap();
	void Pushback_Wave();
	void Popback_Wave();

	//Test
	void PathTest(std::shared_ptr<class GameEngineLevel> _Level);
};
	//std::function<void(int)> ChangeStageInLevel = nullptr;
	//std::function<void()> AddStageLine= nullptr;
	//const StageEnum* StageLevelPtr = nullptr;

