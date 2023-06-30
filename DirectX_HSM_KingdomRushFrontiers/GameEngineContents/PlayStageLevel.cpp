#include "PrecompileHeader.h"
#include "PlayStageLevel.h"
#include <GameEngineBase\GameEngineRandom.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineCore\GameEngineTexture.h>
#include <GameEngineCore\GameEngineCamera.h>
#include <GameEngineCore\GameEngineSprite.h>
#include <GameEngineCore\GameEngineSpriteRenderer.h>
#include <GameEngineCore\GameEngineFont.h>

#include "MousePointer.h"
#include "StageBg.h"
#include "MonsterWave.h"
#include "PlayStageUI.h"
#include "BuildArea.h"
#include "NextWaveStartButton.h"
#include "WaveButtons.h"
#include "BaseMonster.h"
#include "RainOfFire.h"
#include "CallReinforcement.h"
#include "Hero_RallyPoint.h"
#include "PlayManager.h"
#include "VictoryBadge.h"

std::vector<StageData> PlayStageLevel::AllStageData = std::vector<StageData>();
bool PlayStageLevel::IsPause = false;

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
	MaxWave = static_cast<int>(AllStageData[CurStage].Waves.size());
	SetStageBg(CurStage);
	SetStagePaths(CurStage);
	SetStageBuildArea(CurStage);
	SetStageWaveButtons(CurStage);
	SetStageGold(CurStage);
	SetHero(CurStage);
	MainPlayer->InitPlayManager();
}

void PlayStageLevel::ClearStage()
{
	CurStage = -1;
	NextWave = -1;
	MaxWave = -1;
	MainPlayer->Life = -1;
	ClearStageBg();
	ClearStagePaths();
	ClearStageBuildArea();
	ClearStageWaveButtons();
	ClearStageGold();
	ClearHero();
	ClearLiveWave();
	ClearLiveMonster();
}

void PlayStageLevel::Start()
{
	std::shared_ptr _101Camera = CreateNewCamera(101);
	_101Camera->SetProjectionType(CameraType::Orthogonal);

	KeySet(); 
	LoadPlayLevelTexture("Enemies");
	LoadPlayLevelTexture("StageBg");
	LoadPlayLevelTexture("TowerBase");
	LoadPlayLevelTexture("RangedTower");
	LoadPlayLevelTexture("ArtilleryBomb");
	LoadPlayLevelTexture("MeleeTower");
	LoadPlayLevelTexture("PopText");
	LoadPlayLevelAnimation();
	LoadFont();
	
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->SetSortType(RenderOrder::Mob, SortType::ZSort);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0,0,-1000 });

	GetCamera(100)->GetCamTarget()->DepthSettingOff();
	
	MainPlayer = CreateActor<PlayManager>();
	AcStageBg = CreateActor<StageBg>();
	AcPlayStageUI = CreateActor<PlayStageUI>();
	AcMousePointer = CreateActor<MousePointer>();

	LoadAllStageData();
	
	InitStage(0); // 나중에 레벨체인지 스타트에서 들어갈 함수
}

void PlayStageLevel::Update(float _DeltaTime)
{
	//승리, 패배, WorldmapLevel 만들고 본격적으로 활성화 시키기
	if (IsPause)
	{
		GameEngineTime::GlobalTime.SetUpdateOrderTimeScale(ActorOrder::Base, 0.0f);
	}
	else
	{
		GameEngineTime::GlobalTime.SetUpdateOrderTimeScale(ActorOrder::Base, 1.0f);
	}

	if (IsVictory() || GameEngineInput::IsDown("C"))
	{
		Victory();
	}
	else if (IsDefeat())
	{
		Defeat();
	}

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

	if (GameEngineInput::IsUp("V"))
	{
		IsDebugSwitch();
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
	LoadStageHeroStartPos();
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
	GameEngineInput::CreateKey("1",'1');
	GameEngineInput::CreateKey("2",'2');
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
		NextWave = 0;
		MonsterWave::StartWave(DynamicThis<GameEngineLevel>(), AllStageData[CurStage].Waves[NextWave].MonsterSpawn);
		//MsgTextBox("마지막 웨이브까지 실행했습니다.");
		return;
	}

	MonsterWave::StartWave(DynamicThis<GameEngineLevel>() , AllStageData[CurStage].Waves[NextWave].MonsterSpawn);
	if (AcWaveButtons.size() > NextWave)
	{
		AcWaveButtons[NextWave] = nullptr;
	}
	++NextWave;
}

