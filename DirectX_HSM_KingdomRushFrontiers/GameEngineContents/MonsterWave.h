#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsData.h"

class MonsterWave : public GameEngineActor
{
public:
	// construtor destructor
	MonsterWave();
	~MonsterWave();

	// delete Function
	MonsterWave(const MonsterWave& _Other) = delete;
	MonsterWave(MonsterWave&& _Other) noexcept = delete;
	MonsterWave& operator=(const MonsterWave& _Other) = delete;
	MonsterWave& operator=(MonsterWave&& _Other) noexcept = delete;

	static void StartWave(std::shared_ptr<GameEngineLevel> _Level, std::vector<MonsterSpawnData>& _OneWave);
	static void SetCurStagePaths(std::vector<LinePath>* _Path);

protected:
	void Update(float _DeltaTime) override;

private:
	static std::shared_ptr<GameEngineLevel> ParentLevel;

	std::list<MonsterSpawnData> SpawnDatas = std::list<MonsterSpawnData>();
	float WaveTime = 0.0f;
	std::list<MonsterSpawnData>::iterator StartIter = std::list<MonsterSpawnData>::iterator();
	std::list<MonsterSpawnData>::iterator EndIter = std::list<MonsterSpawnData>::iterator();

	static std::vector<LinePath>* CurStagePaths;

	float WaveEndTime = 0.0f; //������ ���Ͱ� ��ȯ�ǰ� �����Ŀ� Wave�� �����°��� �����ִ� ����

	void SetOneWave(std::vector<MonsterSpawnData>& _OneWave);
};
