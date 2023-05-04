#include "PrecompileHeader.h"
#include "DuneRaider.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

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
}

void DuneRaider::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}
