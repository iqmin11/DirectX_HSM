#include "PrecompileHeader.h"
#include "StageSelectMenu.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

StageSelectMenu::StageSelectMenu()
{

}

StageSelectMenu::~StageSelectMenu()
{

}

void StageSelectMenu::Start()
{
	GetTransform()->SetWorldPosition(ActorPos);
	
	StageSelectMenuBg = CreateComponent<GameEngineSpriteRenderer>();
	StageSelectMenuBg->SetPipeLine("2DTexture");
	StageSelectMenuBg->SetTexture("LevelSelect_Bg.png");
	StageSelectMenuBg->GetTransform()->SetWorldScale(StageSelectMenuBgScale * ScaleRatio);

	StageThumbnail = CreateComponent<GameEngineSpriteRenderer>();
	StageThumbnail->SetPipeLine("2DTexture");
	StageThumbnail->SetTexture("thumb_stage1.png");
	StageThumbnail->GetTransform()->SetWorldScale(StageThumbnailScale * ScaleRatio);
	StageThumbnail->GetTransform()->SetWorldPosition(StageThumbnailPos);

	StageSelectLoupe = CreateComponent<GameEngineSpriteRenderer>();
	StageSelectLoupe->SetPipeLine("2DTexture");
	StageSelectLoupe->SetTexture("LevelSelect_loupe.png");
	StageSelectLoupe->GetTransform()->SetWorldScale(StageSelectLoupeScale * ScaleRatio);
	StageSelectLoupe->GetTransform()->SetWorldPosition(StageSelectLoupePos);

	StageStartButton = CreateComponent<GameEngineSpriteRenderer>();
	StageStartButton->SetPipeLine("2DTexture");
	StageStartButton->SetTexture("levelSelect_startMode_0001.png");
	StageStartButton->GetTransform()->SetWorldScale(StageStartButtonScale * ScaleRatio);
	StageStartButton->GetTransform()->SetWorldPosition(StageStartButtonPos);

	CampainModeButton = CreateComponent<GameEngineSpriteRenderer>();
	CampainModeButton->SetPipeLine("2DTexture");
	CampainModeButton->SetTexture("levelSelect_butModes_0001.png");
	CampainModeButton->GetTransform()->SetWorldScale(ModeButtonScale * ScaleRatio);
	CampainModeButton->GetTransform()->SetWorldPosition(CampainModeButtonPos);

	UnlockButton1 = CreateComponent<GameEngineSpriteRenderer>();
	UnlockButton1->SetPipeLine("2DTexture");
	UnlockButton1->SetTexture("levelSelect_butModes_0004.png");
	UnlockButton1->GetTransform()->SetWorldScale(ModeButtonScale * ScaleRatio);
	UnlockButton1->GetTransform()->SetWorldPosition(UnlockButton1Pos);

	UnlockButton2 = CreateComponent<GameEngineSpriteRenderer>();
	UnlockButton2->SetPipeLine("2DTexture");
	UnlockButton2->SetTexture("levelSelect_butModes_0004.png");
	UnlockButton2->GetTransform()->SetWorldScale(ModeButtonScale * ScaleRatio);
	UnlockButton2->GetTransform()->SetWorldPosition(UnlockButton2Pos);

	BackToWorldMapButton = CreateComponent<GameEngineSpriteRenderer>();
	BackToWorldMapButton->SetPipeLine("2DTexture");
	BackToWorldMapButton->SetTexture("LevelSelect_Back_0001.png");
	BackToWorldMapButton->GetTransform()->SetWorldScale(BackToWorldMapButtonScale * ScaleRatio);
	BackToWorldMapButton->GetTransform()->SetWorldPosition(BackToWorldMapButtonPos);

	StageStarBadge1 = CreateComponent<GameEngineSpriteRenderer>();
	StageStarBadge1->SetPipeLine("2DTexture");
	StageStarBadge1->SetTexture("levelSelect_badges_0002.png");
	StageStarBadge1->GetTransform()->SetWorldScale(StageStarBadgeScale * ScaleRatio);
	StageStarBadge1->GetTransform()->SetWorldPosition(StageStarBadge1Pos);
	StageStarBadge1->GetTransform()->SetWorldRotation(StageStarBadge1Rot);

	StageStarBadge2 = CreateComponent<GameEngineSpriteRenderer>();
	StageStarBadge2->SetPipeLine("2DTexture");
	StageStarBadge2->SetTexture("levelSelect_badges_0002.png");
	StageStarBadge2->GetTransform()->SetWorldScale(StageStarBadgeScale * ScaleRatio);
	StageStarBadge2->GetTransform()->SetWorldPosition(StageStarBadge2Pos);
	StageStarBadge2->GetTransform()->SetWorldRotation(StageStarBadge2Rot);

	StageStarBadge3 = CreateComponent<GameEngineSpriteRenderer>();
	StageStarBadge3->SetPipeLine("2DTexture");
	StageStarBadge3->SetTexture("levelSelect_badges_0002.png");
	StageStarBadge3->GetTransform()->SetWorldScale(StageStarBadgeScale * ScaleRatio);
	StageStarBadge3->GetTransform()->SetWorldPosition(StageStarBadge3Pos);
	StageStarBadge3->GetTransform()->SetWorldRotation(StageStarBadge3Rot);

}

void StageSelectMenu::Update(float _DeltaTime)
{
}
