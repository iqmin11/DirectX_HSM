#include "PrecompileHeader.h"
#include "BaseMonster.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseFighter.h"
#include "DesertThug.h"
#include "DuneRaider.h"
#include "Immortal.h"
#include "PlayStageLevel.h"
#include "PlayManager.h"
#include "SandHound.h"
#include "WarHound.h"
#include "DuneTerror.h"
#include "GiantWasp.h"
#include "GiantWaspQueen.h"
#include "GiantScorpion.h"
#include "DessertArcher.h"
#include "Executioner.h"
#include "SandWraith.h"
#include "Fallen.h"

std::list<std::weak_ptr<BaseMonster>> BaseMonster::LiveMonsterList = std::list<std::weak_ptr<BaseMonster>>();

bool BaseMonster::IsAllMonsterDead()
{
	return LiveMonsterList.size() == 0;
}

void BaseMonster::LiveMonsterListForceRelease()
{
	auto StartIter = LiveMonsterList.begin();
	auto EndIter = LiveMonsterList.end();

	for (; StartIter != EndIter;)
	{
		StartIter->lock()->Death();
		StartIter = LiveMonsterList.erase(StartIter);
	}
}

BaseMonster::BaseMonster()
{

}

BaseMonster::~BaseMonster()
{

}

void BaseMonster::SetHPBarPos(float _LocalY)
{
	LifeBarBgLocalPos = { 0,_LocalY ,1 };
	LifeBarLocalPos = { 0,_LocalY };
	LifeBarBg->GetTransform()->SetLocalPosition(LifeBarLocalPos);
	LifeBar->GetTransform()->SetLocalPosition(LifeBarLocalPos);
}

std::shared_ptr<BaseMonster> BaseMonster::CreateMonster(const std::shared_ptr<GameEngineLevel> _Level, const MonsterEnum _Monster, std::vector<float4>& _PathInfo)
{
	std::shared_ptr<BaseMonster> Result = nullptr;

	switch (_Monster)
	{
	case MonsterEnum::DesertThug:
		Result = _Level->CreateActor<DesertThug>();
		break;
	case MonsterEnum::DuneRaider:
		Result = _Level->CreateActor<DuneRaider>();
		break;
	case MonsterEnum::Immortal:
		Result = _Level->CreateActor<Immortal>();
		break;
	case MonsterEnum::SandHound:
		Result = _Level->CreateActor<SandHound>();
		break;
	case MonsterEnum::WarHound:
		Result = _Level->CreateActor<WarHound>();
		break;
	case MonsterEnum::DuneTerror:
		Result = _Level->CreateActor<DuneTerror>();
		break;
	case MonsterEnum::GiantWasp:
		Result = _Level->CreateActor<GiantWasp>();
		break;
	case MonsterEnum::GiantWaspQueen:
		Result = _Level->CreateActor<GiantWaspQueen>();
		break;
	case MonsterEnum::GiantScorpion:
		Result = _Level->CreateActor<GiantScorpion>();
		break;
	case MonsterEnum::DessertArcher:
		Result = _Level->CreateActor<DessertArcher>();
		break;
	case MonsterEnum::Executioner:
		Result = _Level->CreateActor<Executioner>();
		break;
	case MonsterEnum::SandWraith:
		Result = _Level->CreateActor<SandWraith>();
		break;
	case MonsterEnum::Fallen:
		Result = _Level->CreateActor<Fallen>();
		break;
	default:
		MsgAssert("미구현");
		break;
	}

	Result->SetPathInfo(_PathInfo);
	return Result;
}


void BaseMonster::TestPath(float _DeltaTime)
{
	if (Walk.PathInfo == nullptr)
	{
		MsgAssert("몬스터의 경로가 지정되지 않아 이동할 수 없습니다.");
		return;
	}

	if (Walk.Ratio >= 1)
	{
		Walk.Time = 0;
		Walk.Ratio = 0;
		Walk.CurPoint++;
		Walk.NextPoint++;
	}

	if (Walk.NextPoint == Walk.PathInfo->end())
	{
		Death();
		LiveMonsterListRelease();
		return;
	}

	WalkToNextPoint(_DeltaTime);
}

