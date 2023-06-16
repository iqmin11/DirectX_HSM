#include "PrecompileHeader.h"
#include "CallReinforcement.h"

#include <GameEngineCore\GameEngineLevel.h>
#include "Reinforcement_RallyPoint.h"

CallReinforcement::CallReinforcement()
{

}

CallReinforcement::~CallReinforcement()
{

}

void CallReinforcement::CastingSpell(GameEngineLevel* _Level, const float4& _Pos)
{
	std::weak_ptr<Reinforcement_RallyPoint> LocSpell(Reinforcement_RallyPoint::CreateRallyPoint(_Level, _Pos, 2));
}
