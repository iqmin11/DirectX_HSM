#include "PrecompileHeader.h"
#include "StageEditLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "StageEditor.h"

#include "StageBg.h"
//#include "StagePath.h"

StageEditLevel* StageEditLevel::MainStageEditLevel = nullptr;

StageEditLevel::StageEditLevel()
{
	MainStageEditLevel = this;
}

StageEditLevel::~StageEditLevel()
{

}

void StageEditLevel::Start()
{
	SetKey();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->SetSortType(RenderOrder::Mob, SortType::ZSort);
	AcStageBg = CreateActor<StageBg>();
	
	//AcStagePath = CreateActor<StagePath>();
	
	//AcPathEdit = CreateActor<PathEdit>();
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
	GameEngineInput::CreateKey("Z", 'Z');
	GameEngineInput::CreateKey("X", 'X');
	GameEngineInput::CreateKey("C", 'C');
	GameEngineInput::CreateKey("W", 'W');
	GameEngineInput::CreateKey("A", 'A');
	GameEngineInput::CreateKey("S", 'S');
	GameEngineInput::CreateKey("D", 'D');
	GameEngineInput::CreateKey("V", 'V');
	GameEngineInput::CreateKey("M", 'M');
	GameEngineInput::CreateKey("Enter",VK_RETURN);
	GameEngineInput::CreateKey("LeftClick", VK_LBUTTON);
	GameEngineInput::CreateKey("RightClick", VK_RBUTTON);
	GameEngineInput::CreateKey("Space", VK_SPACE);
}


void StageEditLevel::LevelChangeStart() 
{
	if (nullptr == GameEngineGUI::FindGUIWindow("StageEditor"))
	{
		std::shared_ptr<GameEngineGUIWindow> NewWindow = GameEngineGUI::GUIWindowCreate<StageEditor>("StageEditor");
		Editor = std::dynamic_pointer_cast<StageEditor>(NewWindow);
	}

	ShowCursor(TRUE);
	Editor->On();
}

void StageEditLevel::LevelChangeEnd()
{
	ShowCursor(FALSE);
	Editor->Off();
}