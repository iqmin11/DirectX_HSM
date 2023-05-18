#include "PrecompileHeader.h"
#include "BaseShooter.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include<GameEngineCore/GameEngineSpriteRenderer.h>
#include "BaseBullet.h"
#include "PlayStageLevel.h"

BaseShooter::BaseShooter()
{

}

BaseShooter::~BaseShooter()
{

}

void BaseShooter::Start()
{
	BaseShooterRenderer = CreateComponent<GameEngineSpriteRenderer>();
}

void BaseShooter::Update(float _DeltaTime)
{
	if (GetTransform()->GetWorldPosition().y < TargetPos->y)
	{
		Dir = "Up";
	}
	else
	{
		Dir = "Down";
	}
}
