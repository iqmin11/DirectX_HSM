#include "PrecompileHeader.h"
#include "PlayStageLevel.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "MousePointer.h"
#include "StageBg.h"
#include "MonsterWave.h"
#include "PlayStageUI.h"
#include "BuildArea.h"
#include "NextWaveStartButton.h"
#include "WaveButtons.h"
#include "BaseMonster.h"


std::vector<StageData> PlayStageLevel::AllStageData = std::vector<StageData>();


PlayStageLevel::PlayStageLevel()
{
}

PlayStageLevel::~PlayStageLevel()
{

}

void PlayStageLevel::InitStage(int _Stage)
{
	ClearStage();
	CurStage = _Stage;
	NextWave = 0;
	Life = 20;
	SetStageBg(CurStage);
	SetStagePaths(CurStage);
	SetStageBuildArea(CurStage);
	SetStageWaveButtons(CurStage);
	SetStageGold(CurStage);
}

void PlayStageLevel::ClearStage()
{
	CurStage = -1;
	NextWave = -1;
	Life = -1;
	ClearStageBg();
	ClearStagePaths();
	ClearStageBuildArea();
	ClearStageWaveButtons();
	ClearStageGold();
}

void PlayStageLevel::Start()
{
	KeySet(); 
	LoadPlayLevelTexture("Enemies");
	LoadPlayLevelTexture("StageBg");
	LoadPlayLevelTexture("TowerBase");
	LoadPlayLevelTexture("RangedTower");
	LoadPlayLevelTexture("ArtilleryBomb");
	LoadPlayLevelTexture("MeleeTower");
	LoadPlayLevelAnimation();
	
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->SetSortType(RenderOrder::Mob, SortType::ZSort);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0,0,-1000 });
	
	AcStageBg = CreateActor<StageBg>();
	AcPlayStageUI = CreateActor<PlayStageUI>();
	AcMousePointer = CreateActor<MousePointer>();

	LoadAllStageData();
	
	InitStage(0); // ���߿� ����ü���� ��ŸƮ���� �� �Լ�
}

void PlayStageLevel::Update(float _DeltaTime)
{
	//if (IsVictory())
	//{
	//	Victory();
	//}
	//else if (IsDefeat())
	//{
	//	Defeat();
	//}

	if (GameEngineInput::IsDown("TestLevel"))
	{
		GameEngineCore::ChangeLevel("TestLevel");
	}

	{
		static int a = 0;
		if (GameEngineInput::IsUp("RightArrow"))
		{
			++a;
			if (a > 5)
			{
				a = 0;
			}
			InitStage(a);
		}

		if (GameEngineInput::IsUp("LeftArrow"))
		{
			--a;
			if (a < 0)
			{
				a = 5;
			}
			InitStage(a);
		}
	}
}

void PlayStageLevel::LoadAllStageData()
{
	LoadPathBinData();
	LoadWaveBinData();
	LoadAreaBinData();
	LoadRallyBinData();
	LoadWaveButtonPos();
	LoadStageStartGold();
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
	// ����ó�� �ʿ�(������ ���̺���� ����������� �� ���ɾ��� �¸���Ű���� �ؾߴ�)
	//�ӽ� ����ó��
	if (AllStageData[CurStage].Waves.size() <= NextWave)
	{
		NextWave = 0;
		MonsterWave::StartWave(DynamicThis<GameEngineLevel>(), AllStageData[CurStage].Waves[NextWave].MonsterSpawn);
		//MsgTextBox("������ ���̺���� �����߽��ϴ�.");
		return;
	}

	MonsterWave::StartWave(DynamicThis<GameEngineLevel>() , AllStageData[CurStage].Waves[NextWave].MonsterSpawn);
	if (AcWaveButtons.size() > NextWave)
	{
		AcWaveButtons[NextWave] = nullptr;
	}
	++NextWave;
}

void PlayStageLevel::SetStageBuildArea(int _Stage)
{
	AcBuildAreas.resize(AllStageData[_Stage].BuildAreaPos.size());
	for (size_t i = 0; i < AcBuildAreas.size(); i++)
	{
		AcBuildAreas[i] = BuildArea::CreateBuildArea(this, AllStageData[_Stage].BuildAreaPos[i], AllStageData[_Stage].AreaStartRallyPos[i]);
	}
}

