#pragma once
#include <GameEngineCore/GameEngineActor.h>

class TestActor : public GameEngineActor
{
public:
	// construtor destructor
	TestActor();
	~TestActor();

	// delete Function
	TestActor(const TestActor& _Other) = delete;
	TestActor(TestActor&& _Other) noexcept = delete;
	TestActor& operator=(const TestActor& _Other) = delete;
	TestActor& operator=(TestActor&& _Other) noexcept = delete;

protected:
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:

};

