#include "PrecompileHeader.h"
#include "BaseTower.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "TowerButton.h"
#include "UpgradeTowerUI.h"
#include "BuildArea.h"

BaseTower::BaseTower()
{

}

BaseTower::~BaseTower()
{

}

void BaseTower::SellTower()
{
	if (ParentArea == nullptr)
	{
		MsgAssert("타워를 팔려고 했는데 ParentArea가 nullptr였습니다")
	}
	
	//돈주는 함수 자리

	ParentArea->On();
	ParentArea->ReleaseChildTower();
}

void BaseTower::Start()
{
	Construct = ConstructState::Constructing;
	TowerAreaRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	TowerAreaRenderer->SetTexture("terrain_0004.png");
	TowerAreaRenderer->GetTransform()->SetWorldScale({128,128,1});
	TowerAreaRenderer->GetTransform()->SetLocalPosition({ 0,0,1 });
	TowerRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	UpgradeButton = TowerButton::CreateButton(this);
	UpgradeButton->Off();

	UpgradeUI = UpgradeTowerUI::CreateUpgradeTowerUI(this);
	UpgradeUI->GetTransform()->SetLocalPosition(UpgradeUILocPos);

	BuildBarBg = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::BuildBarBg);
	BuildBarBg->SetTexture("buildbar_bg.png");
	BuildBarBg->GetTransform()->SetWorldScale(BuildBarBgScale);
	BuildBarBg->GetTransform()->SetLocalPosition({ 0,50,-1 });

	BuildBar = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::BuildBar);
	BuildBar->SetTexture("buildbar.png");
	BuildBar->GetTransform()->SetWorldScale({ 0,8,1 });
	BuildBar->GetTransform()->SetLocalPosition({ 0,50,-2 });
 }



