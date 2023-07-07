#include "PrecompileHeader.h"
#include "WorldMapLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore\GameEngineSprite.h>
#include <GameEngineCore\GameEngineFont.h>

#include "WorldMapBg.h"
#include "WorldMapFlagManager.h"
#include "SelectStageWindow.h"
#include "_101UIRenderer.h"

bool WorldMapLevel::IsPause = false;

WorldMapLevel::WorldMapLevel()
{

}

WorldMapLevel::~WorldMapLevel()
{

}

void WorldMapLevel::Start()
{
	std::shared_ptr _101Camera = CreateNewCamera(101);
	_101Camera->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

    LoadWorldMapTexture("WorldMapBg");
    LoadWorldMapTexture("SelectStage");
	LoadWorldMapAnimation();
	LoadFont();

    AcWorldMapBg = CreateActor<WorldMapBg>();
	AcFlags = CreateActor<WorldMapFlagManager>();
	AcSelectStageWindow = CreateActor<SelectStageWindow>();
	PauseFade = CreateActor<GameEngineActor>()->CreateComponent<_101UIRenderer>(UIRenderOrder::Bg);
	PauseFade->SetTexture("PauseBg.png");
	PauseFade->GetTransform()->SetWorldScale({ 1650,928,1 });
	PauseFade->Off();
	

}

void WorldMapLevel::Update(float _DeltaTime)
{
	PauseProcess();
	if (GameEngineInput::IsDown("TestLevel"))
	{
		GameEngineCore::ChangeLevel("TestLevel");
	}
}

void WorldMapLevel::LevelChangeStart()
{
	GameEngineTime::GlobalTime.SetUpdateOrderTimeScale(ActorOrder::Base, 1.0f);
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

	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Flag_Clear_Appear").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Flag_Clear_Hover").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Flag_Clear_Release").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("FlagStar").GetFullPath());

	Dir.MoveParentToDirectory("PathDot");
	Dir.Move("PathDot");
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("PathDot_Blue").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("PathDot_Red").GetFullPath());
}

void WorldMapLevel::PauseProcess()
{
	if (IsPause)
	{
		PauseFade->On();
	}
	else
	{
		PauseFade->Off();
	}
}

void WorldMapLevel::LoadFont()
{
	GameEngineFont::Load("TOONISH");
	GameEngineFont::Load("³ª´®¼Õ±Û¾¾ Ææ OTF");
	GameEngineFont::Load("Á¦ÁÖÇÑ¶ó»ê");
	GameEngineFont::Load("¹è´ÞÀÇ¹ÎÁ· ¿¬¼º OTF");
}