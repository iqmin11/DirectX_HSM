#pragma once
#include "ContentsEnum.h"

class LinePath
{
public:
	std::vector<float4> Points = std::vector<float4>();
};

class MonsterSpawnData
{
public:
	MonsterSpawnData() {}
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

class StageData
{
public:
	//int StageLevel = 0;
	//std::string BackGroundName = "\0";
	std::vector<LinePath> Lines = std::vector<LinePath>();
	std::vector<WaveData> Waves = std::vector<WaveData>();
	std::vector<float4> BuildAreaPos = std::vector<float4>();
	std::vector<float4> AreaStartRallyPos = std::vector<float4>();
	std::vector<std::vector<float4>> WaveStartButtonPos = std::vector<std::vector<float4>>();
	int StartGold = -1;
	float4 HeroStartPos = float4::Null;

	static const float4 Invisible;
	static const float4 Stage0_North_Path;
	static const float4 Stage0_South_Path;
	static const float4 Stage1_West;
	static const float4 Stage1_East;
	static const float4 Stage2_North;
	static const float4 Stage2_East;
	static const float4 Stage3_West;
	static const float4 Stage3_East;
	static const float4 Stage4_West_Path;
	static const float4 Stage4_East_Path;
	static const float4 Stage4_East;
	static const float4 Stage5_NorthWest;
	static const float4 Stage5_West;
	static const float4 Stage5_East;

	void SetButtonPos(int _Stage);
	void SetHeroStartPos(int _Stage);
};

class TowerData
{
public:
	static const float Short;
	static const float Average;
	static const float Long;
	static const float Great;
	static const float Extreme;

	TowerData GetNextTowerData();

	float GetNextLvRange()
	{
		TowerEnum NextEnum = static_cast<TowerEnum>(static_cast<int>(TowerType) + Level + 1);
		TowerData NextData = TowerData();
		NextData.SetData(NextEnum);
		if (NextData.TowerType != TowerType)
		{
			MsgAssert("인덱스를 넘어간 타워 레벨");
		}

		return NextData.Range;
	}

