#include "PrecompileHeader.h"
#include "WorldMapLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "Background.h"
#include "WorldMap.h"
#include "UpgradeMenu.h"
#include "StageSelectMenu.h"

WorldMapLevel::WorldMapLevel()
{

}

WorldMapLevel::~WorldMapLevel()
{

}

void WorldMapLevel::Start()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("2.WORLDMAP LEVEL");
	
	std::vector<GameEngineFile> File = Dir.GetAllFile({ ".png" });
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineTexture::Load(File[i].GetFullPath());
	}

	AcBg = CreateActor<Background>();
	//AcWorldMap = CreateActor<WorldMap>();
	//AcUpgradeMenu = CreateActor<UpgradeMenu>();
	AcStageSelectMenu = CreateActor<StageSelectMenu>();

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
}

void WorldMapLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("TestLevel"))
	{
		GameEngineCore::ChangeLevel("TestLevel");
	}
}
