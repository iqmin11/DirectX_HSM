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
	LoadTexture();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
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
	GameEngineInput::CreateKey("Z",'Z');
	GameEngineInput::CreateKey("Enter",VK_RETURN);
	GameEngineInput::CreateKey("LeftClick", VK_LBUTTON);
	GameEngineInput::CreateKey("RightClick", VK_RBUTTON);
}

void StageEditLevel::LoadTexture()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("3.PLAY STAGE LEVEL");
	std::vector<GameEngineFile> File = Dir.GetAllFile({ ".png" });
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineTexture::Load(File[i].GetFullPath());
	}
}


void StageEditLevel::LevelChangeStart() 
{
	if (nullptr == GameEngineGUI::FindGUIWindow("StageEditor"))
	{
		std::shared_ptr<GameEngineGUIWindow> NewWindow = GameEngineGUI::GUIWindowCreate<StageEditor>("StageEditor");
		Editor = std::dynamic_pointer_cast<StageEditor>(NewWindow);
	}

	Editor->On();
}

void StageEditLevel::LevelChangeEnd()
{
	Editor->Off();
}