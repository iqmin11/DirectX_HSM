#include "PrecompileHeader.h"
#include "BaseTower.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "BaseShooter.h"

BaseTower::BaseTower()
{

}

BaseTower::~BaseTower()
{

}

void BaseTower::Start()
{
	GetTransform()->SetWorldPosition(ActorPos);
	TowerRenderer = CreateComponent<GameEngineSpriteRenderer>();

	TowerRangeRender = CreateComponent<GameEngineSpriteRenderer>();
	TowerRangeRender->SetTexture("range_circle.png");
}

//void BaseTower::Update(float _DeltaTime)
//{
//	Time += _DeltaTime;
//	if (Time >= 1.0f)
//	{
//		Time = 0.0f;
//		if (Attack == nullptr)
//		{
//			MsgAssert("Attack함수가 nullptr압니다. 함수를 설정해주세요");
//		}
//		Attack();
//	}
//}




