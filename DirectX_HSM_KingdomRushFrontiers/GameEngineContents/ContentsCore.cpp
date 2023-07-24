#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "TestLevel.h"
#include "TitleLevel.h"
#include "WorldMapLevel.h"
#include "PlayStageLevel.h"
#include "StageEditLevel.h"
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineFont.h>
#include <GameEnginePlatform\GameEngineInput.h>

GameEngineSoundPlayer ContentsCore::BGM = GameEngineSoundPlayer();

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::GameStart()
{
	ContentsResourcesCreate();
	LoadSound();
	InstallFont();
	GameEngineInput::MouseCursorOff();

	GameEngineCore::CreateLevel<TestLevel>();
	GameEngineCore::CreateLevel<PlayStageLevel>();
	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<WorldMapLevel>();
	GameEngineCore::CreateLevel<StageEditLevel>();
	GameEngineCore::ChangeLevel("TitleLevel");
}

void ContentsCore::GameEnd()
{
	RemoveFont();
}

void ContentsCore::BGMPlay(const std::string_view& _File)
{
	if (BGM.IsValid())
	{
		bool IsPlaying = false;
		BGM.isPlaying(&IsPlaying);
		if (IsPlaying)
		{
			BGM.Stop();
		}
	}

	BGM = GameEngineSound::Play(_File);
	BGM.SetLoop();
	BGM.SetVolume(0.2f);
}

void ContentsCore::BGMStop()
{
	BGM.Stop();
}

void ContentsCore::LoadSound()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("sounds");
	Dir.Move("Base");

	std::vector<GameEngineFile> File = Dir.GetAllFile({ ".ogg" });
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineSound::Load(File[i].GetFullPath());
	}
}

void ContentsCore::InstallFont()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("fonts");
	std::vector<GameEngineFile> FontFiles = Dir.GetAllFile({ ".otf", ".ttf" });
	for (GameEngineFile& File : FontFiles)
	{
		if (0 == AddFontResourceA(File.GetFullPath().c_str()))
		{
			MsgAssert("폰트 설치에 실패했습니다.");
			return;
		}

		SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, NULL, NULL);
	}
}

void ContentsCore::RemoveFont()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("fonts");
	std::vector<GameEngineFile> FontFiles = Dir.GetAllFile({ ".otf", ".ttf" });
	for (GameEngineFile& File : FontFiles)
	{
		if (0 == RemoveFontResourceA(File.GetFullPath().data()))
		{
			MsgAssert("폰트 삭제에 실패했습니다.");
			return;
		}

		SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, NULL, NULL);
	}
}



