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
	FlagPosData.push_back({256,287});
	FlagPosData.push_back({388,305});
	FlagPosData.push_back({374,398});
	FlagPosData.push_back({279,435});
	FlagPosData.push_back({230,570});
	FlagPosData.push_back({533,733});

	Flags.reserve(6);
	Flags.push_back(WorldMapFlag::CreateFlag(GetLevel(), []()
		{

		}));
}
