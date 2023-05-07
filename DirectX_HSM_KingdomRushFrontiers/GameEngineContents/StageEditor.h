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

