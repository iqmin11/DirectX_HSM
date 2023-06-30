#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class DefeatBadgeState
{
	Fall,
	Update
};

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
	std::shared_ptr<class _101UIRenderer> BadgeRenderer = nullptr;

	std::shared_ptr<class Defeat_RetryButton> AcRetryButton = nullptr;
	float4 AcRetryButtonLocPos = {-85,-120};

	std::shared_ptr<class Defeat_ExitButton> AcExitButton = nullptr;
	float4 AcExitButtonLocPos = { 85,-120 };

	std::vector<std::string> Tips = std::vector<std::string>();
	std::shared_ptr<class _101UIFontRenderer> TipRender = nullptr;
	std::string Font = "³ª´®¼Õ±Û¾¾ Ææ OTF";
	float FontScale = 30;
	float4 FontColor = { 1.f, 1.f, 1.f }; ;
	float4 FontLocPos = { 0,30 };

	float4 StartPos = {0,800};
	float4 EndPos = float4::Zero;
	float Time = 0.f;
	float Ratio = 0.f;
	DefeatBadgeState State = DefeatBadgeState::Fall;
	void FallBadge(float _DeltaTime);
	void SetTips();
	void RenderTips(int _Index);
};

