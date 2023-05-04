#include "PrecompileHeader.h"
#include "DesertThug.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

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
}

void DesertThug::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}
