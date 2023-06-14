#pragma once

enum class ActorOrder
{
	Base,
	Monster,
};

enum class RenderOrder
{
	Bg = -10000,
	Ground = -1000,
	Mob = 1,
	Shooter,
	//Monster,
	//Bullet,
	BgObj,
	UI,
	MousePointer,
};

enum class UIRenderOrder
{
	Null = -1,
	TowerButton,
	TowerRange,
	BuildBarBg,
	BuildBar,
	TowerUI,
	TowerUIButton,
	StageUI,
	MousePoint
};

enum class ColOrder
{
	TowerRange,
	Monster,
	UI,
	MousePointer,
	Tower,
	Bullet,
	Fighter,
	Button,
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
	RangedTower,
	RangedTower_Level1,
	RangedTower_Level2,
	RangedTower_Level3,
	RangedTower_Level4,
	MeleeTower,
	MeleeTower_Level1,
	MeleeTower_Level2,
	MeleeTower_Level3,
	MeleeTower_Level4,
	MagicTower,
	MagicTower_Level1,
	MagicTower_Level2,
	MagicTower_Level3,
	MagicTower_Level4,
	ArtilleryTower,
	ArtilleryTower_Level1,
	ArtilleryTower_Level2,
	ArtilleryTower_Level3,
	ArtilleryTower_Level4,
};

enum class FighterEnum
{
	Null = -1,
	Melee,
	MeleeLv1,
	MeleeLv2,
	MeleeLv3,
	MeleeLv4,
	Reinforce,
	ReinforceLv0,
	ReinforceLv1,
	ReinforceLv2,
	ReinforceLv3,
	ReinforceLv4,
	ReinforceLv5,
};

enum class ButtonState
{
	Release,
	Press,
	Hover,
};

enum class HitState
{
	Etc,
	Arrow,
	Melee,
	Bolt,
	Bomb,
};