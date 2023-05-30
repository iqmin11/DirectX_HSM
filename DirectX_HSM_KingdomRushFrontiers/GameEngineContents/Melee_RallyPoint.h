#pragma once
#include "RallyPoint.h"

class Melee_RallyPoint : public RallyPoint
{
public:
	// construtor destructor
	Melee_RallyPoint();
	~Melee_RallyPoint();

	// delete Function
	Melee_RallyPoint(const Melee_RallyPoint& _Other) = delete;
	Melee_RallyPoint(Melee_RallyPoint&& _Other) noexcept = delete;
	Melee_RallyPoint& operator=(const Melee_RallyPoint& _Other) = delete;
	Melee_RallyPoint& operator=(Melee_RallyPoint&& _Other) noexcept = delete;

protected:


private:

};

