#include "PrecompileHeader.h"
#include "MonsterWave.h"
#include <GameEngineCore/GameEngineLevel.h>

#include "PlayStageLevel.h"
#include "BaseMonster.h"
#include "WaveButtons.h"
#include "NextWaveStartButton.h"
#include "BottomWaveButton.h"

std::vector<LinePath>* MonsterWave::CurStagePaths = nullptr;
std::shared_ptr<PlayStageLevel> MonsterWave::ParentLevel = nullptr;

bool MonsterWave::IsLastMonsterSummon = false;
std::list<std::weak_ptr<MonsterWave>> MonsterWave::LiveWaveManager = std::list<std::weak_ptr<MonsterWave>>();


MonsterWave::MonsterWave()
{

}

MonsterWave::~MonsterWave()
{

}

void MonsterWave::StartWave(std::shared_ptr<GameEngineLevel> _Level, std::vector<MonsterSpawnData>& _OneWave)
{
	ParentLevel = _Level->DynamicThis<PlayStageLevel>();
	std::weak_ptr<MonsterWave> Local(ParentLevel->CreateActor<MonsterWave>());
	Local.lock()->SetOneWave(_OneWave);
	LiveWaveManager.push_back(Local);
	IsLastMonsterSummon = false;
	BottomWaveButton::IsValid = false;
	Local.lock()->WaveStartSound = GameEngineSound::Play("Sound_WaveIncoming.ogg");
	Local.lock()->WaveStartSound.SetVolume(0.5f);
}

void MonsterWave::SetCurStagePaths(std::vector<LinePath>* _Path)
{
	CurStagePaths = _Path;
}

void MonsterWave::DeathWave()
{
	auto StartIter = LiveWaveManager.begin();
	auto EndIter = LiveWaveManager.end();

	for (; StartIter != EndIter; StartIter)
	{
		if (StartIter->lock().get() == this)
		{
			LiveWaveManager.erase(StartIter);
			Death();
			break;
		}
	}
}

void MonsterWave::ReleaseWave()
{
	auto StartIter = LiveWaveManager.begin();
	auto EndIter = LiveWaveManager.end();
	for (; StartIter != EndIter; )
	{
		StartIter->lock()->Death();
		StartIter = LiveWaveManager.erase(StartIter);
	}
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
		IsLastMonsterSummon = true;
		if (ParentLevel->GetWaveButtons().size() > ParentLevel->GetNextWave())
		{
			ParentLevel->GetWaveButtons()[ParentLevel->GetNextWave()]->OnButtons();
			BottomWaveButton::IsValid = true;
		}
		DeathWave();
	}
}

void MonsterWave::SetOneWave(std::vector<MonsterSpawnData>& _OneWave)
{
	std::copy(_OneWave.begin(), _OneWave.end(), std::back_inserter(SpawnDatas));
}
