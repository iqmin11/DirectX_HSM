#pragma once
class Sandman_Fighter
{
public:
	// construtor destructor
	Sandman_Fighter();
	~Sandman_Fighter();

	// delete Function
	Sandman_Fighter(const Sandman_Fighter& _Other) = delete;
	Sandman_Fighter(Sandman_Fighter&& _Other) noexcept = delete;
	Sandman_Fighter& operator=(const Sandman_Fighter& _Other) = delete;
	Sandman_Fighter& operator=(Sandman_Fighter&& _Other) noexcept = delete;

protected:


private:

};

