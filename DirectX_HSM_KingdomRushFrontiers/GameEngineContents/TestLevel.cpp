#include "PrecompileHeader.h"
#include "TestLevel.h"
#include "TestActor.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsUIRenderer.h"

#include "ContentsButton.h"
#include "PopText.h"
#include "RainOfFire.h"
#include "FireBall.h"
#include "PriceTag.h"
#include "VictoryBadge.h"

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

	std::shared_ptr<VictoryBadge> TestVictoryBadge = CreateActor<VictoryBadge>();
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
