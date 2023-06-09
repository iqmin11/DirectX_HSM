#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "TestLevel.h"
#include "TitleLevel.h"
#include "WorldMapLevel.h"
#include "PlayStageLevel.h"
#include "StageEditLevel.h"
#include <GameEngineCore/GameEngineCoreWindow.h>

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
	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<WorldMapLevel>();
	GameEngineCore::CreateLevel<PlayStageLevel>();
	GameEngineCore::CreateLevel<StageEditLevel>();

	GameEngineCore::ChangeLevel("TitleLevel");
}

void ContentsCore::GameEnd()
{

}