#pragma once
#include <GameEngineCore/GameEngineActor.h>

class DefeatBadge : public GameEngineActor
{
public:
	// construtor destructor
	DefeatBadge();
	~DefeatBadge();

	// delete Function
	DefeatBadge(const DefeatBadge& _Other) = delete;
	DefeatBadge(DefeatBadge&& _Other) noexcept = delete;
	DefeatBadge& operator=(const DefeatBadge& _Other) = delete;
	DefeatBadge& operator=(DefeatBadge&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderScale = { 494,398,1 };
	std::shared_ptr<class GameEngineUIRenderer> BadgeRenderer = nullptr;
	
};

