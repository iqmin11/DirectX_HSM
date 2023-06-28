#include "PrecompileHeader.h"
#include "BaseTower.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "TowerButton.h"
#include "UpgradeTowerUI.h"
#include "BuildArea.h"
#include "UpgradeTowerButton.h"
#include "PlayManager.h"

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
	
	PlayManager::MainPlayer->Gold += Data.SellCost;

	ParentArea->On();
	ParentArea->ReleaseChildTower();
}

void BaseTower::Start()
{
	Construct = ConstructState::Constructing;
	TowerAreaRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	TowerAreaRenderer->SetTexture(TowerAreaRenderer_ReleaseName);
	TowerAreaRenderer->GetTransform()->SetWorldScale({128,128,1});
	TowerAreaRenderer->GetTransform()->SetLocalPosition({ 0,0,1 });
	TowerRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);

	BuildBarBg = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::BuildBarBg);
	BuildBarBg->SetTexture("buildbar_bg.png");
	BuildBarBg->GetTransform()->SetWorldScale(BuildBarBgScale);
	BuildBarBg->GetTransform()->SetLocalPosition({ 0,50 });

	BuildBar = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::BuildBar);
	BuildBar->SetTexture("buildbar.png");
	BuildBar->GetTransform()->SetWorldScale({ 0,8,1 });
	BuildBar->GetTransform()->SetLocalPosition({ 0,50 });

	TowerRangeRender = CreateComponent<GameEngineSpriteRenderer>(UIRenderOrder::TowerRange);
	NextLvRangeRender = CreateComponent<GameEngineSpriteRenderer>(UIRenderOrder::TowerRange);
	RangeCol = CreateComponent<GameEngineCollision>(ColOrder::TowerRange);
 }

void BaseTower::Update(float _DeltaTime)
{
	if (UpgradeUI->IsUpdate())
	{
		if (UpgradeUI->AcUpgradeButton->GetState() != ButtonState::Release)
		{
			NextLvRangeRender->On();
		}
		else
		{
			NextLvRangeRender->Off();
		}
	}
	else
	{
		NextLvRangeRender->Off();
	}

	if (UpgradeUI->IsUpdate())
	{
		if (TowerAreaRenderer->GetTexName() != TowerAreaRenderer_HoverName)
		{
			TowerAreaRenderer->SetTexture(TowerAreaRenderer_HoverName);
		}
	}
	else if (UpgradeButton->GetState() == ButtonState::Release)
	{
		if (TowerAreaRenderer->GetTexName() != TowerAreaRenderer_ReleaseName)
		{
			TowerAreaRenderer->SetTexture(TowerAreaRenderer_ReleaseName);
		}
	}
	else
	{
		if (TowerAreaRenderer->GetTexName() != TowerAreaRenderer_HoverName)
		{
			TowerAreaRenderer->SetTexture(TowerAreaRenderer_HoverName);
		}
	}

}



