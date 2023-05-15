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
	BaseMonster::MonsterRenderer->SetTexture(TextureName);
	BaseMonster::MonsterRenderer->GetTransform()->SetWorldScale(RenderScale);
	BaseMonster::MonsterCol->GetTransform()->SetWorldScale(ColScale);
}

void DesertThug::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}