void PlayStageLevel::SubLife(int _LivesTaken)
{
	MainPlayer->Life -= _LivesTaken;
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
	AcWaveButtons[0]->OnButtons();
}

void PlayStageLevel::SetStageGold(int _Stage)
{
	PlayManager::MainPlayer->Gold = AllStageData[_Stage].StartGold;
}

void PlayStageLevel::SetHero(int _Stage)
{
	AcHero = Hero_RallyPoint::CreateRallyPoint(this, AllStageData[_Stage].HeroStartPos);
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
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("MagicTower_Construct").GetFullPath());
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

	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_Construct").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_Level1_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_Level1_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_Level2_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_Level2_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_Level3_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_Level3_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_FireSmoke").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ArtilleryTower_ExplosionSmoke").GetFullPath());

	Dir.MoveParentToDirectory("ArtilleryTower");
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

	Dir.MoveParentToDirectory("DuneRaider");
	Dir.Move("EffectAnimation");

	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Small_Blood").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Small_Explosion").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Small_Poison").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("RallyPointEffectAnimation").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("HeroPositionAnimation").GetFullPath());

	Dir.MoveParentToDirectory("EffectAnimation");
	Dir.Move("PlayerSpell");
	Dir.Move("RainOfFire_Animation");

	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("FireBall").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("FireBallSmoke").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("FireBallExplosion").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("FireBallShadow").GetFullPath());
	
	Dir.MoveParentToDirectory("RainOfFire_Animation");
	Dir.Move("Reinforcement");

	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_0_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_0_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_0_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_0_Death").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_1_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_1_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_1_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_1_Death").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_2_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_2_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_2_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_2_Death").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_3_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_3_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_3_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_3_Death").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_4_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_4_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_4_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceA_4_Death").GetFullPath());

	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_0_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_0_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_0_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_0_Death").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_1_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_1_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_1_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_1_Death").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_2_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_2_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_2_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_2_Death").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_3_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_3_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_3_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_3_Death").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_4_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_4_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_4_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceB_4_Death").GetFullPath());

	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_0_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_0_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_0_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_0_Death").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_1_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_1_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_1_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_1_Death").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_2_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_2_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_2_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_2_Death").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_3_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_3_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_3_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_3_Death").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_4_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_4_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_4_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforceC_4_Death").GetFullPath());

	Dir.MoveParentToDirectory("PlayerSpell");
	Dir.Move("Hero");
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Hero_Alric_Attack_0").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Hero_Alric_Attack_1").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Hero_Alric_Death").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Hero_Alric_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Hero_Alric_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Hero_Alric_Revive").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Hero_Alric_Skill_Flurry").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Hero_Alric_Skill_Summon").GetFullPath());
	
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Sandman_Attack").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Sandman_Born").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Sandman_Death").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Sandman_Idle").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Sandman_MoveStart").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Sandman_Move").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Sandman_MoveEnd").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Sandman_MoveDeath").GetFullPath());

	Dir.MoveParentToDirectory("Hero");
	Dir.Move("GUIAnimation");

	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Mouse_CallReinforcement").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Mouse_Press").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Mouse_RainOfFire").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Mouse_Release").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Mouse_UnitSelect").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("RainOfFireButton_Revive").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("ReinforcementButton_Revive").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("PortrateFrame_Revive").GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName("StarAnimation").GetFullPath());
}

void PlayStageLevel::LoadFont()
{
	GameEngineFont::Load("TOONISH");
	GameEngineFont::Load("나눔손글씨 펜 OTF");
	GameEngineFont::Load("제주한라산");
}

void PlayStageLevel::Defeat()
{
	MsgTextBox("패배했습니다.");
}

void PlayStageLevel::Victory()
{
	if (AcVictoryBadge.expired())
	{
		AcVictoryBadge = std::weak_ptr(CreateActor<VictoryBadge>(ActorOrder::VictoryBadge));
		IsPause = true;
	}
}

bool PlayStageLevel::IsDefeat()
{
	return MainPlayer->Life == 0;
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

void PlayStageLevel::LoadStageHeroStartPos()
{
	for (int i = 0; i < AllStageData.size(); i++)
	{
		AllStageData[i].SetHeroStartPos(i);
	}
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
	MainPlayer->Gold = -1;
}

void PlayStageLevel::ClearHero()
{
	if (AcHero != nullptr)
	{
		AcHero->Death();
		AcHero = nullptr;
	}
}

void PlayStageLevel::ClearLiveWave()
{
	MonsterWave::ReleaseWave();
}

void PlayStageLevel::ClearLiveMonster()
{
	BaseMonster::LiveMonsterListForceRelease();
}
