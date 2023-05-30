#pragma once
class Melee_Fighter
{
public:
	// construtor destructor
	Melee_Fighter();
	~Melee_Fighter();

	// delete Function
	Melee_Fighter(const Melee_Fighter& _Other) = delete;
	Melee_Fighter(Melee_Fighter&& _Other) noexcept = delete;
	Melee_Fighter& operator=(const Melee_Fighter& _Other) = delete;
	Melee_Fighter& operator=(Melee_Fighter&& _Other) noexcept = delete;

protected:


private:

};

