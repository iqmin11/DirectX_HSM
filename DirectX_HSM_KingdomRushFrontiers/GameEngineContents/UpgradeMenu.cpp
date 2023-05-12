#include "PrecompileHeader.h"
#include "UpgradeMenu.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

UpgradeMenu::UpgradeMenu()
{

}

UpgradeMenu::~UpgradeMenu()
{

}

void UpgradeMenu::Start()
{
	//GetTransform()->SetWorldPosition(ActorPos);

	UpgradeBgMid = CreateComponent<GameEngineSpriteRenderer>();
	UpgradeBgMid->SetTexture("upgrades_bg2_tileMid.png");
	UpgradeBgMid->GetTransform()->SetWorldScale(UpgradeBgMidScale * ScaleRatio);

	UpgradeBgLeft = CreateComponent<GameEngineSpriteRenderer>();
	UpgradeBgLeft->SetTexture("upgrades_bg2_tileLeftpng.png");
	UpgradeBgLeft->GetTransform()->SetWorldScale(UpgradeBgLeftScale * ScaleRatio);

	UpgradeBgRight = CreateComponent<GameEngineSpriteRenderer>();
	UpgradeBgRight->SetTexture("upgrades_bg2_tileRight.png");
	UpgradeBgRight->GetTransform()->SetWorldScale(UpgradeBgRightScale * ScaleRatio);

	SetUpgradeBgPos(UpgradeBgMidPos);

	UpgradeInfo = CreateComponent<GameEngineSpriteRenderer>();
	UpgradeInfo->SetTexture("upgrades_info.png");
	UpgradeInfo->GetTransform()->SetWorldScale(UpgradeInfoScale * ScaleRatio);
	UpgradeInfo->GetTransform()->SetWorldPosition(UpgradeInfoPos);

	UpgradeButton = CreateComponent<GameEngineSpriteRenderer>();
	UpgradeButton->SetTexture("upgrades_buyBut_0001.png");
	UpgradeButton->GetTransform()->SetWorldScale(UpgradeButtonScale * ScaleRatio);
	UpgradeButton->GetTransform()->SetWorldPosition(UpgradeButtonPos);

	ResetButton = CreateComponent<GameEngineSpriteRenderer>();
	ResetButton->SetTexture("upgrades_buttons_0001.png");
	ResetButton->GetTransform()->SetWorldScale(ResetButtonScale * ScaleRatio);
	ResetButton->GetTransform()->SetWorldPosition(ResetButtonPos);

	DoneButton = CreateComponent<GameEngineSpriteRenderer>();
	DoneButton->SetTexture("upgrades_buttons_0003.png");
	DoneButton->GetTransform()->SetWorldScale(DoneButtonScale * ScaleRatio);
	DoneButton->GetTransform()->SetWorldPosition(DoneButtonPos);

	UpgradeGauges.reserve(6);
	for (size_t i = 0; i < UpgradeGauges.capacity(); i++)
	{
		UpgradeGauges.emplace_back();
		UpgradeGauges[i] = CreateComponent<GameEngineSpriteRenderer>();
		UpgradeGauges[i]->SetTexture("upgrade_bar_0002.png");
		UpgradeGauges[i]->GetTransform()->SetWorldScale(UpgradeGaugeScale * ScaleRatio);
		UpgradeGauges[i]->GetTransform()->SetWorldPosition(UpgradeGaugeStartPos + ((float4::Right * (BaseIconScale + BaseIconInterval))) * static_cast<float>(i));
	}

	UpgradeBaseIcons.reserve(6);
	for (size_t i = 0; i < UpgradeBaseIcons.capacity(); i++)
	{
		UpgradeBaseIcons.emplace_back();
		UpgradeBaseIcons[i] = CreateComponent<GameEngineSpriteRenderer>();
		UpgradeBaseIcons[i]->SetTexture("upgrades_bg_icons_000" + std::to_string(i + 1) + ".png");
		UpgradeBaseIcons[i]->GetTransform()->SetWorldScale(BaseIconScale * ScaleRatio);
		UpgradeBaseIcons[i]->GetTransform()->SetWorldPosition(BaseIconStartPos + ((float4::Right * (BaseIconScale + BaseIconInterval))) * static_cast<float>(i));
	}

	UpgradeRangedTowerIcon.reserve(5);
	for (size_t i = 0; i < UpgradeRangedTowerIcon.capacity(); i++)
	{
		UpgradeRangedTowerIcon.emplace_back();
		UpgradeRangedTowerIcon[i] = CreateComponent<GameEngineSpriteRenderer>();
		UpgradeRangedTowerIcon[i]->SetTexture("upgrades_icons_" + std::to_string(i + 1) + ".png");
		UpgradeRangedTowerIcon[i]->GetTransform()->SetWorldScale(UpgradeIconScale * ScaleRatio);
		UpgradeRangedTowerIcon[i]->GetTransform()->SetWorldPosition(UpgradeRangedTowerIconStartPos + ((float4::Up * (UpgradeIconScale + UpgradeIconInterval))) * static_cast<float>(i));
	}

	UpgradeMeleeTowerIcon.reserve(5);
	for (size_t i = 0; i < UpgradeMeleeTowerIcon.capacity(); i++)
	{
		UpgradeMeleeTowerIcon.emplace_back();
		UpgradeMeleeTowerIcon[i] = CreateComponent<GameEngineSpriteRenderer>();
		UpgradeMeleeTowerIcon[i]->SetTexture("upgrades_icons_" + std::to_string(i + 6) + ".png");
		UpgradeMeleeTowerIcon[i]->GetTransform()->SetWorldScale(UpgradeIconScale * ScaleRatio);
		UpgradeMeleeTowerIcon[i]->GetTransform()->SetWorldPosition(UpgradeMeleeTowerIconStartPos + ((float4::Up * (UpgradeIconScale + UpgradeIconInterval))) * static_cast<float>(i));
	}

	UpgradeMagicTowerIcon.reserve(5);
	for (size_t i = 0; i < UpgradeMagicTowerIcon.capacity(); i++)
	{
		UpgradeMagicTowerIcon.emplace_back();
		UpgradeMagicTowerIcon[i] = CreateComponent<GameEngineSpriteRenderer>();
		UpgradeMagicTowerIcon[i]->SetTexture("upgrades_icons_" + std::to_string(i + 11) + ".png");
		UpgradeMagicTowerIcon[i]->GetTransform()->SetWorldScale(UpgradeIconScale * ScaleRatio);
		UpgradeMagicTowerIcon[i]->GetTransform()->SetWorldPosition(UpgradeMagicTowerIconStartPos + ((float4::Up * (UpgradeIconScale + UpgradeIconInterval))) * static_cast<float>(i));
	}

	UpgradeArtilleryTowerIcon.reserve(5);
	for (size_t i = 0; i < UpgradeArtilleryTowerIcon.capacity(); i++)
	{
		UpgradeArtilleryTowerIcon.emplace_back();
		UpgradeArtilleryTowerIcon[i] = CreateComponent<GameEngineSpriteRenderer>();
		UpgradeArtilleryTowerIcon[i]->SetTexture("upgrades_icons_" + std::to_string(i + 16) + ".png");
		UpgradeArtilleryTowerIcon[i]->GetTransform()->SetWorldScale(UpgradeIconScale * ScaleRatio);
		UpgradeArtilleryTowerIcon[i]->GetTransform()->SetWorldPosition(UpgradeArtilleryTowerIconStartPos + ((float4::Up * (UpgradeIconScale + UpgradeIconInterval))) * static_cast<float>(i));
	}

	UpgradeFireballIcon.reserve(5);
	for (size_t i = 0; i < UpgradeFireballIcon.capacity(); i++)
	{
		UpgradeFireballIcon.emplace_back();
		UpgradeFireballIcon[i] = CreateComponent<GameEngineSpriteRenderer>();
		UpgradeFireballIcon[i]->SetTexture("upgrades_icons_" + std::to_string(i + 21) + ".png");
		UpgradeFireballIcon[i]->GetTransform()->SetWorldScale(UpgradeIconScale * ScaleRatio);
		UpgradeFireballIcon[i]->GetTransform()->SetWorldPosition(UpgradeFireballIconStartPos + ((float4::Up * (UpgradeIconScale + UpgradeIconInterval))) * static_cast<float>(i));
	}

	UpgradeReinforcementTowerIcon.reserve(5);
	for (size_t i = 0; i < UpgradeReinforcementTowerIcon.capacity(); i++)
	{
		UpgradeReinforcementTowerIcon.emplace_back();
		UpgradeReinforcementTowerIcon[i] = CreateComponent<GameEngineSpriteRenderer>();
		UpgradeReinforcementTowerIcon[i]->SetTexture("upgrades_icons_" + std::to_string(i + 26) + ".png");
		UpgradeReinforcementTowerIcon[i]->GetTransform()->SetWorldScale(UpgradeIconScale * ScaleRatio);
		UpgradeReinforcementTowerIcon[i]->GetTransform()->SetWorldPosition(UpgradeReinforcementTowerIconStartPos + ((float4::Up * (UpgradeIconScale + UpgradeIconInterval))) * static_cast<float>(i));
	}

	//GameEngineInput::CreateKey("ddd",'D');
}

void UpgradeMenu::Update(float _DeltaTime)
{
	//if (GameEngineInput::IsPress("ddd"))
	//{
	//	UpgradeBgMidPos += float4::Right * 100 * _DeltaTime;
	//	SetUpgradeBgPos(UpgradeBgMidPos);
	//}
}

void UpgradeMenu::SetUpgradeBgPos(float4& _Pos)
{
	UpgradeBgMid->GetTransform()->SetWorldPosition(_Pos);
	UpgradeBgLeft->GetTransform()->SetWorldPosition(_Pos + float4::Left * ((UpgradeBgMidScale * ScaleRatio).hx() + (UpgradeBgLeftScale * ScaleRatio).hx()) + float4{ 0,27 });
	UpgradeBgRight->GetTransform()->SetWorldPosition(_Pos + float4::Right * ((UpgradeBgMidScale * ScaleRatio).hx() + (UpgradeBgLeftScale * ScaleRatio).hx()) + float4{ 0,27 });
}
