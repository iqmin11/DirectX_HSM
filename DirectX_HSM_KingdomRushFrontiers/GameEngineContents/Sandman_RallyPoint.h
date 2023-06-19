#pragma once
class Sandman_RallyPoint
{
public:
	// construtor destructor
	Sandman_RallyPoint();
	~Sandman_RallyPoint();

	// delete Function
	Sandman_RallyPoint(const Sandman_RallyPoint& _Other) = delete;
	Sandman_RallyPoint(Sandman_RallyPoint&& _Other) noexcept = delete;
	Sandman_RallyPoint& operator=(const Sandman_RallyPoint& _Other) = delete;
	Sandman_RallyPoint& operator=(Sandman_RallyPoint&& _Other) noexcept = delete;

protected:


private:

};