	void SetData(TowerEnum _Enum)
	{
		switch (_Enum)
		{
		case TowerEnum::Null:
			break;
		case TowerEnum::RangedTower_Level1:
			TowerType = TowerEnum::RangedTower;
			Level = 1;
			FireRate = 0.8f;
			Range = Short;
			Damage_min = 4;
			Damage_MAX = 6;
			BulletTime = 1.0f;
			BuildCost = 70;
			SellCost = 70;
			break;
		case TowerEnum::RangedTower_Level2:
			TowerType = TowerEnum::RangedTower;
			Level = 2;
			FireRate = 0.6f;
			Range = Average;
			Damage_min = 7;
			Damage_MAX = 11;
			BulletTime = 1.0f;
			BuildCost = 110;
			SellCost = 180;
			break;
		case TowerEnum::RangedTower_Level3:
			TowerType = TowerEnum::RangedTower;
			Level = 3;
			FireRate = 0.5f;
			Range = Long;
			Damage_min = 10;
			Damage_MAX = 16;
			BulletTime = 1.0f;
			BuildCost = 160;
			SellCost = 340;
			break;
		case TowerEnum::RangedTower_Level4:
			TowerType = TowerEnum::RangedTower;
			Level = 4;
			FireRate = 0.5f;
			Range = Great;
			Damage_min = 15;
			Damage_MAX = 23;
			BulletTime = 1.0f;
			BuildCost = 230;
			SellCost = 570;
			break;
		case TowerEnum::MeleeTower_Level1:
			TowerType = TowerEnum::MeleeTower;
			Level = 1;
			FireRate = 1.0f;
			Range = Short;
			Damage_min = 1;
			Damage_MAX = 3;
			BuildCost = 70;
			SellCost = 70;
			break;
		case TowerEnum::MeleeTower_Level2:
			TowerType = TowerEnum::MeleeTower;
			Level = 2;
			FireRate = 1.36f;
			Range = Short;
			Damage_min = 3;
			Damage_MAX = 4;
			BuildCost = 110;
			SellCost = 180;
			break;
		case TowerEnum::MeleeTower_Level3:
			TowerType = TowerEnum::MeleeTower;
			Level = 3;
			FireRate = 1.36f;
			Range = Short;
			Damage_min = 6;
			Damage_MAX = 10;
			BuildCost = 160;
			SellCost = 340;
			break;
		case TowerEnum::MeleeTower_Level4:
			TowerType = TowerEnum::MeleeTower;
			Level = 4;
			FireRate = 1.0f;
			Range = Short;
			Damage_min = 10;
			Damage_MAX = 14;
			BuildCost = 230;
			SellCost = 570;
			break;
		case TowerEnum::MagicTower_Level1:
			TowerType = TowerEnum::MagicTower;
			Level = 1;
			FireRate = 1.5f;
			Range = Short;
			Damage_min = 9;
			Damage_MAX = 17;
			BulletTime = 0.4f;
			BuildCost = 100;
			SellCost = 100;
			break;
		case TowerEnum::MagicTower_Level2:
			TowerType = TowerEnum::MagicTower;
			Level = 2;
			FireRate = 1.5f;
			Range = Average;
			Damage_min = 23;
			Damage_MAX = 43;
			BulletTime = 0.4f;
			BuildCost = 160;
			SellCost = 260;
			break;
		case TowerEnum::MagicTower_Level3:
			TowerType = TowerEnum::MagicTower;
			Level = 3;
			FireRate = 1.5f;
			Range = Long;
			Damage_min = 40;
			Damage_MAX = 74;
			BulletTime = 0.4f;
			BuildCost = 240;
			SellCost = 500;
			break;
		case TowerEnum::MagicTower_Level4:
			TowerType = TowerEnum::MagicTower;
			Level = 4;
			FireRate = 1.5f;
			Range = Great;
			Damage_min = 60;
			Damage_MAX = 120;
			BulletTime = 0.4f;
			BuildCost = 300;
			SellCost = 800;
			break;
		case TowerEnum::ArtilleryTower_Level1:
			TowerType = TowerEnum::ArtilleryTower;
			Level = 1;
			FireRate = 3.0f;
			Range = Average;
			Damage_min = 8;
			Damage_MAX = 15;
			BulletTime = 1.0f;
			BuildCost = 125;
			SellCost = 125;
			break;
		case TowerEnum::ArtilleryTower_Level2:
			TowerType = TowerEnum::ArtilleryTower;
			Level = 2;
			FireRate = 3.0f;
			Range = Average;
			Damage_min = 20;
			Damage_MAX = 40;
			BulletTime = 1.0f;
			BuildCost = 220;
			SellCost = 345;
			break;
		case TowerEnum::ArtilleryTower_Level3:
			TowerType = TowerEnum::ArtilleryTower;
			Level = 3;
			FireRate = 3.0f;
			Range = Long;
			Damage_min = 30;
			Damage_MAX = 60;
			BulletTime = 1.0f;
			BuildCost = 320;
			SellCost = 665;
			break;
		case TowerEnum::ArtilleryTower_Level4:
			TowerType = TowerEnum::ArtilleryTower;
			Level = 4;
			FireRate = 3.0f;
			Range = Long;
			Damage_min = 25;
			Damage_MAX = 45;
			BulletTime = 1.0f;
			BuildCost = 400;
			SellCost = 1065;
			break;
		default:
			MsgAssert("잘못된 TowerTypeEnum값을 넣었습니다.")
			break;
		}
	}

public:
	TowerEnum TowerType = TowerEnum::Null;
	int Level = 0;
	float FireRate = 0.0f;
	float Range = 0.0f;
	int Damage_min = 0;
	int Damage_MAX = 0;
	float BulletTime = 1.0f;
	int BuildCost = 0;
	int SellCost = 0;
};

class MonsterData
{
public:
	static const float Def_None;
	static const float Def_Low;
	static const float Def_Midium;
	static const float Def_High;
	static const float Speed_Slow;
	static const float Speed_Midium;
	static const float Speed_Fast;

