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
	UpgradeBgMid->SetPipeLine("2DTexture");
	UpgradeBgMid->SetTexture("upgrades_bg2_tileMid.png");
	UpgradeBgMid->GetTransform()->SetWorldScale(UpgradeBgMidScale * ScaleRatio);

	UpgradeBgLeft = CreateComponent<GameEngineSpriteRenderer>();
	UpgradeBgLeft->SetPipeLine("2DTexture");
	UpgradeBgLeft->SetTexture("upgrades_bg2_tileLeftpng.png");
	UpgradeBgLeft->GetTransform()->SetWorldScale(UpgradeBgLeftScale * ScaleRatio);

	UpgradeBgRight = CreateComponent<GameEngineSpriteRenderer>();
	UpgradeBgRight->SetPipeLine("2DTexture");
	UpgradeBgRight->SetTexture("upgrades_bg2_tileRight.png");
	UpgradeBgRight->GetTransform()->SetWorldScale(UpgradeBgRightScale * ScaleRatio);

	SetUpgradeBgPos(UpgradeBgMidPos);
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
	UpgradeBgLeft->GetTransform()->SetWorldPosition(_Pos + float4::Left * ((UpgradeBgMidScale * ScaleRatio).hx() + (UpgradeBgLeftScale * ScaleRatio).hx()) + float4{ 0,21 });
	UpgradeBgRight->GetTransform()->SetWorldPosition(_Pos + float4::Right * ((UpgradeBgMidScale * ScaleRatio).hx() + (UpgradeBgLeftScale * ScaleRatio).hx()) + float4{ 0,21 });
}
