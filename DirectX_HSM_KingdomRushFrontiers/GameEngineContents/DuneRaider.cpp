#include "PrecompileHeader.h"
#include "DuneRaider.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

DuneRaider::DuneRaider()
{

}

DuneRaider::~DuneRaider()
{

}

void DuneRaider::Start()
{
	BaseMonster::Start();
	BaseMonster::MonsterRenderer->SetTexture(TextureName);
	BaseMonster::MonsterRenderer->GetTransform()->SetWorldScale(RenderScale);
	BaseMonster::MonsterCol->GetTransform()->SetWorldScale(ColScale);
}

void DuneRaider::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}
