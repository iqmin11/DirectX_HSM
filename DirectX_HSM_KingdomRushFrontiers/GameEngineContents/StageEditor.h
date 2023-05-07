#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include "StagePath.h"
#include <GameEngineBase/GameEngineSerializer.h>
#include <GameEngineBase/GameEngineFile.h>

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

	//int LineIndexs; // 0�� ������ Ÿ��
	//int MonsterIndex; // 0�� ����
	//int MonsterCount; // 10 ���� �����µ�
	//float InterTime; // 2.�ʸ��� Monster�� 1������ �������� 
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

//  Monster�� 3������
// 0�� ����
// 1�� ����
// 2�� ����

class StageData
{
public:
	int StageLevel;
	std::string BackGroundName;
	// 0�� ����
	// 1�� ����
	std::vector<LinePath> Lines;

	std::vector<WaveData> Waves;

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
	int SelectedLine = -1;
	int LineSize = 0;
	std::vector<StageData> Data = {};
	std::shared_ptr<GameEngineActor> LineActor = nullptr;

	GameEngineSerializer PathsSavedBinData = GameEngineSerializer();
	GameEngineSerializer PathsLoadedBinData = GameEngineSerializer();

	void OnGUI(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime) override;
	void ChangeStage(std::shared_ptr<class GameEngineLevel> _Level, int _Selected);

	void StageMapBgTap();
	void PathEditTap();

	void Pushback_Path();
	void Popback_Path();
	void Pushback_Point();
	void Popback_Point();

	void DrawPointRenderer(std::shared_ptr<class GameEngineLevel> _Level);
	void SerializeOneLine(int _StageLevel, int _PathIndex);
	void SerializeOneStageLines(int _StageLevel);
	void SerializeAllPathData();
	void SavePathBinData();

	/*void LoadPathBinData();
	void LoadOneStageLines(int _StageLevel);
	void LoadOneLine(int _StageLevel, int _PathIndex);*/
};
	//std::function<void(int)> ChangeStageInLevel = nullptr;
	//std::function<void()> AddStageLine= nullptr;
	//const StageEnum* StageLevelPtr = nullptr;