void PlayStageLevel::SetStageWaveButtons(int _Stage)
{
	AcWaveButtons.resize(AllStageData[_Stage].Waves.size());
	for (size_t i = 0; i < AcWaveButtons.size(); i++)
	{
		AcWaveButtons[i] = WaveButtons::CreateWaveButtons(this, AllStageData[_Stage].WaveStartButtonPos[i], static_cast<int>(i));
		AcWaveButtons[i]->Off();
	}
	AcWaveButtons[0]->On();
}

void PlayStageLevel::SetStageGold(int _Stage)
{
	Gold = AllStageData[_Stage].StartGold;
}

void PlayStageLevel::ClearStageBg()
{
	AcStageBg->RenderStage();
}

void PlayStageLevel::ClearStagePaths()
{
	MonsterWave::SetCurStagePaths(nullptr);
}

void PlayStageLevel::LoadPlayLevelTexture(std::string_view _Folder)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("3.PLAY STAGE LEVEL");
	Dir.Move(_Folder);

	std::vector<GameEngineFile> File = Dir.GetAllFile({ ".png" });
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineTexture::Load(File[i].GetFullPath());
	}
}

void PlayStageLevel::LoadPlayLevelAnimation()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("3.PLAY STAGE LEVEL");
	Dir.Move("RangedTowerShooterAnimation");

	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("RangedLv1_Shooter_Attack_Down").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("RangedLv2_Shooter_Attack_Down").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("RangedLv3_Shooter_Attack_Down").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("RangedLv1_Shooter_Idle_Down").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("RangedLv2_Shooter_Idle_Down").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("RangedLv3_Shooter_Idle_Down").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("RangedLv1_Shooter_Attack_Up").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("RangedLv2_Shooter_Attack_Up").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("RangedLv3_Shooter_Attack_Up").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("RangedLv1_Shooter_Idle_Up").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("RangedLv2_Shooter_Idle_Up").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("RangedLv3_Shooter_Idle_Up").GetFullPath());

	Dir.MoveParentToDirectory("RangedTowerShooterAnimation");
	Dir.Move("MagicTower");
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MagicTower_Level1_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MagicTower_Level1_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MagicTower_Level2_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MagicTower_Level2_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MagicTower_Level3_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MagicTower_Level3_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MagicBolt_Shoot").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MagicBolt_Death").GetFullPath());

	Dir.MoveParentToDirectory("MagicTower");
	Dir.Move("MagicTowerShooterAnimation");

	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Magic_Shooter_Attack_Down").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Magic_Shooter_Attack_Up").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Magic_Shooter_Idle_Down").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Magic_Shooter_Idle_Up").GetFullPath());

	Dir.MoveParentToDirectory("MagicTowerShooterAnimation");
	Dir.Move("ArtilleryTower");

	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_Level1_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_Level1_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_Level2_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_Level2_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_Level3_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_Level3_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_FireSmoke").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_ExplosionSmoke").GetFullPath());

	Dir.MoveParentToDirectory("ArtilleryTower");
	Dir.Move("Reinforcement");

	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_0_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_0_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_0_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_0_Death").GetFullPath());

	Dir.MoveParentToDirectory("Reinforcement");
	Dir.Move("DesertThug");

	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("DesertThug_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("DesertThug_Death").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("DesertThug_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("DesertThug_Move_Back").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("DesertThug_Move_Front").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("DesertThug_Move_Profile").GetFullPath());

	Dir.MoveParentToDirectory("DesertThug");
	Dir.Move("MeleeTowerFighterAnimation");

	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MeleeLv1_Fighter_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MeleeLv1_Fighter_Death" ).GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MeleeLv1_Fighter_Idle"  ).GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MeleeLv1_Fighter_Move"  ).GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MeleeLv2_Fighter_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MeleeLv2_Fighter_Death" ).GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MeleeLv2_Fighter_Idle"  ).GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MeleeLv2_Fighter_Move"  ).GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MeleeLv3_Fighter_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MeleeLv3_Fighter_Death" ).GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MeleeLv3_Fighter_Idle"  ).GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MeleeLv3_Fighter_Move"  ).GetFullPath());

	Dir.MoveParentToDirectory("MeleeTowerFighterAnimation");
	Dir.Move("DuneRaider");

	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("DuneRaider_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("DuneRaider_Death").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("DuneRaider_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("DuneRaider_Move_Back").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("DuneRaider_Move_Front").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("DuneRaider_Move_Profile").GetFullPath());

}