	void SetData(MonsterEnum _MonsterType)
	{
		switch (_MonsterType)
		{
		case MonsterEnum::Null:
			break;
		case MonsterEnum::DesertThug:
			MonsterType = _MonsterType;
			Hp = 50;
			AttackRate = 1.0f;
			Damage_min = 2;
			Damage_MAX = 6;
			Armor = Def_None;
			MagicResistance = Def_None;
			Speed = Speed_Midium;
			Dodge = 0.0f;
			LivesTaken = 1;
			Bounty = 5;
			IsBurrow = false;
			IsFlying = false;
			IsRanged = false;
			break;
		case MonsterEnum::DuneRaider:
			MonsterType = _MonsterType;
			Hp = 160;
			AttackRate = 1.2f;
			Damage_min = 6;
			Damage_MAX = 10;
			Armor = Def_Low;
			MagicResistance = Def_None;
			Speed = Speed_Midium;
			Dodge = 0.0f;
			LivesTaken = 1;
			Bounty = 16;
			IsBurrow = false;
			IsFlying = false;
			IsRanged = false;
			break;
		case MonsterEnum::DessertArcher:
			MonsterType = _MonsterType;
			Hp = 150;
			AttackRate = 1.0f;
			Damage_min = 10;
			Damage_MAX = 20;
			RangedAttackRate = 1.4f;
			RangedDamage_min = 20;
			RangedDamage_MAX = 30;
			Armor = Def_None;
			MagicResistance = Def_Low;
			Speed = Speed_Midium;
			Dodge = 0.0f;
			LivesTaken = 1;
			Bounty = 12;
			IsBurrow = false;
			IsFlying = false;
			IsRanged = true;
			break;
		case MonsterEnum::SandHound:
			MonsterType = _MonsterType;
			Hp = 30;
			AttackRate = 1.0f;
			Damage_min = 1;
			Damage_MAX = 3;
			Armor = Def_None;
			MagicResistance = Def_None;
			Speed = Speed_Fast;
			Dodge = 0.25f;
			LivesTaken = 1;
			Bounty = 5;
			IsBurrow = false;
			IsFlying = false;
			IsRanged = false;
			break;
		case MonsterEnum::WarHound:
			MonsterType = _MonsterType;
			Hp = 100;
			AttackRate = 1.5f;
			Damage_min = 12;
			Damage_MAX = 18;
			Armor = Def_None;
			MagicResistance = Def_Midium;
			Speed = Speed_Fast;
			Dodge = 0.3f;
			LivesTaken = 1;
			Bounty = 10;
			IsBurrow = false;
			IsFlying = false;
			IsRanged = false;
			break;
		case MonsterEnum::Immortal:
			MonsterType = _MonsterType;
			Hp = 290;
			AttackRate = 1.5f;
			Damage_min = 12;
			Damage_MAX = 28;
			Armor = Def_Midium;
			MagicResistance = Def_None;
			Speed = Speed_Midium;
			Dodge = 0.0f;
			LivesTaken = 2;
			Bounty = 24;
			IsBurrow = false;
			IsFlying = false;
			IsRanged = false;
			break;
		case MonsterEnum::Fallen:
			MonsterType = _MonsterType;
			Hp = 100;
			AttackRate = 1.0f;
			Damage_min = 12;
			Damage_MAX = 28;
			Armor = Def_None;
			MagicResistance = Def_None;
			Speed = Speed_Midium;
			Dodge = 0.0f;
			LivesTaken = 1;
			Bounty = 0;
			IsBurrow = false;
			IsFlying = false;
			IsRanged = false;
			break;
		case MonsterEnum::Executioner:
			MonsterType = _MonsterType;
			Hp = 1600;
			AttackRate = 1.5f;
			Damage_min = 30;
			Damage_MAX = 60;
			Armor = Def_None;
			MagicResistance = Def_None;
			Speed = Speed_Slow;
			Dodge = 0.0f;
			LivesTaken = 2;
			Bounty = 130;
			IsBurrow = false;
			IsFlying = false;
			IsRanged = false;
			break;
		case MonsterEnum::GiantScorpion:
			MonsterType = _MonsterType;
			Hp = 400;
			AttackRate = 1.0f;
			Damage_min = 12;
			Damage_MAX = 28;
			Armor = Def_High;
			MagicResistance = Def_None;
			Speed = Speed_Slow;
			Dodge = 0.0f;
			LivesTaken = 2;
			Bounty = 28;
			IsBurrow = false;
			IsFlying = false;
			IsRanged = false;
			break;
		case MonsterEnum::GiantWasp:
			MonsterType = _MonsterType;
			Hp = 70;
			Armor = Def_None;
			MagicResistance = Def_None;
			Speed = Speed_Midium;
			Dodge = 0.0f;
			LivesTaken = 1;
			Bounty = 8;
			IsBurrow = false;
			IsFlying = true;
			IsRanged = false;
			break;
		case MonsterEnum::GiantWaspQueen:
			MonsterType = _MonsterType;
			Hp = 320;
			Armor = Def_None;
			MagicResistance = Def_None;
			Speed = Speed_Midium;
			Dodge = 0.0f;
			LivesTaken = 5;
			Bounty = 40;
			IsBurrow = false;
			IsFlying = true;
			IsRanged = false;
			break;
		case MonsterEnum::DuneTerror:
			MonsterType = _MonsterType;
			Hp = 100;
			AttackRate = 1.0f;
			Damage_min = 4;
			Damage_MAX = 8;
			Armor = Def_None;
			MagicResistance = Def_None;
			Speed = Speed_Midium;
			Dodge = 0.0f;
			LivesTaken = 1;
			Bounty = 10;
			IsBurrow = true;
			IsFlying = false;
			IsRanged = false;
			break;
		case MonsterEnum::SandWraith:
			MonsterType = _MonsterType;
			Hp = 800;
			AttackRate = 1.0f;
			Damage_min = 30;
			Damage_MAX = 60;
			RangedAttackRate = 1.3f;
			RangedDamage_min = 20;
			RangedDamage_MAX = 40;
			Armor = Def_None;
			MagicResistance = Def_None;
			Speed = Speed_Slow;
			Dodge = 0.0f;
			LivesTaken = 1;
			Bounty = 100;
			IsBurrow = false;
			IsFlying = false;
			IsRanged = true;
			break;
		default:
			break;
		}
	}

public:
	MonsterEnum MonsterType = MonsterEnum::Null;
	float Hp = 0;
	float AttackRate = -1;
	int Damage_min = -1;
	int Damage_MAX = -1;
	float RangedAttackRate = -1;
	int RangedDamage_min = -1;
	int RangedDamage_MAX = -1;
	float Armor = 0.0f;
	float MagicResistance = 0.0f;
	float Speed = 0.0f;
	float Dodge = 0.0f;
	int LivesTaken = 0;
	int Bounty = 0;
	bool IsBurrow = false;
	bool IsFlying = false;
	bool IsRanged= false;
};


class FighterData
{
public:
	void SetData(int _TowerLevel)
	{
		if (_TowerLevel <= 0 && _TowerLevel > 4)
		{
			MsgAssert("타워레벨 인덱스를 벗어났습니다.")
		}
		SetData(static_cast<FighterEnum>(_TowerLevel));
	}
	
