#pragma once

enum class ActorOrder
{
	Base,
	Monster,
};

enum class RenderOrder
{
	Bg = -1000,
	Tower = 0,
	Shooter,
	Monster,
	BgObj,
	UI,
	MousePointer,
};

enum class ColOrder
{
	TowerRange,
	Monster,
	UI,
	MousePointer,
	Tower,
};

enum class MonsterEnum
{
	Null = -1,
	DesertThug,
	DuneRaider,
	DesertArcher,
	SandHound,
	WarHound,
	Immortal,
	Fallen,
	Executioner,
	GiantScorpion,
	GiantWasp,
	GiantWaspQueen,
	DuneTerror,
	SandWraith
};

enum class StageEditMode
{
	Null,
	PathEdit,
};

enum class TowerEnum
{
	Null = -1,
	RangedTower_Level1,
	RangedTower_Level2,
	RangedTower_Level3,
	RangedTower_Level4,
	MeleeTower_Level1,
	MeleeTower_Level2,
	MeleeTower_Level3,
	MeleeTower_Level4,
	MagicTower_Level1,
	MagicTower_Level2,
	MagicTower_Level3,
	MagicTower_Level4,
	ArtilleryTower_Level1,
	ArtilleryTower_Level2,
	ArtilleryTower_Level3,
	ArtilleryTower_Level4,
};