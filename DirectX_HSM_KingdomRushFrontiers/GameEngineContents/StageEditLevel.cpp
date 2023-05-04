#include "PrecompileHeader.h"
#include "StageEditLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "PathEdit.h"

StageEditLevel::StageEditLevel()
{

}

StageEditLevel::~StageEditLevel()
{

}

void StageEditLevel::Start()
{
	SetKey();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	
	AcPathEdit = CreateActor<PathEdit>();
}

void StageEditLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("TestLevel"))
	{
		GameEngineCore::ChangeLevel("TestLevel");
	}
}

void StageEditLevel::SetKey()
{
	GameEngineInput::CreateKey("LeftArrow",VK_LEFT);
	GameEngineInput::CreateKey("RightArrow",VK_RIGHT);
	GameEngineInput::CreateKey("UpArrow",VK_UP);
	GameEngineInput::CreateKey("DownArrow",VK_DOWN);
	GameEngineInput::CreateKey("Z",'Z');
	GameEngineInput::CreateKey("Enter",VK_RETURN);
}
