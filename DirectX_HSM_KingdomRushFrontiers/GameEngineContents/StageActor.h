#pragma once
#include <GameEngineCore\GameEngineActor.h>

class StageActor : public GameEngineActor
{
public:
	static bool Pause;

	// construtor destructor
	StageActor();
	~StageActor();

	// delete Function
	StageActor(const StageActor& _Other) = delete;
	StageActor(StageActor&& _Other) noexcept = delete;
	StageActor& operator=(const StageActor& _Other) = delete;
	StageActor& operator=(StageActor&& _Other) noexcept = delete;

protected:

private:

};

