#include "PrecompileHeader.h"
#include "ContentsData.h"

const float TowerData::Short = 140.f;
const float TowerData::Average = 160.f;
const float TowerData::Long = 180.f;
const float TowerData::Great = 198.f;
//const float TowerData::Extreme = ;

const float MonsterData::Def_None = 0.0f;
const float MonsterData::Def_Low = 0.3f;
const float MonsterData::Def_Midium = 0.5f;
const float MonsterData::Def_High = 0.85f;
const float MonsterData::Speed_Slow = 25.f;
const float MonsterData::Speed_Midium = 50.f;
const float MonsterData::Speed_Fast = 100.f;

const float4 StageData::Invisible = { 10000, 10000, -1000 };
const float4 StageData::Stage0_North_Path = { 744, 45, -1000 };
const float4 StageData::Stage0_South_Path = { 744, -10, -1000 };
const float4 StageData::Stage1_West = {-730, -230, -1000};
const float4 StageData::Stage1_East = { 387, -383, -1000 };
const float4 StageData::Stage2_North = {75, 398, -1000 };
const float4 StageData::Stage2_East = { 754, -129, -1000 };
const float4 StageData::Stage3_West = { -740, -255, -1000};
const float4 StageData::Stage3_East = { 743, -306, -1000 };
const float4 StageData::Stage4_West_Path = { 87, 304, -1000 };
const float4 StageData::Stage4_East_Path = { 139, 271, -1000 };
const float4 StageData::Stage4_East = { 550, 63, -1000 };
const float4 StageData::Stage5_NorthWest = { -742, 136, -1000 };
const float4 StageData::Stage5_West = { -742, -43, -1000 };
const float4 StageData::Stage5_East = { 739, -5, -1000 };