void PlayStageLevel::Defeat()
{
	MsgTextBox("�й��߽��ϴ�.");
}

void PlayStageLevel::Victory()
{
	MsgTextBox("�¸��߽��ϴ�.");
}

bool PlayStageLevel::IsDefeat()
{
	return Life == 0;
}

bool PlayStageLevel::IsVictory()
{
	return IsLastWave() && MonsterWave::IsLastMonsterSummon && BaseMonster::IsAllMonsterDead();
}

bool PlayStageLevel::IsLastWave()
{
	size_t LastWave = AllStageData[CurStage].Waves.size() - 1;
	return LastWave + 1 == NextWave;
}

void PlayStageLevel::LoadAreaBinData()
{
	GameEngineSerializer LoadSerializer = GameEngineSerializer();

	GameEngineFile File("..//ContentsData//BuildAreaData.txt");
	LoadSerializer.BufferResize(8000);
	File.LoadBin(LoadSerializer);

	int StgSize = 0;
	LoadSerializer.Read(StgSize);

	AllStageData.resize(StgSize);
	for (int i = 0; i < AllStageData.size(); i++)
	{
		LoadOneStageAreas(LoadSerializer, i);
	}
}

void PlayStageLevel::LoadOneStageAreas(GameEngineSerializer& _Serializer, int _StageLevel)
{
	int AreaSize = 0;
	_Serializer.Read(AreaSize);
	AllStageData[_StageLevel].BuildAreaPos.resize(AreaSize);
	for (int i = 0; i < AllStageData[_StageLevel].BuildAreaPos.size(); i++)
	{
		_Serializer.Read(&AllStageData[_StageLevel].BuildAreaPos[i], sizeof(float4));
	}
}

void PlayStageLevel::LoadRallyBinData()
{
	GameEngineSerializer LoadSerializer = GameEngineSerializer();

	GameEngineFile File("..//ContentsData//RallyData.txt");
	LoadSerializer.BufferResize(8000);
	File.LoadBin(LoadSerializer);

	int StgSize = 0;
	LoadSerializer.Read(StgSize);

	AllStageData.resize(StgSize);
	for (int i = 0; i < AllStageData.size(); i++)
	{
		LoadOneStageRally(LoadSerializer, i);
	}
}

void PlayStageLevel::LoadOneStageRally(GameEngineSerializer& _Serializer, int _StageLevel)
{
	int RallySize = 0;
	_Serializer.Read(RallySize);
	AllStageData[_StageLevel].AreaStartRallyPos.resize(RallySize);
	for (int i = 0; i < AllStageData[_StageLevel].AreaStartRallyPos.size(); i++)
	{
		_Serializer.Read(&AllStageData[_StageLevel].AreaStartRallyPos[i], sizeof(float4));
	}
}

void PlayStageLevel::LoadWaveButtonPos()
{
	for (int i = 0; i < AllStageData.size(); i++)
	{
		AllStageData[i].SetButtonPos(i);
	}
}

void PlayStageLevel::LoadStageStartGold()
{
	AllStageData[0].StartGold = 300;
	AllStageData[1].StartGold = 520;
	AllStageData[2].StartGold = 520;
	AllStageData[3].StartGold = 600;
	AllStageData[4].StartGold = 800;
	AllStageData[5].StartGold = 1000;
}

void PlayStageLevel::ClearStageBuildArea()
{
	for (size_t i = 0; i < AcBuildAreas.size(); i++)
	{
		AcBuildAreas[i]->ReleaseChildTower();
		AcBuildAreas[i]->Death();
	}
	AcBuildAreas.clear();
}

void PlayStageLevel::ClearStageWaveButtons()
{
	for (size_t i = 0; i < AcWaveButtons.size(); i++)
	{
		if (AcWaveButtons [i] != nullptr)
		{
			AcWaveButtons[i]->Death();
		}
	}
	AcWaveButtons.clear();
}

void PlayStageLevel::ClearStageGold()
{
	Gold = -1;
}
