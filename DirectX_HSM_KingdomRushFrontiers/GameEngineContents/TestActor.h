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
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	float Angle = 0.0f;
	std::shared_ptr<class GameEngineRenderer> Render0;
	std::shared_ptr<class GameEngineRenderer> Render1;
	std::shared_ptr<class GameEngineRenderer> Render2;
};

