#include "PrecompileHeader.h"
#include "TestLevel.h"
#include "TestActor.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

#include "ContentsButton.h"
#include "PopText.h"

TestLevel::TestLevel()
{

}

TestLevel::~TestLevel()
{

}

void TestLevel::Start()
{

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentsResources");
		NewDir.Move("ContentsResources");
		NewDir.Move("Texture");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}

		File = NewDir.GetAllFile({ ".bmp", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	std::shared_ptr<TestActor> AcTest = CreateActorToName<TestActor>("TestActor");

	GameEngineInput::CreateKey("TitleLevel", '1');
	GameEngineInput::CreateKey("WorldMapLevel", '2');
	GameEngineInput::CreateKey("PlayStageLevel", '3');
	GameEngineInput::CreateKey("StageEditLevel", '4');

	//TestButton = ContentsButton::CreateButton(this, "Release.bmp", "Hover.bmp", "Press.bmp");
	//TestButton->GetTransform()->SetWorldScale({ 100, 100 });

	//TestPopText = CreateActor<PopText>();
	//std::shared_ptr<GameEngineActor> Test = CreateActor<GameEngineActor>();
	//Test->GetTransform()->SetWorldPosition({300, 300});
	//std::shared_ptr<GameEngineUIRenderer> TestRender = Test->CreateComponent<GameEngineUIRenderer>();
	//TestRender->GetTransform()->SetWorldScale({200, 200, 1});
	//TestRender->SetTexture("range_circle.png");


	std::shared_ptr<GameEngineActor> Test0 = CreateActor<GameEngineActor>();
	Test0->GetTransform()->SetWorldPosition({ 300, 300 });
	std::shared_ptr<GameEngineSpriteRenderer> Test0Render = Test0->CreateComponent<GameEngineSpriteRenderer>();
	Test0Render->GetTransform()->SetWorldScale({ 200, 200, 1 });
	Test0Render->SetTexture("range_circle.png");
//
//	//TestPopText = CreateActor<PopText>();
//	std::shared_ptr<GameEngineActor> Test1 = CreateActor<GameEngineActor>();
//	Test1->GetTransform()->SetWorldPosition({ 300, 300 });
//	std::shared_ptr<GameEngineUIRenderer> Test1Render = Test1->CreateComponent<GameEngineUIRenderer>();
//	Test1Render->GetTransform()->SetWorldScale({ 200, 200, 1 });
//	Test1Render->SetTexture("Release.bmp");
//
//	Test0Render->SetOrder(4);
//	Test1Render->SetOrder(3);
}

void TestLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("TitleLevel"))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (GameEngineInput::IsDown("WorldMapLevel"))
	{
		GameEngineCore::ChangeLevel("WorldMapLevel");
	}

	if (GameEngineInput::IsDown("PlayStageLevel"))
	{
		GameEngineCore::ChangeLevel("PlayStageLevel");
	}

	if (GameEngineInput::IsDown("StageEditLevel"))
	{
		GameEngineCore::ChangeLevel("StageEditLevel");
	}
}
