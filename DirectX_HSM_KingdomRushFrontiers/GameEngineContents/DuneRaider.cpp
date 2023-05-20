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
	MonsterRenderer->SetTexture(TextureName);
	MonsterRenderer->GetTransform()->SetWorldScale(RenderScale);
	MonsterCol->GetTransform()->SetWorldScale(ColScale);
	Data.SetData(MonsterEnum::DuneRaider);
	CurHP = Data.Hp;
}

void DuneRaider::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}
