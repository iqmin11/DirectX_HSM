#include "PrecompileHeader.h"
#include "PlayStageLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "StageMap.h"
#include "PlayStageUI.h"
#include "BaseMonster.h"
#include "MonsterPath.h"

PlayStageLevel::PlayStageLevel()
{

}

PlayStageLevel::~PlayStageLevel()
{

}

void PlayStageLevel::Start()
{
	KeySet();

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("3.PLAY STAGE LEVEL");

	std::vector<GameEngineFile> File = Dir.GetAllFile({ ".png" });
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineTexture::Load(File[i].GetFullPath());
	}

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	AcStageMap = CreateActor<StageMap>();
	AcPlayStageUI = CreateActor<PlayStageUI>();
	AcMonsterPath = CreateActor<MonsterPath>();
	AcBaseMonster = CreateActor<BaseMonster>();
	AcBaseMonster->SetPathInfo(AcMonsterPath->GetMonsterPathRef(0));
}

void PlayStageLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("TestLevel"))
	{
		GameEngineCore::ChangeLevel("TestLevel");
	}
}

void PlayStageLevel::KeySet()
{
	GameEngineInput::CreateKey("LeftClick",VK_LBUTTON);
	GameEngineInput::CreateKey("RightClick",VK_RBUTTON);
	GameEngineInput::CreateKey("F1",VK_F1);
}
