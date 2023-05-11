#include "PrecompileHeader.h"
#include "PlayStageLevel.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineBase/GameEngineTimeEvent.h>


#include "StageBg.h"
#include "MonsterWave.h"
#include "PlayStageUI.h"
#include "BaseMonster.h"
#include "DesertThug.h"
#include "DuneRaider.h"

std::vector<StageData> PlayStageLevel::AllStageData = std::vector<StageData>();


PlayStageLevel::PlayStageLevel()
{

}

PlayStageLevel::~PlayStageLevel()
{

}

void PlayStageLevel::SetStage(int _Stage)
{
	CurStage = _Stage;
	NextWave = 0;
	SetStageBg(CurStage);
	SetStagePaths(CurStage);
}

void PlayStageLevel::ResetStage()
{
	CurStage = -1;
	NextWave = -1;
	ResetStageBg();
	ResetStagePaths();
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
	
	AcStageBg = CreateActor<StageBg>();
	//AcMonsterPath = CreateActor<MonsterPath>();
	//AcMonsterWave = CreateActor<MonsterWave>();
	AcPlayStageUI = CreateActor<PlayStageUI>();

	LoadAllStageData();
	
	//Spawner.AddEvent(1.f, bind(&PlayStageLevel::MonsterSpawn,this),true);

	//임시 코드
	SetStage(0); // 나중에 레벨체인지 스타트에서 들어갈 함수
	
}

void PlayStageLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("TestLevel"))
	{
		GameEngineCore::ChangeLevel("TestLevel");
	}

	if (GameEngineInput::IsUp("Space"))
	{
		StartNextWave();
	}
	
	//Spawner.Update(_DeltaTime);
	//static float Time = 0;
	//Time += _DeltaTime;
	//if (Time >= 1)
	//{
	//	//어떤 몬스터가 어떤 경로에 몇마리 들어가야 한다를 넣어야 함.... 스폰할때
	//	Time = 0;
	//	MonsterSpawn();
	//}
}

void PlayStageLevel::LoadAllStageData()
{
	LoadPathBinData();
	LoadWaveBinData();

}

void PlayStageLevel::LoadPathBinData()
{
	GameEngineSerializer LoadSerializer = GameEngineSerializer();

	GameEngineFile File("..//ContentsData//PathData.txt");
	LoadSerializer.BufferResize(8000);
	File.LoadBin(LoadSerializer);

	int StgSize = 0;
	LoadSerializer.Read(StgSize);

	AllStageData.resize(StgSize);
	for (int i = 0; i < AllStageData.size(); i++)
	{
		LoadOneStageLines(LoadSerializer, i);
	}
}

void PlayStageLevel::LoadOneStageLines(GameEngineSerializer& _Serializer, int _StageLevel)
{
	int LineSize = 0;
	_Serializer.Read(LineSize);
	AllStageData[_StageLevel].Lines.resize(LineSize);
	for (int i = 0; i < AllStageData[_StageLevel].Lines.size(); i++)
	{
		//_Serializer.Read(&Data[_StageLevel].Lines[i].Index, sizeof(int));
		LoadOneLine(_Serializer, _StageLevel, i);
	}
}

void PlayStageLevel::LoadOneLine(GameEngineSerializer& _Serializer, int _StageLevel, int _PathIndex)
{
	int PointSize = 0;
	_Serializer.Read(PointSize);
	AllStageData[_StageLevel].Lines[_PathIndex].Points.resize(PointSize);
	for (size_t i = 0; i < AllStageData[_StageLevel].Lines[_PathIndex].Points.size(); i++)
	{
		_Serializer.Read(&AllStageData[_StageLevel].Lines[_PathIndex].Points[i], sizeof(float4));
	}
}

void PlayStageLevel::LoadWaveBinData()
{
	GameEngineSerializer LoadSerializer = GameEngineSerializer();

	GameEngineFile File("..//ContentsData//WaveData.txt");
	LoadSerializer.BufferResize(8000);
	File.LoadBin(LoadSerializer);

	int StgSize = 0;
	LoadSerializer.Read(StgSize);

	AllStageData.resize(StgSize);
	for (int i = 0; i < AllStageData.size(); i++)
	{
		LoadOneStageWave(LoadSerializer, i);
	}
}

void PlayStageLevel::LoadOneStageWave(GameEngineSerializer& _Serializer, int _StageLevel)
{
	int WaveSize = 0;
	_Serializer.Read(WaveSize);
	AllStageData[_StageLevel].Waves.resize(WaveSize);
	for (int i = 0; i < AllStageData[_StageLevel].Waves.size(); i++)
	{
		LoadOneWave(_Serializer, _StageLevel, i);
	}
}

void PlayStageLevel::LoadOneWave(GameEngineSerializer& _Serializer, int _StageLevel, int _WaveIndex)
{
	int MonsterSpawnDataSize = 0;
	_Serializer.Read(MonsterSpawnDataSize);
	std::vector<MonsterSpawnData>& LocalData = AllStageData[_StageLevel].Waves[_WaveIndex].MonsterSpawn;
	LocalData.resize(MonsterSpawnDataSize);
	for (size_t i = 0; i < LocalData.size(); i++)
	{
		_Serializer.Read(&LocalData[i].Monster, sizeof(MonsterEnum));
		_Serializer.Read(LocalData[i].LineIndex);
		_Serializer.Read(&LocalData[i].StartTime, sizeof(float));
	}
}

void PlayStageLevel::KeySet()
{
	//GameEngineInput::CreateKey("LeftClick",VK_LBUTTON);
	//GameEngineInput::CreateKey("RightClick",VK_RBUTTON);
	GameEngineInput::CreateKey("F1",VK_F1);
}

void PlayStageLevel::SetStageBg(int _Stage)
{
	AcStageBg->RenderStage(_Stage);
}

void PlayStageLevel::SetStagePaths(int _Stage)
{
	MonsterWave::SetCurStagePaths(&AllStageData[_Stage].Lines);
}

void PlayStageLevel::StartNextWave()
{
	// 예외처리 필요(마지막 웨이브까지 실행했을경우 뭐 어케어케 승리시키던가 해야댐)
	//임시 예외처리
	if (AllStageData[CurStage].Waves.size() <= NextWave)
	{
		MsgTextBox("마지막 웨이브까지 실행했습니다.");
		return;
	}

	MonsterWave::StartWave(std::dynamic_pointer_cast<GameEngineLevel>(std::enable_shared_from_this<GameEngineObject>::shared_from_this()), AllStageData[CurStage].Waves[NextWave].MonsterSpawn);
	++NextWave;
}

void PlayStageLevel::ResetStageBg()
{
	AcStageBg->RenderStage();
}

void PlayStageLevel::ResetStagePaths()
{
	MonsterWave::SetCurStagePaths(nullptr);

}

