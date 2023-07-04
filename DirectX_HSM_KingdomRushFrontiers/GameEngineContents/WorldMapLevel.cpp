#include "PrecompileHeader.h"
#include "WorldMapLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore\GameEngineSprite.h>

#include "WorldMapBg.h"
#include "WorldMapFlagManager.h"

WorldMapLevel::WorldMapLevel()
{

}

WorldMapLevel::~WorldMapLevel()
{

}

void WorldMapLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

    LoadWorldMapTexture("WorldMapBg");
	LoadWorldMapAnimation();

    AcWorldMapBg = CreateActor<WorldMapBg>();
	AcFlags = CreateActor<WorldMapFlagManager>();
}

void WorldMapLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("TestLevel"))
	{
		GameEngineCore::ChangeLevel("TestLevel");
	}
}

void WorldMapLevel::LoadWorldMapTexture(std::string_view _Folder)
{
 	GameEngineDirectory Dir;
 	Dir.MoveParentToDirectory("ContentsResources");
 	Dir.Move("ContentsResources");
    Dir.Move("2.WORLDMAP LEVEL");
    Dir.Move(_Folder);
 
 	std::vector<GameEngineFile> File = Dir.GetAllFile({ ".png" });
 	for (size_t i = 0; i < File.size(); i++)
 	{
 		GameEngineTexture::Load(File[i].GetFullPath());
 	}
}

void WorldMapLevel::LoadWorldMapAnimation()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("2.WORLDMAP LEVEL");
	Dir.Move("MapFlag");

	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Flag_BeforClear_Appear").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Flag_BeforClear_Hover").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Flag_BeforClear_Release").GetFullPath());

	Dir.MoveParentToDirectory("PathDot");
	Dir.Move("PathDot");
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("PathDot_Blue").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("PathDot_Red").GetFullPath());
}
