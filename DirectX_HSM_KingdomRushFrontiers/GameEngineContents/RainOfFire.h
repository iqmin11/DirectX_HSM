#pragma once
class RainOfFire
{
public:
	// construtor destructor
	RainOfFire();
	~RainOfFire();

	// delete Function
	RainOfFire(const RainOfFire& _Other) = delete;
	RainOfFire(RainOfFire&& _Other) noexcept = delete;
	RainOfFire& operator=(const RainOfFire& _Other) = delete;
	RainOfFire& operator=(RainOfFire&& _Other) noexcept = delete;

protected:


private:

};

