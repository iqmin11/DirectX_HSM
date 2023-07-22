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
	BaseShooterRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
}

void BaseShooter::Update(float _DeltaTime)
{
	ShooterFSM.Update(_DeltaTime);
}

void BaseShooter::PlayShooterSound(const std::string_view& _Name)
{
	ShooterSound = GameEngineSound::Play(_Name);
	ShooterSound.SetVolume(0.2f);
}

void BaseShooter::CheckDir()
{
	float4 WorldPos = GetTransform()->GetWorldPosition();
	if (WorldPos.y < TargetPos->y)
	{
		Dir_y = "Up";
	}
	else
	{
		Dir_y = "Down";
	}

	if (WorldPos.x < TargetPos->x)
	{
		Dir_x = "Right";
	}
	else
	{
		Dir_x = "Left";
	}
}

void BaseShooter::ChangeBaseShooterAnimation(const std::string_view& _AnimationName)
{
	BaseShooterRenderer->ChangeAnimation(_AnimationName);
}
