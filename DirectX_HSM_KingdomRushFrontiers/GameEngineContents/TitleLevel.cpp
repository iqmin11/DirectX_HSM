#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "TitleBackground.h"
#include "TitleLogo.h"


TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::Start()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("1.TITLE LEVEL");

	std::vector<GameEngineFile> File = Dir.GetAllFile({ ".png" });
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineTexture::Load(File[i].GetFullPath());
	}

	AcTitleBackground = CreateActor<TitleBackground>();
	AcTitleLogo = CreateActor<TitleLogo>();

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	//GetMainCamera()->GetTransform()->SetLocalPosition(CameraPos);
	GameEngineInput::CreateKey("TestLevel",VK_ESCAPE);
}

void TitleLevel::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);

	if (GameEngineInput::IsDown("TestLevel"))
	{
		GameEngineCore::ChangeLevel("TestLevel");
	}
}
