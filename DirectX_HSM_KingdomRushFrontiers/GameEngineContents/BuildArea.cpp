#include "PrecompileHeader.h"
#include "BuildArea.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

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

void BuildArea::Start()
{
	BuildAreaRenderer = CreateComponent<GameEngineSpriteRenderer>();
	BuildAreaRenderer->SetTexture("build_terrain_0004.png");
	BuildAreaRenderer->GetTransform()->SetWorldScale(RenderScale);
}

void BuildArea::Update(float _DeltaTime)
{
}
