#include "PrecompileHeader.h"
#include "StageEditLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "MapEdit.h"

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
	
	AcMapEdit = CreateActor<MapEdit>();
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
	GameEngineInput::CreateKey("Z",'Z');
	GameEngineInput::CreateKey("Enter",VK_RETURN);
}
