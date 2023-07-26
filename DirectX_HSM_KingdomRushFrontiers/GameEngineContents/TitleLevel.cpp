#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform\GameEngineSound.h>

#include "ContentsCore.h"
#include "TitleBackground.h"
#include "TitleMenuManager.h"
#include "Title_MousePointer.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::Start()
{
	LoadTexture();
	LoadSound();
	
	std::shared_ptr _101Camera = CreateNewCamera(101);
	_101Camera->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);
	
	AcTitleBackground = CreateActor<TitleBackground>();
	AcTitleMenu = CreateActor<TitleMenuManager>();
	AcTitleMenu->GetTransform()->SetLocalPosition(TitleMenuLocPos);
	AcMousePointer = CreateActor<Title_MousePointer>();
	
	GameEngineInput::CreateKey("TestLevel",VK_ESCAPE);
}

void TitleLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("TestLevel"))
	{
		GameEngineCore::ChangeLevel("TestLevel");
	}

	if (GameEngineInput::IsUp("V"))
	{
		IsDebugSwitch();
	}
}

void TitleLevel::LevelChangeStart()
{
	ContentsCore::BGMPlay("savage_music_theme.ogg");
}

void TitleLevel::LevelChangeEnd()
{
	ContentsCore::BGMStop();
}

void TitleLevel::LoadTexture()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("1.TITLE LEVEL");

	std::vector<GameEngineFile> File = Dir.GetAllFile({ ".png" });
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineTexture::Load(File[i].GetFullPath());
	}
}

void TitleLevel::LoadSound()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("sounds");
	Dir.Move("Title");

	std::vector<GameEngineFile> File = Dir.GetAllFile({ ".ogg" });
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineSound::Load(File[i].GetFullPath());
	}
}
