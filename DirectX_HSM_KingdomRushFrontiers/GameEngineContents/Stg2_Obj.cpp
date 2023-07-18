#include "PrecompileHeader.h"
#include "Stg2_Obj.h"

#include <GameEngineCore\GameEngineSpriteRenderer.h>

Stg2_Obj::Stg2_Obj()
{

}

Stg2_Obj::~Stg2_Obj()
{

}

void Stg2_Obj::Start()
{
	Obj0 = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	Obj0->GetTransform()->SetWorldScale({246, 424, 1});
	Obj0->GetTransform()->SetWorldPosition({-703, -239, static_cast<float>(RenderOrder::Obj)});
	Obj0->SetTexture("Stage_2_Obj0.png");

	Obj1 = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	Obj1->GetTransform()->SetWorldScale({ 223, 312, 1 });
	Obj1->GetTransform()->SetWorldPosition({ 715, -295, static_cast<float>(RenderOrder::Obj)});
	Obj1->SetTexture("Stage_2_Obj1.png");
}
