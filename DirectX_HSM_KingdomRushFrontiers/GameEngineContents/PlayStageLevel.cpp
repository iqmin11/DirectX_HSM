#include "PrecompileHeader.h"
#include "PlayStageLevel.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineBase/GameEngineTimeEvent.h>


#include "StageMap.h"
#include "PlayStageUI.h"
#include "BaseMonster.h"
#include "MonsterPath.h"
#include "DesertThug.h"
#include "DuneRaider.h"


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
	
	Stage = StageState::Stage1;
	Spawner.AddEvent(1.f, bind(&PlayStageLevel::MonsterSpawn,this),true);
	
}

void PlayStageLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("TestLevel"))
	{
		GameEngineCore::ChangeLevel("TestLevel");
	}
	
	Spawner.Update(_DeltaTime);
	//static float Time = 0;
	//Time += _DeltaTime;
	//if (Time >= 1)
	//{
	//	//어떤 몬스터가 어떤 경로에 몇마리 들어가야 한다를 넣어야 함.... 스폰할때
	//	Time = 0;
	//	MonsterSpawn();
	//}
}

void PlayStageLevel::MonsterSpawn()
{
	CreateActor<DuneRaider>()->SetPathInfo(AcMonsterPath->GetMonsterPathRef(GameEngineRandom::MainRandom.RandomInt(0, 2)));
	CreateActor<DesertThug>()->SetPathInfo(AcMonsterPath->GetMonsterPathRef(GameEngineRandom::MainRandom.RandomInt(3, 5)));
}

void PlayStageLevel::KeySet()
{
	GameEngineInput::CreateKey("LeftClick",VK_LBUTTON);
	GameEngineInput::CreateKey("RightClick",VK_RBUTTON);
	GameEngineInput::CreateKey("F1",VK_F1);
}
