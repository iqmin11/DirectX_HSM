#include "PrecompileHeader.h"
#include "Stg0_Obj.h"

#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore\GameEngineSpriteRenderer.h>

#include "CityTower.h"

Stg0_Obj::Stg0_Obj()
{

}

Stg0_Obj::~Stg0_Obj()
{

}

void Stg0_Obj::Start()
{
	HammerObj = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	HammerObj->GetTransform()->SetWorldScale({213,213,1});
	HammerObj->GetTransform()->SetWorldPosition({0,30,30});
	HammerObj->SetTexture("Stage_0_Hammer.png");

	WallObj = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	WallObj->GetTransform()->SetWorldScale({ 300,712,1 });
	WallObj->GetTransform()->SetWorldPosition({ -676,-94,static_cast<float>(RenderOrder::Obj)});
	WallObj->SetTexture("Stage_0_Wall.png");

	CastleFlag0 = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	CastleFlag0->GetTransform()->SetWorldScale({ 53,53,1 });
	CastleFlag0->GetTransform()->SetWorldPosition({-737,106,static_cast<float>(RenderOrder::Obj)});
	CastleFlag0->CreateAnimation({.AnimationName = "Flag", .SpriteName = "Stage0_Flag", .FrameInter = 0.1f, .Loop = true});
	CastleFlag0->ChangeAnimation("Flag");

	CastleFlag1 = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	CastleFlag1->GetTransform()->SetWorldScale({ 53,53,1 });
	CastleFlag1->GetTransform()->SetWorldPosition({ -718,235,static_cast<float>(RenderOrder::Ground) });
	CastleFlag1->CreateAnimation({ .AnimationName = "Flag", .SpriteName = "Stage0_Flag", .FrameInter = 0.1f, .Loop = true });
	CastleFlag1->ChangeAnimation("Flag");

	AcCityTower0 = CityTower::CreateTower(this, {339,-65,-65 });
	AcCityTower1 = CityTower::CreateTower(this, {-336, 110, 110});
}

void Stg0_Obj::Update(float _DeltaTime)
{
}
