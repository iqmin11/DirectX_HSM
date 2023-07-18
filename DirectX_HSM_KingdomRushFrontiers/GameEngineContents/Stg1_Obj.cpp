#include "PrecompileHeader.h"
#include "Stg1_Obj.h"

#include <GameEngineCore\GameEngineSpriteRenderer.h>
#include "CityTower.h"

Stg1_Obj::Stg1_Obj()
{

}

Stg1_Obj::~Stg1_Obj()
{

}

void Stg1_Obj::Start()
{
	AcCityTower0 = CityTower::CreateTower(this, {184, -55, -55});
	AcCityTower1 = CityTower::CreateTower(this, {-101, 300, 300});
}

