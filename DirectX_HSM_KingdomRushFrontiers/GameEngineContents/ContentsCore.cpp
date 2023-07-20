#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "TestLevel.h"
#include "TitleLevel.h"
#include "WorldMapLevel.h"
#include "PlayStageLevel.h"
#include "StageEditLevel.h"
#include <GameEngineCore/GameEngineCoreWindow.h>

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

	GameEngineCore::CreateLevel<TestLevel>();
	GameEngineCore::CreateLevel<PlayStageLevel>();
	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<WorldMapLevel>();
	GameEngineCore::CreateLevel<StageEditLevel>();

	GameEngineCore::ChangeLevel("TitleLevel");
}

void ContentsCore::GameEnd()
{

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