void StageData::SetButtonPos(int _Stage)
{
	if (_Stage == 0)
	{
		WaveStartButtonPos.resize(6);
		for (size_t i = 0; i < WaveStartButtonPos.size(); i++)
		{
			WaveStartButtonPos[i].resize(2);
		}

		for (size_t i = 0; i < WaveStartButtonPos.size(); i++)
		{
			for (size_t j = 0; j < WaveStartButtonPos[i].size(); j++)
			{
				if (j % 2 == 0)
				{
					WaveStartButtonPos[i][j] = Stage0_North_Path;
				}
				else if (j % 2 == 1)
				{
					WaveStartButtonPos[i][j] = Stage0_South_Path;
				}
			}
		}
	}
	else if (_Stage == 1)
	{
		WaveStartButtonPos.resize(8);
		for (size_t i = 0; i < WaveStartButtonPos.size(); i++)
		{
			WaveStartButtonPos[i].resize(2);
		}
		WaveStartButtonPos[0][0] = Stage1_West;
		WaveStartButtonPos[0][1] = Invisible;
		WaveStartButtonPos[1][0] = Invisible;
		WaveStartButtonPos[1][1] = Stage1_East;
		WaveStartButtonPos[2][0] = Stage1_West;
		WaveStartButtonPos[2][1] = Stage1_East;
		WaveStartButtonPos[3][0] = Invisible;
		WaveStartButtonPos[3][1] = Stage1_East;
		WaveStartButtonPos[4][0] = Stage1_West;
		WaveStartButtonPos[4][1] = Stage1_East;
		WaveStartButtonPos[5][0] = Stage1_West;
		WaveStartButtonPos[5][1] = Stage1_East;
		WaveStartButtonPos[6][0] = Stage1_West;
		WaveStartButtonPos[6][1] = Stage1_East;
		WaveStartButtonPos[7][0] = Stage1_West;
		WaveStartButtonPos[7][1] = Stage1_East;
	}
	else if (_Stage == 2)
	{
		WaveStartButtonPos.resize(10);
		for (size_t i = 0; i < WaveStartButtonPos.size(); i++)
		{
			WaveStartButtonPos[i].resize(2);
		}
		WaveStartButtonPos[0][0] = Stage2_North;
		WaveStartButtonPos[0][1] = Stage2_East;
		WaveStartButtonPos[1][0] = Invisible;
		WaveStartButtonPos[1][1] = Stage2_East;
		WaveStartButtonPos[2][0] = Stage2_North;
		WaveStartButtonPos[2][1] = Stage2_East;
		WaveStartButtonPos[3][0] = Invisible;
		WaveStartButtonPos[3][1] = Stage2_East;
		WaveStartButtonPos[4][0] = Stage2_North;
		WaveStartButtonPos[4][1] = Stage2_East;
		WaveStartButtonPos[5][0] = Stage2_North;
		WaveStartButtonPos[5][1] = Invisible;
		WaveStartButtonPos[6][0] = Stage2_North;
		WaveStartButtonPos[6][1] = Stage2_East;
		WaveStartButtonPos[7][0] = Stage2_North;
		WaveStartButtonPos[7][1] = Stage2_East;
		WaveStartButtonPos[8][0] = Stage2_North;
		WaveStartButtonPos[8][1] = Stage2_East;
		WaveStartButtonPos[9][0] = Stage2_North;
		WaveStartButtonPos[9][1] = Stage2_East;
	}
	else if (_Stage == 3)
	{
		WaveStartButtonPos.resize(14);
		for (size_t i = 0; i < WaveStartButtonPos.size(); i++)
		{
			WaveStartButtonPos[i].resize(2);
		}
		WaveStartButtonPos[0][0] = Stage3_West;
		WaveStartButtonPos[0][1] = Stage3_East;
		WaveStartButtonPos[1][0] = Stage3_West;
		WaveStartButtonPos[1][1] = Stage3_East;
		WaveStartButtonPos[2][0] = Stage3_West;
		WaveStartButtonPos[2][1] = Stage3_East;
		WaveStartButtonPos[3][0] = Invisible;
		WaveStartButtonPos[3][1] = Stage3_East;
		WaveStartButtonPos[4][0] = Stage3_West;
		WaveStartButtonPos[4][1] = Invisible;
		WaveStartButtonPos[5][0] = Stage3_West;
		WaveStartButtonPos[5][1] = Stage3_East;
		WaveStartButtonPos[6][0] = Stage3_West;
		WaveStartButtonPos[6][1] = Stage3_East;
		WaveStartButtonPos[7][0] = Stage3_West;
		WaveStartButtonPos[7][1] = Stage3_East;
		WaveStartButtonPos[8][0] = Stage3_West;
		WaveStartButtonPos[8][1] = Stage3_East;
		WaveStartButtonPos[9][0] = Stage3_West;
		WaveStartButtonPos[9][1] = Stage3_East;
		WaveStartButtonPos[10][0] = Invisible;
		WaveStartButtonPos[10][1] = Stage3_East;
		WaveStartButtonPos[11][0] = Stage3_West;
		WaveStartButtonPos[11][1] = Stage3_East;
		WaveStartButtonPos[12][0] = Stage3_West;
		WaveStartButtonPos[12][1] = Stage3_East;
		WaveStartButtonPos[13][0] = Stage3_West;
		WaveStartButtonPos[13][1] = Stage3_East;
	}
	else if (_Stage == 4)
	{
		WaveStartButtonPos.resize(15);
		for (size_t i = 0; i < WaveStartButtonPos.size(); i++)
		{
			WaveStartButtonPos[i].resize(3);
		}
		WaveStartButtonPos[0][0] = Stage4_West_Path;
		WaveStartButtonPos[0][1] = Stage4_East_Path;
		WaveStartButtonPos[0][2] = Invisible;
		WaveStartButtonPos[1][0] = Invisible;
		WaveStartButtonPos[1][1] = Stage4_East_Path;
		WaveStartButtonPos[1][2] = Invisible;
		WaveStartButtonPos[2][0] = Stage4_West_Path;
		WaveStartButtonPos[2][1] = Stage4_East_Path;
		WaveStartButtonPos[2][2] = Invisible;
		WaveStartButtonPos[3][0] = Stage4_West_Path;
		WaveStartButtonPos[3][1] = Stage4_East_Path;
		WaveStartButtonPos[3][2] = Invisible;
		WaveStartButtonPos[4][0] = Stage4_West_Path;
		WaveStartButtonPos[4][1] = Stage4_East_Path;
		WaveStartButtonPos[4][2] = Invisible;
		WaveStartButtonPos[5][0] = Invisible;
		WaveStartButtonPos[5][1] = Stage4_East_Path;
		WaveStartButtonPos[5][2] = Invisible;
		WaveStartButtonPos[6][0] = Stage4_West_Path;
		WaveStartButtonPos[6][1] = Stage4_East_Path;
		WaveStartButtonPos[6][2] = Invisible;
		WaveStartButtonPos[7][0] = Stage4_West_Path;
		WaveStartButtonPos[7][1] = Stage4_East_Path;
		WaveStartButtonPos[7][2] = Stage4_East;
		WaveStartButtonPos[8][0] = Stage4_West_Path;
		WaveStartButtonPos[8][1] = Stage4_East_Path;
		WaveStartButtonPos[8][2] = Stage4_East;
		WaveStartButtonPos[9][0] = Stage4_West_Path;
		WaveStartButtonPos[9][1] = Stage4_East_Path;
		WaveStartButtonPos[9][2] = Stage4_East;
		WaveStartButtonPos[10][0] = Invisible;
		WaveStartButtonPos[10][1] = Stage4_East_Path;
		WaveStartButtonPos[10][2] = Invisible;
		WaveStartButtonPos[11][0] = Stage4_West_Path;
		WaveStartButtonPos[11][1] = Stage4_East_Path;
		WaveStartButtonPos[11][2] = Invisible;
		WaveStartButtonPos[12][0] = Stage4_West_Path;
		WaveStartButtonPos[12][1] = Stage4_East_Path;
		WaveStartButtonPos[12][2] = Stage4_East;
		WaveStartButtonPos[13][0] = Stage4_West_Path;
		WaveStartButtonPos[13][1] = Stage4_East_Path;
		WaveStartButtonPos[13][2] = Stage4_East;
		WaveStartButtonPos[14][0] = Stage4_West_Path;
		WaveStartButtonPos[14][1] = Stage4_East_Path;
		WaveStartButtonPos[14][2] = Stage4_East;
	}
	else if (_Stage == 5)
	{
		WaveStartButtonPos.resize(14);
		for (size_t i = 0; i < WaveStartButtonPos.size(); i++)
		{
			WaveStartButtonPos[i].resize(3);
		}
		WaveStartButtonPos[0][0] = Stage5_NorthWest;
		WaveStartButtonPos[0][1] = Invisible;
		WaveStartButtonPos[0][2] = Stage5_East;
		WaveStartButtonPos[1][0] = Stage5_NorthWest;
		WaveStartButtonPos[1][1] = Stage5_West;
		WaveStartButtonPos[1][2] = Stage5_East;
		WaveStartButtonPos[2][0] = Stage5_NorthWest;
		WaveStartButtonPos[2][1] = Stage5_West;
		WaveStartButtonPos[2][2] = Stage5_East;
		WaveStartButtonPos[3][0] = Stage5_NorthWest;
		WaveStartButtonPos[3][1] = Invisible;
		WaveStartButtonPos[3][2] = Stage5_East;
		WaveStartButtonPos[4][0] = Stage5_NorthWest;
		WaveStartButtonPos[4][1] = Stage5_West;
		WaveStartButtonPos[4][2] = Stage5_East;
		WaveStartButtonPos[5][0] = Stage5_NorthWest;
		WaveStartButtonPos[5][1] = Stage5_West;
		WaveStartButtonPos[5][2] = Stage5_East;
		WaveStartButtonPos[6][0] = Stage5_NorthWest;
		WaveStartButtonPos[6][1] = Invisible;
		WaveStartButtonPos[6][2] = Stage5_East;
		WaveStartButtonPos[7][0] = Stage5_NorthWest;
		WaveStartButtonPos[7][1] = Invisible;
		WaveStartButtonPos[7][2] = Stage5_East;
		WaveStartButtonPos[8][0] = Stage5_NorthWest;
		WaveStartButtonPos[8][1] = Stage5_West;
		WaveStartButtonPos[8][2] = Stage5_East;
		WaveStartButtonPos[9][0] = Stage5_NorthWest;
		WaveStartButtonPos[9][1] = Stage5_West;
		WaveStartButtonPos[9][2] = Stage5_East;
		WaveStartButtonPos[10][0] = Stage5_NorthWest;
		WaveStartButtonPos[10][1] = Stage5_West;
		WaveStartButtonPos[10][2] = Stage5_East;
		WaveStartButtonPos[11][0] = Stage5_NorthWest;
		WaveStartButtonPos[11][1] = Stage5_West;
		WaveStartButtonPos[11][2] = Stage5_East;
		WaveStartButtonPos[12][0] = Stage5_NorthWest;
		WaveStartButtonPos[12][1] = Stage5_West;
		WaveStartButtonPos[12][2] = Stage5_East;
		WaveStartButtonPos[13][0] = Stage5_NorthWest;
		WaveStartButtonPos[13][1] = Stage5_West;
		WaveStartButtonPos[13][2] = Stage5_East;
	}
	else
	{
		return;
	}
}

void StageData::SetHeroStartPos(int _Stage)
{
	switch (_Stage)
	{
	case 0:
		HeroStartPos = {-458, 22, 22};
		break;
	case 1:
		HeroStartPos = {97, 398, 398};
		break;
	case 2:
		HeroStartPos = {-545, -52, -52};
		break;
	case 3:
		HeroStartPos = {-30, 410, 410};
		break;
	case 4:
		HeroStartPos = {-531, -241, -241};
		break;
	case 5:
		HeroStartPos = {24, -380, -380};
		break;
	default:
		break;
	}
}
