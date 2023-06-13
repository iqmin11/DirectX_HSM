#include "PrecompileHeader.h"
#include "BuildArea.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Ranged_Tower.h"
#include "Magic_Tower.h"
#include "Artillery_Tower.h"
#include "Melee_Tower.h"
#include "BuildAreaButton.h"
#include "BuildTowerUI.h"

BuildArea::BuildArea()
{

}

BuildArea::~BuildArea()
{

}

std::shared_ptr<BuildArea> BuildArea::CreateBuildArea(GameEngineLevel* _Level, const float4& _ActorPos, const float4& _RallyPos)
{
	std::shared_ptr<BuildArea> Result = nullptr;
	Result = _Level->CreateActor<BuildArea>();
	Result->ActorPos = _ActorPos;
	Result->RallyPos = _RallyPos;
	Result->GetTransform()->SetWorldPosition(Result->ActorPos);
	Result->AreaButton = BuildAreaButton::CreateButton(Result.get());
	Result->BuildUI = BuildTowerUI::CreateBuildTowerUI(Result.get());
	return Result;
}

void BuildArea::ReleaseChildTower()
{
	if (ChildTower != nullptr)
	{
		ChildTower->Death();
		ChildTower = nullptr;
	}
	return;
}

void BuildArea::CreateRangedTower()
{
	ChildTower = Ranged_Tower::CreateTower(GetLevel(), this);
}

void BuildArea::CreateMeleeTower()
{
	ChildTower = Melee_Tower::CreateTower(GetLevel(), this);
}

void BuildArea::CreateMagicTower()
{
	ChildTower = Magic_Tower::CreateTower(GetLevel(), this);
}

void BuildArea::CreateArtilleryTower()
{
	ChildTower = Artillery_Tower::CreateTower(GetLevel(), this);
}

void BuildArea::Start()
{
	BuildAreaRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	BuildAreaRenderer->SetTexture("build_terrain_0004.png");
	BuildAreaRenderer->GetTransform()->SetWorldScale(RenderScale);
	BuildAreaCol = CreateComponent<GameEngineCollision>(ColOrder::Tower);
	BuildAreaCol->GetTransform()->SetWorldScale(ColScale);

	//BuildUI->GetTransform()->SetLocalPosition(BuildUILocPos);
}

void BuildArea::Update(float _DeltaTime)
{
	if (ChildTower != nullptr && ChildTower->IsUpdate())
	{
		Off();
	}
}