void BaseMonster::Start()
{
	MonsterRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	MonsterCol = CreateComponent<GameEngineCollision>(ColOrder::Monster);
	LifeBarBg = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	LifeBarBg->SetTexture("lifebar_bg_small.png");
	LifeBarBg->GetTransform()->SetWorldScale(LifeBarScale);
	LifeBarBg->GetTransform()->SetLocalPosition(LifeBarLocalPos);
	LifeBar = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	LifeBar->SetTexture("lifebar_small.png");
	LifeBar->GetTransform()->SetWorldScale(LifeBarScale);
	LifeBar->GetTransform()->SetLocalPosition(LifeBarLocalPos);

	ParentLevel = GetLevel()->DynamicThis<PlayStageLevel>();

	LiveMonsterList.push_back(DynamicThis<BaseMonster>());
}

void BaseMonster::Update(float _DeltaTime)
{
	if (IsPause())
	{
		return;
	}

	if (IsTestMonster)
	{
		TestPath(_DeltaTime);
		return;
	}

	MonsterFSM.Update(_DeltaTime);
	UpdateLifeBar();
}

void BaseMonster::WalkToNextPoint(float _DeltaTime)
{
	//내가 점을 어떻게 찍던 상관 없이 속도는 일정해야한다...
	//기준 속력 V = 100 가정 (1초에 100을 간다는 뜻)
	//길이가 L = 200 일때 Time*0.5 = Time * (V/L)
	//길이가 100 일때 Time*1 = Time * (V/L)
	//길이가 50 일때 Time*2 = Time * (V/L)
	//길이가 25 일때 Time*4 = Time * (V/L)

	Walk.Time += _DeltaTime;
	Walk.Ratio = Walk.Time * (Data.Speed / (*Walk.NextPoint - *Walk.CurPoint).Size());
	Walk.ActorPos = float4::LerpClamp(*Walk.CurPoint, *Walk.NextPoint, Walk.Ratio);
	GetTransform()->SetWorldPosition(Walk.ActorPos);
}

void BaseMonster::WalkPath(float _DeltaTime)
{
	if (Walk.PathInfo == nullptr)
	{
		MsgAssert("몬스터의 경로가 지정되지 않아 이동할 수 없습니다.");
		return;
	}

	if (Walk.Ratio >= 1)
	{
		Walk.Time = 0;
		Walk.Ratio = 0;
		Walk.CurPoint++;
		Walk.NextPoint++;
	}

	if (Walk.NextPoint == Walk.PathInfo->end())
	{
		Death();
		LiveMonsterListRelease();
		dynamic_cast<PlayStageLevel*>(GetLevel())->SubLife(Data.LivesTaken);
		GiveBounty();
		return;
	}

	WalkToNextPoint(_DeltaTime);
}


void BaseMonster::LiveMonsterListRelease()
{
	std::list<std::weak_ptr<BaseMonster>>::iterator ReleaseStartIter = LiveMonsterList.begin();
	std::list<std::weak_ptr<BaseMonster>>::iterator ReleaseEndIter = LiveMonsterList.end();

	for (; ReleaseStartIter != ReleaseEndIter; )
	{
		if (false == ReleaseStartIter->lock()->IsDeath())
		{
			++ReleaseStartIter;
			continue;
		}

		ReleaseStartIter = LiveMonsterList.erase(ReleaseStartIter);
	}
}

void BaseMonster::CalMonsterDir()
{
	Walk.ActorDir.w = 0.0f;
	Walk.ActorDir = Walk.ActorPos - Walk.PrevActorPos;
	Walk.ActorDir.Normalize(); // 지름이 1인 원
	Walk.PrevActorPos = Walk.ActorPos;
	float DegZ = Walk.ActorDir.GetAnagleDegZ();

	if (DegZ > 45.f && DegZ <= 135.f)
	{
		Walk.DirString = "_Back";
	}
	else if (DegZ > 135.f && DegZ <= 225.f)
	{
		Walk.DirString = "_Profile";
		MonsterRenderer->GetTransform()->SetLocalNegativeScaleX();
	}
	else if (DegZ > 225.f && DegZ <= 315.f)
	{
		Walk.DirString = "_Front";
	}
	else if ((DegZ > 315.f && DegZ <= 360.f) || (DegZ >= 0.f && DegZ <= 45.f))
	{
		Walk.DirString = "_Profile";
		MonsterRenderer->GetTransform()->SetLocalPositiveScaleX();
	}
}

