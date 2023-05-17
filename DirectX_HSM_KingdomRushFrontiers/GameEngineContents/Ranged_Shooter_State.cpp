#include "PrecompileHeader.h"
#include "Ranged_Shooter.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "BaseShooter.h"
#include "Ranged_Bullet.h"
#include "BaseShootingTower.h"


//��ģ���� ������Ʈ ������ ������ Ÿ���� �������ִµ���.. friend�� �ɾ���ϳ� ���

void Ranged_Shooter::ChangeState(ShooterState _StateValue)
{
	ShooterState CurState = _StateValue;
	ShooterState PrevState = StateValue;

	StateValue = CurState;

	switch (StateValue)
	{
	case ShooterState::Idle:
		IdleStart();
		break;
	case ShooterState::Attack:
		AttackStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case ShooterState::Idle:
		IdleEnd();
		break;
	case ShooterState::Attack:
		AttackEnd();
		break;
	default:
		break;
	}
}
void Ranged_Shooter::UpdateState(float _DeltaTime)
{
}

void Ranged_Shooter::IdleStart()
{
	BaseShooterRenderer->ChangeAnimation("1_Idle_Down", false);
}
void Ranged_Shooter::IdleUpdate(float _DeltaTime)
{
	if (true) // ���Ͱ� �����ؾ��Ҷ�!
	{
		ChangeState(ShooterState::Attack);
		return;
	}
}
void Ranged_Shooter::IdleEnd()
{
}

void Ranged_Shooter::AttackStart()
{
	BaseShooterRenderer->ChangeAnimation("1_Attack_Down", false);
}
void Ranged_Shooter::AttackUpdate(float _DeltaTime)
{
	if (true/*!IsThereTarget()*/)
	{
		ChangeState(ShooterState::Idle);
		return;
	}
}
void Ranged_Shooter::AttackEnd()
{
}