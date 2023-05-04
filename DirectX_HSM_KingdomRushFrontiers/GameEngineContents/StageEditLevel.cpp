#include "PrecompileHeader.h"
#include "StageEditLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "StageEditor.h"

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


void StageEditLevel::LevelChangeStart() 
{
	

	if (nullptr == GameEngineGUI::FindGUIWindow("StageEditor"))
	{
		std::shared_ptr<GameEngineGUIWindow> NewWindow = GameEngineGUI::GUIWindowCreate<StageEditor>("StageEditor");
		Editor = std::dynamic_pointer_cast<StageEditor>(NewWindow);
	}

	Editor->On();

	// Stage Editor가 실행됐으면 좋겠다.
	int a = 0;
}

void StageEditLevel::LevelChangeEnd()
{
	Editor->Off();
}