#include "PrecompileHeader.h"
#include "WorldMap.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

WorldMap::WorldMap()
{

}

WorldMap::~WorldMap()
{

}

void WorldMap::Start()
{
	Bg = CreateComponent<GameEngineSpriteRenderer>();
	Bg->SetPipeLine("2DTexture");
	Bg->SetTexture("Bg.png");
	Bg->GetTransform()->SetWorldScale(BgScale);
	
	WorldMapBg = CreateComponent<GameEngineSpriteRenderer>();
	WorldMapBg->SetPipeLine("2DTexture");
	WorldMapBg->SetTexture("MapBackground.png");
	WorldMapBg->GetTransform()->SetWorldScale(WorldMapBgScale * ScaleRatio);
	
	Stage1Flag = CreateComponent<GameEngineSpriteRenderer>();
	Stage1Flag->SetPipeLine("2DTexture");
	Stage1Flag->SetTexture(FlagImageName);
	Stage1Flag->GetTransform()->SetWorldScale(FlagScale * ScaleRatio);
	Stage1Flag->GetTransform()->SetWorldPosition(Stage1FlagPos);

	Stage1to2Road = CreateComponent<GameEngineSpriteRenderer>();
	Stage1to2Road->SetPipeLine("2DTexture");
	Stage1to2Road->SetTexture("MapRoads_1to20002.png");
	Stage1to2Road->GetTransform()->SetWorldScale(Stage1to2RoadScale * ScaleRatio);
	Stage1to2Road->GetTransform()->SetWorldPosition(Stage1to2RoadPos);

	Stage2Flag = CreateComponent<GameEngineSpriteRenderer>();
	Stage2Flag->SetPipeLine("2DTexture");
	Stage2Flag->SetTexture(FlagImageName);
	Stage2Flag->GetTransform()->SetWorldScale(FlagScale * ScaleRatio);
	Stage2Flag->GetTransform()->SetWorldPosition(Stage2FlagPos);

	Stage2to3Road = CreateComponent<GameEngineSpriteRenderer>();
	Stage2to3Road->SetPipeLine("2DTexture");
	Stage2to3Road->SetTexture("MapRoads_2to30004.png");
	Stage2to3Road->GetTransform()->SetWorldScale(Stage2to3RoadScale * ScaleRatio);
	Stage2to3Road->GetTransform()->SetWorldPosition(Stage2to3RoadPos);

	Stage3Flag = CreateComponent<GameEngineSpriteRenderer>();
	Stage3Flag->SetPipeLine("2DTexture");
	Stage3Flag->SetTexture(FlagImageName);
	Stage3Flag->GetTransform()->SetWorldScale(FlagScale * ScaleRatio);
	Stage3Flag->GetTransform()->SetWorldPosition(Stage3FlagPos);

	Stage3to4Road = CreateComponent<GameEngineSpriteRenderer>();
	Stage3to4Road->SetPipeLine("2DTexture");
	Stage3to4Road->SetTexture("MapRoads_3to40003.png");
	Stage3to4Road->GetTransform()->SetWorldScale(Stage3to4RoadScale * ScaleRatio);
	Stage3to4Road->GetTransform()->SetWorldPosition(Stage3to4RoadPos);

	Stage4Flag = CreateComponent<GameEngineSpriteRenderer>();
	Stage4Flag->SetPipeLine("2DTexture");
	Stage4Flag->SetTexture(FlagImageName);
	Stage4Flag->GetTransform()->SetWorldScale(FlagScale * ScaleRatio);
	Stage4Flag->GetTransform()->SetWorldPosition(Stage4FlagPos);

	Stage4to5Road = CreateComponent<GameEngineSpriteRenderer>();
	Stage4to5Road->SetPipeLine("2DTexture");
	Stage4to5Road->SetTexture("MapRoads_4to50006.png");
	Stage4to5Road->GetTransform()->SetWorldScale(Stage4to5RoadScale * ScaleRatio);
	Stage4to5Road->GetTransform()->SetWorldPosition(Stage4to5RoadPos);

	Stage5Flag = CreateComponent<GameEngineSpriteRenderer>();
	Stage5Flag->SetPipeLine("2DTexture");
	Stage5Flag->SetTexture(FlagImageName);
	Stage5Flag->GetTransform()->SetWorldScale(FlagScale * ScaleRatio);
	Stage5Flag->GetTransform()->SetWorldPosition(Stage5FlagPos);

	Stage5to6Road = CreateComponent<GameEngineSpriteRenderer>();
	Stage5to6Road->SetPipeLine("2DTexture");
	Stage5to6Road->SetTexture("MapRoads_5to60019.png");
	Stage5to6Road->GetTransform()->SetWorldScale(Stage5to6RoadScale * ScaleRatio);
	Stage5to6Road->GetTransform()->SetWorldPosition(Stage5to6RoadPos);

	Stage6Flag = CreateComponent<GameEngineSpriteRenderer>();
	Stage6Flag->SetPipeLine("2DTexture");
	Stage6Flag->SetTexture(FlagImageName);
	Stage6Flag->GetTransform()->SetWorldScale(FlagScale * ScaleRatio);
	Stage6Flag->GetTransform()->SetWorldPosition(Stage6FlagPos);

	StarContainer = CreateComponent<GameEngineSpriteRenderer>();
	StarContainer->SetPipeLine("2DTexture");
	StarContainer->SetTexture("mapStarsContainer.png");
	StarContainer->GetTransform()->SetWorldScale(StarContainerScale);
	StarContainer->GetTransform()->SetWorldPosition(StarContainerPos);

	UpgradeButton = CreateComponent<GameEngineSpriteRenderer>();
	UpgradeButton->SetPipeLine("2DTexture");
	UpgradeButton->SetTexture("butUpgrades_0001.png");
	UpgradeButton->GetTransform()->SetWorldScale(UpgradeButtonScale);
	UpgradeButton->GetTransform()->SetWorldPosition(UpgradeButtonPos);

	HomeButton = CreateComponent<GameEngineSpriteRenderer>();
	HomeButton->SetPipeLine("2DTexture");
	HomeButton->SetTexture("options_overlay_buttons_0005.png");
	HomeButton->GetTransform()->SetWorldScale(HomeButtonScale);
	HomeButton->GetTransform()->SetWorldPosition(HomeButtonPos);
}

void WorldMap::Update(float _DeltaTime)
{
	
}
