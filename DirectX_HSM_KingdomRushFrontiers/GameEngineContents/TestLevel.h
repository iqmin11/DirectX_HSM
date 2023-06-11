#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class TestLevel : public GameEngineLevel
{
public:
	// construtor destructor
	TestLevel();
	~TestLevel();

	// delete Function
	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(TestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	
	std::shared_ptr<class ContentsButton> TestButton = nullptr;
	std::shared_ptr<class PopText> TestPopText = nullptr;

};