	void SetData(FighterEnum _FighterEnum)
	{
		switch (_FighterEnum)
		{
		case FighterEnum::MeleeLv1:
			FighterType = FighterEnum::Melee;
			Level = 1;
			Hp = 50.f;
			AttackRate = 1.0f;
			Damage_min = 1;
			Damage_MAX = 3;
			RangedAttackRate = -1;
			RangedDamage_min = -1;
			RangedDamage_MAX = -1;
			Armor = 0.0f;
			break;
		case FighterEnum::MeleeLv2:
			FighterType = FighterEnum::Melee;
			Level = 2;
			Hp = 100.f;
			AttackRate = 1.36f;
			Damage_min = 3;
			Damage_MAX = 4;
			RangedAttackRate = -1;
			RangedDamage_min = -1;
			RangedDamage_MAX = -1;
			Armor = 0.15f;
			break;
		case FighterEnum::MeleeLv3:
			FighterType = FighterEnum::Melee;
			Level = 3;
			Hp = 150.f;
			AttackRate = 1.36f;
			Damage_min = 6;
			Damage_MAX = 10;
			RangedAttackRate = -1;
			RangedDamage_min = -1;
			RangedDamage_MAX = -1;
			Armor = 0.3f;
			break;
		case FighterEnum::MeleeLv4:
			FighterType = FighterEnum::Melee;
			Level = 4;
			Hp = 200.f;
			AttackRate = 1.0f;
			Damage_min = 10;
			Damage_MAX = 14;
			RangedAttackRate = -1;
			RangedDamage_min = -1;
			RangedDamage_MAX = -1;
			Armor = 0.0f;
			break;
		case FighterEnum::ReinforceLv0:
			FighterType = FighterEnum::Reinforce;
			Level = 0;
			Hp = 30.f;
			AttackRate = 1.0f;
			Damage_min = 1;
			Damage_MAX = 2;
			RangedAttackRate = -1;
			RangedDamage_min = -1;
			RangedDamage_MAX = -1;
			Armor = 0.0f;
			break;
		case FighterEnum::ReinforceLv1:
			FighterType = FighterEnum::Reinforce;
			Level = 1;
			Hp = 50.f;
			AttackRate = 1.0f;
			Damage_min = 1;
			Damage_MAX = 3;
			RangedAttackRate = -1;
			RangedDamage_min = -1;
			RangedDamage_MAX = -1;
			Armor = 0.0f;
			break;
		case FighterEnum::ReinforceLv2:
			FighterType = FighterEnum::Reinforce;
			Level = 2;
			Hp = 70.f;
			AttackRate = 1.0f;
			Damage_min = 2;
			Damage_MAX = 4;
			RangedAttackRate = -1;
			RangedDamage_min = -1;
			RangedDamage_MAX = -1;
			Armor = 0.1f;
			break;
		case FighterEnum::ReinforceLv3:
			FighterType = FighterEnum::Reinforce;
			Level = 3;
			Hp = 90.f;
			AttackRate = 1.0f;
			Damage_min = 3;
			Damage_MAX = 6;
			RangedAttackRate = -1;
			RangedDamage_min = -1;
			RangedDamage_MAX = -1;
			Armor = 0.2f;
			break;
		case FighterEnum::ReinforceLv4:
			FighterType = FighterEnum::Reinforce;
			Level = 4;
			Hp = 110.f;
			AttackRate = 1.0f;
			Damage_min = 6;
			Damage_MAX = 10;
			RangedAttackRate = -1;
			RangedDamage_min = -1;
			RangedDamage_MAX = -1;
			Armor = 0.3f;
			break;
		case FighterEnum::ReinforceLv5:
			FighterType = FighterEnum::Reinforce;
			Level = 5;
			Hp = 110.f;
			AttackRate = 1.0f;
			Damage_min = 6;
			Damage_MAX = 10;
			RangedAttackRate = 1.4f;
			RangedDamage_min = 16;
			RangedDamage_MAX = 30;
			Armor = 0.3f;
			break;
		case FighterEnum::Hero_Alric:
			FighterType = FighterEnum::Hero;
			Level = 10;
			Hp = 560.f;
			AttackRate = 1.0f;
			Damage_min = 27;
			Damage_MAX = 40;
			RangedAttackRate = -1.f;
			RangedDamage_min = -1;
			RangedDamage_MAX = -1;
			Armor = 0.65f;
			break;
		case FighterEnum::Creature_Sandman:
			FighterType = FighterEnum::Creature;
			Level = 3;
			Hp = 140.f;
			AttackRate = 1.0f;
			Damage_min = 2;
			Damage_MAX = 6;
			RangedAttackRate = -1.f;
			RangedDamage_min = -1;
			RangedDamage_MAX = -1;
			Armor = 0.0f;
			break;
		default:
			MsgAssert("엉뚱한 FighterEnum값을 넣었습니다.")
			break;
		}
	}

public:
	FighterEnum FighterType = FighterEnum::Null;
	int Level = -1;
	float Hp = 0.f;
	float AttackRate = -1.0f;
	int Damage_min = -1;
	int Damage_MAX = -1;
	float RangedAttackRate = -1.f;
	int RangedDamage_min = -1;
	int RangedDamage_MAX = -1;
	float Armor = -1.0f;
};

class PlayerData
{	
public:
	int ReinforceLevel = -1;
};