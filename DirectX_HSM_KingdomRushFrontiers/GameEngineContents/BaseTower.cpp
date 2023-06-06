#include "PrecompileHeader.h"
#include "BaseTower.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
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
	TowerAreaRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	TowerAreaRenderer->SetTexture("terrain_0004.png");
	TowerAreaRenderer->GetTransform()->SetWorldScale({128,128,1});
	TowerAreaRenderer->GetTransform()->SetLocalPosition({ 0,0,1 });
	TowerRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	UpgradeButton = TowerButton::CreateButton(this);
	UpgradeUI = UpgradeTowerUI::CreateUpgradeTowerUI(this);
	UpgradeUI->GetTransform()->SetLocalPosition(UpgradeUILocPos);
}



