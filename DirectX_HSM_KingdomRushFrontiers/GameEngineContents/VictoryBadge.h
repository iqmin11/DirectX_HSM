#pragma once
#include <GameEngineCore\GameEngineActor.h>

class VictoryBadge : public GameEngineActor
{
public:
	// construtor destructor
	VictoryBadge();
	~VictoryBadge();

	// delete Function
	VictoryBadge(const VictoryBadge& _Other) = delete;
	VictoryBadge(VictoryBadge&& _Other) noexcept = delete;
	VictoryBadge& operator=(const VictoryBadge& _Other) = delete;
	VictoryBadge& operator=(VictoryBadge&& _Other) noexcept = delete;

protected:


private:

};

