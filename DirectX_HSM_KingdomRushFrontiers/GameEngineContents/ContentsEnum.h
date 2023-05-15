#pragma once

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

enum class ActorOrder
{
	Base,
	Monster,
};

enum class RenderOrder
{
	Bg,
	Tower,
	Shooter,
	Monster,
	BgObj,
	UI,
	MousePointer,
};