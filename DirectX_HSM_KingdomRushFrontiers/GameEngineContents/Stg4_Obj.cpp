#include "PrecompileHeader.h"
#include "Stg4_Obj.h"

#include <GameEngineCore\GameEngineSpriteRenderer.h>

Stg4_Obj::Stg4_Obj()
{

}

Stg4_Obj::~Stg4_Obj()
{

}

void Stg4_Obj::Start()
{
	Obj0 = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	Obj0->GetTransform()->SetWorldScale({ 274, 183, 1 });
	Obj0->GetTransform()->SetWorldPosition({ 233, 359, static_cast<float>(RenderOrder::Obj) });
	Obj0->SetTexture("Stage_4_Obj0.png");

	Obj1 = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	Obj1->GetTransform()->SetWorldScale({ 159, 106, 1 });
	Obj1->GetTransform()->SetWorldPosition({ 129, 278, static_cast<float>(RenderOrder::Ground) });
	Obj1->SetTexture("Stage_4_Obj1.png");
}
