#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MonsterMotionPath : public GameEngineActor
{
public:
	// construtor destructor
	MonsterMotionPath();
	~MonsterMotionPath();

	// delete Function
	MonsterMotionPath(const MonsterMotionPath& _Other) = delete;
	MonsterMotionPath(MonsterMotionPath&& _Other) noexcept = delete;
	MonsterMotionPath& operator=(const MonsterMotionPath& _Other) = delete;
	MonsterMotionPath& operator=(MonsterMotionPath&& _Other) noexcept = delete;

protected:


private:
	std::vector<float4> PathPoints = {};


};

