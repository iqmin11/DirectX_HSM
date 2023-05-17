#include "PrecompileHeader.h"
#include "BuildArea.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Ranged_Tower.h"

BuildArea::BuildArea()
{

}

BuildArea::~BuildArea()
{

}

std::shared_ptr<BuildArea> BuildArea::CreateBuildArea(GameEngineLevel* _Level, const float4& _ActorPos)
{
	std::shared_ptr<BuildArea> Result = nullptr;
	Result = _Level->CreateActor<BuildArea>();
	Result->ActorPos = _ActorPos;
	Result->GetTransform()->SetWorldPosition(Result->ActorPos);
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

void BuildArea::Start()
{
	BuildAreaRenderer = CreateComponent<GameEngineSpriteRenderer>();
	BuildAreaRenderer->SetTexture("build_terrain_0004.png");
	BuildAreaRenderer->GetTransform()->SetWorldScale(RenderScale);
	BuildAreaCol = CreateComponent<GameEngineCollision>(ColOrder::Tower);
	BuildAreaCol->GetTransform()->SetWorldScale(ColScale);
}

void BuildArea::Update(float _DeltaTime)
{
	if (ChildTower != nullptr && ChildTower->IsUpdate())
	{
		Off();
	}
	else
	{
		On();
	}

	if (IsAreaClick())
	{
		ChildTower = Ranged_Tower::CreateTower(GetLevel(), ActorPos);
	}
}

bool BuildArea::IsAreaClick()
{
	if (nullptr != BuildAreaCol->Collision(ColOrder::MousePointer, ColType::AABBBOX2D, ColType::AABBBOX2D) && GameEngineInput::IsUp("LeftClick"))
	{
		return true;
	}
	return false;
}