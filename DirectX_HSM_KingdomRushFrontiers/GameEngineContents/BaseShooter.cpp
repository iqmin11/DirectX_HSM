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

	//Test ���߿� �����Ұ�
	TestTargetRender = CreateComponent<GameEngineSpriteRenderer>();
	TestTargetRender->GetTransform()->SetWorldScale({5,5});
}

void BaseShooter::Update(float _DeltaTime)
{
	//Ÿ���� ���ϴ� �Լ��� ���� �Ǿ����

	float Distance = (ParentPos - TargetPos).Size();
	if (Range >= Distance)
	{
		Time += _DeltaTime;
		if (Time >= AttackSpeed)
		{
			Time = 0;
			Attack();
		}
	}

	//Test ���߿� �����ϼ�
	if (GameEngineInput::IsPress("LeftArrow"))
	{
		TargetPos += float4::Left;
	}

	if (GameEngineInput::IsPress("RightArrow"))
	{
		TargetPos += float4::Right;
	}

	if (GameEngineInput::IsPress("DownArrow"))
	{
		TargetPos += float4::Down;
	}

	if (GameEngineInput::IsPress("UpArrow"))
	{
		TargetPos += float4::Up;
	}

	
}

void BaseShooter::Render(float _DeltaTime)
{
	//Test ���߿� ����
	TestTargetRender->GetTransform()->SetWorldPosition(TargetPos);
}

//void BaseShooter::Attack()
//{
//	BaseBullet::ShootingBullet(GetLevel(), this);
//}
