#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsData.h"

class MonsterWave : public GameEngineActor
{
public:
	static bool IsLastMonsterSummon;
	static std::list<std::weak_ptr<MonsterWave>> LiveWaveManager;

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
	static void ReleaseWave();

protected:
	void Update(float _DeltaTime) override;

private:
	static std::shared_ptr<class PlayStageLevel> ParentLevel;

	std::list<MonsterSpawnData> SpawnDatas = std::list<MonsterSpawnData>();
	float WaveTime = 0.0f;
	std::list<MonsterSpawnData>::iterator StartIter = std::list<MonsterSpawnData>::iterator();
	std::list<MonsterSpawnData>::iterator EndIter = std::list<MonsterSpawnData>::iterator();

	static std::vector<LinePath>* CurStagePaths;

	float WaveEndTime = 5.0f; //마지막 몬스터가 소환되고 몇초후에 Wave가 끝나는가를 정해주는 숫자

	void SetOneWave(std::vector<MonsterSpawnData>& _OneWave);
	void DeathWave();
};

