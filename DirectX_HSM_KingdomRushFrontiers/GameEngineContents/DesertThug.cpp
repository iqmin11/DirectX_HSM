#include "PrecompileHeader.h"
#include "DesertThug.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

DesertThug::DesertThug()
{

}

DesertThug::~DesertThug()
{

}

void DesertThug::Start()
{
	BaseMonster::Start();
	MonsterRenderer->SetTexture(TextureName);
	MonsterRenderer->GetTransform()->SetWorldScale(RenderScale);
	MonsterCol->GetTransform()->SetWorldScale(ColScale);
	Data.SetData(MonsterEnum::DesertThug);
}

void DesertThug::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}

