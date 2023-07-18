#include "PrecompileHeader.h"
#include "Stg3_Obj.h"

#include <GameEngineCore\GameEngineSpriteRenderer.h>

Stg3_Obj::Stg3_Obj()
{

}

Stg3_Obj::~Stg3_Obj()
{

}

void Stg3_Obj::Start()
{
	Obj0 = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	Obj0->GetTransform()->SetWorldScale({ 151, 201, 1 });
	Obj0->GetTransform()->SetWorldPosition({ 750,-350, static_cast<float>(RenderOrder::Obj) });
	Obj0->SetTexture("Stage_3_Obj0.png");
}
