#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
//#include "TestLevel.h"
#include "TitleLevel.h"
#include "WorldMapLevel.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::GameStart()
{
	//GameEngineCore::CreateLevel<TestLevel>();
	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<WorldMapLevel>();
	

	GameEngineCore::ChangeLevel("TitleLevel");
}

void ContentsCore::GameEnd()
{

}