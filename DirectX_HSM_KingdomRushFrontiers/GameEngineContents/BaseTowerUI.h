#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

protected:

	void Start() override;
	void Update(float _DeltaTime) override;
	virtual void UpdateStart();
	virtual void UpdateEnd();

private:
	std::shared_ptr<class GameEngineUIRenderer> RingRender = nullptr;
	float4 RingRenderScale = { 171,171,1 };

};

