#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

enum class BaseTowerUIState
{
	Start,
	Update,
};

class GameEngineUIRenderer;
class BaseTowerUI : public GameEngineActor
{
public:
	static int UpdateCount;
	static BaseTowerUI* UpdatedUI;
	
	// construtor destructor
	BaseTowerUI();
	~BaseTowerUI();

	// delete Function
	BaseTowerUI(const BaseTowerUI& _Other) = delete;
	BaseTowerUI(BaseTowerUI&& _Other) noexcept = delete;
	BaseTowerUI& operator=(const BaseTowerUI& _Other) = delete;
	BaseTowerUI& operator=(BaseTowerUI&& _Other) noexcept = delete;

	virtual void OnUI();
	virtual void OffUI();

	BaseTowerUIState GetState() const 
	{
		return State;
	}

protected:

	void Start() override;
	void Update(float _DeltaTime) override;
	virtual void UpdateStart();
	virtual void UpdateEnd();

	BaseTowerUIState State = BaseTowerUIState::Start;
private:

	std::shared_ptr<class GameEngineUIRenderer> RingRender = nullptr;
	float4 RingRenderScale = { 171,171,1 };
	float4 StartActorScale = { 0.5f, 0.5f, 0.5f };
	float Time = 0.0f;
};

