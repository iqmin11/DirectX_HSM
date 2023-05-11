#include "PrecompileHeader.h"
#include "MonsterWave.h"
#include <GameEngineCore/GameEngineLevel.h>

#include "PlayStageLevel.h"
#include "BaseMonster.h"

std::vector<LinePath>* MonsterWave::CurStagePaths = nullptr;
std::shared_ptr<GameEngineLevel> MonsterWave::ParentLevel = nullptr;


MonsterWave::MonsterWave()
{

}

MonsterWave::~MonsterWave()
{

}

void MonsterWave::StartWave(std::shared_ptr<GameEngineLevel> _Level, std::vector<MonsterSpawnData>& _OneWave)
{
	ParentLevel = _Level;
	_Level->CreateActor<MonsterWave>()->SetOneWave(_OneWave);
}

void MonsterWave::SetCurStagePaths(std::vector<LinePath>* _Path)
{
	CurStagePaths = _Path;
}

void MonsterWave::Update(float _DeltaTime)
{
	WaveTime += _DeltaTime;
	if (SpawnDatas.size() != 0)
	{
		StartIter = SpawnDatas.begin();
		EndIter = SpawnDatas.end();
		for (; StartIter != EndIter;)
		{
			if (StartIter->StartTime <= WaveTime)
			{
				BaseMonster::CreateMonster(ParentLevel, StartIter->Monster, (*CurStagePaths)[StartIter->LineIndex].Points);
				StartIter = SpawnDatas.erase(StartIter);
				if (SpawnDatas.size() == 0)
				{
					WaveTime = 0.0f;
					return;
				}
				continue;
			}
			++StartIter;
		}
	}
	else if (WaveTime >= WaveEndTime)
	{
 		Death();
	}
}

void MonsterWave::SetOneWave(std::vector<MonsterSpawnData>& _OneWave)
{
	std::copy(_OneWave.begin(), _OneWave.end(), std::back_inserter(SpawnDatas));
}
