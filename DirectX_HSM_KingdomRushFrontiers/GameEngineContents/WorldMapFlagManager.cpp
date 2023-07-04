#include "PrecompileHeader.h"
#include "WorldMapFlagManager.h"

#include "WorldMapFlag.h"

WorldMapFlagManager::WorldMapFlagManager()
{

}

WorldMapFlagManager::~WorldMapFlagManager()
{

}

void WorldMapFlagManager::Start()
{
	FlagPosData.reserve(6);
	FlagPosData.push_back(WinToDec({ 256,287 }));
	FlagPosData.push_back(WinToDec({388,305}));
	FlagPosData.push_back(WinToDec({374,398}));
	FlagPosData.push_back(WinToDec({279,435}));
	FlagPosData.push_back(WinToDec({230,570}));
	FlagPosData.push_back(WinToDec({533,733}));

	Flags.reserve(6);
	for (size_t i = 0; i < Flags.capacity(); i++)
	{
		Flags.push_back(WorldMapFlag::CreateFlag(this, []()
			{

			}));
		Flags[i]->GetTransform()->SetLocalPosition(FlagPosData[i]);
	}
}

float4 WorldMapFlagManager::WinToDec(const float4& _Win)
{
	return float4{ _Win.x - 800.f, 450.f - _Win.y };
}
