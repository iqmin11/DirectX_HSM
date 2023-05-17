#include "PrecompileHeader.h"
#include "BaseShootingTower.h"

#include <GameEngineCore/GameEngineCollision.h>
#include "BaseShooter.h"
#include "BaseMonster.h"

void BaseShootingTower::IdleStateInit(std::function<void()> _Start, std::function<void(float)> _Update, std::function<void()> _End)
{
	ShootingTowerFSM.CreateState({ .Name = "Idle", .Start = _Start, .Update = _Update, .End = _End });
}

void BaseShootingTower::AttackStateInit(std::function<void()> _Start, std::function<void(float)> _Update, std::function<void()> _End)
{
	ShootingTowerFSM.CreateState({ .Name = "Attack", .Start = _Start, .Update = _Update, .End = _End });
}