void BaseMonster::UpdateLifeBar()
{
	float4 CurHpBarXSize = float4::LerpClamp(float4{ 0,LifeBarScale.y,0,1 }, float4{ LifeBarScale.x,LifeBarScale.y,0,1 }, CurHP / Data.Hp);
	float4 CurHpBarXPos = float4::LerpClamp(float4{ -LifeBarScale.hx(),LifeBarLocalPos.y,0,1 }, float4{ 0,LifeBarLocalPos.y,0,1 }, CurHP / Data.Hp);
	LifeBar->GetTransform()->SetWorldScale(CurHpBarXSize);
	LifeBar->GetTransform()->SetLocalPosition(CurHpBarXPos);
}

void BaseMonster::GiveBounty()
{
	PlayManager::MainPlayer->Gold += Data.Bounty;
	//이펙트 추가 필요
}

void BaseMonster::PlayHumanDeathSound()
{
	if (DeathSoundPtr->IsValid())
	{
		bool Value = false;
		DeathSoundPtr->isPlaying(&Value);
		if (Value)
		{
			return;
		}
	}
	*DeathSoundPtr = GameEngineSound::Play("Sound_HumanDead" + std::to_string(GameEngineRandom::MainRandom.RandomInt(1, 4)) + ".ogg");
	DeathSoundPtr->SetVolume(0.2f);
}

void BaseMonster::PlayPuffDeathSound()
{
	if (DeathSoundPtr->IsValid())
	{
		bool Value = false;
		DeathSoundPtr->isPlaying(&Value);
		if (Value)
		{
			return;
		}
	}
	*DeathSoundPtr = GameEngineSound::Play("Sound_EnemyPuffDead.ogg");
	DeathSoundPtr->SetVolume(0.2f);
}

void BaseMonster::PlayExplosionDeathSound()
{
	if (DeathSoundPtr->IsValid())
	{
		bool Value = false;
		DeathSoundPtr->isPlaying(&Value);
		if (Value)
		{
			return;
		}
	}
	*DeathSoundPtr = GameEngineSound::Play("Sound_EnemyExplode1.ogg");
	DeathSoundPtr->SetVolume(0.1f);
}

void BaseMonster::PlayExecutionerDeathSound()
{
	if (DeathSoundPtr->IsValid())
	{
		bool Value = false;
		DeathSoundPtr->isPlaying(&Value);
		if (Value)
		{
			return;
		}
	}
	*DeathSoundPtr = GameEngineSound::Play("Sound_EnemyBigDead.ogg");
	DeathSoundPtr->SetVolume(0.2f);
}

void BaseMonster::PlayWraithDeathSound()
{
	if (DeathSoundPtr->IsValid())
	{
		bool Value = false;
		DeathSoundPtr->isPlaying(&Value);
		if (Value)
		{
			return;
		}
	}
	*DeathSoundPtr = GameEngineSound::Play("KRF_sfx_vodoo_kamikazelanza.ogg");
	DeathSoundPtr->SetVolume(0.2f);
}

bool BaseMonster::IsPause()
{
	return ParentLevel.lock()->IsPause;
}

float BaseMonster::CalDistance()
{
	return (*Walk.LastPoint - Walk.ActorPos).Size();
}

void BaseMonster::Attack()
{
	if (TargetFighter == nullptr)
	{
		return;
	}
	TargetFighter->CurHP -= CalDamage();
	TargetFighter->IsHit = true;
}

float BaseMonster::CalDamage()
{
	return static_cast<float>(GameEngineRandom::MainRandom.RandomInt(Data.Damage_min, Data.Damage_MAX));
}


