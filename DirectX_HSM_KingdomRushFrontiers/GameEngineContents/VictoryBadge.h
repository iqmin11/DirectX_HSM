#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"

enum class BadgeState
{
	GrowBig,
	Star,
	FallButton,
	Update
};

class VictoryBadge : public GameEngineActor
{
public:
	// construtor destructor
	VictoryBadge();
	~VictoryBadge();

	// delete Function
	VictoryBadge(const VictoryBadge& _Other) = delete;
	VictoryBadge(VictoryBadge&& _Other) noexcept = delete;
	VictoryBadge& operator=(const VictoryBadge& _Other) = delete;
	VictoryBadge& operator=(VictoryBadge&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> VictoryBadgeBg = nullptr;
	float4 VictoryBadgeBgScale = { 536,406,1 };

	std::shared_ptr<class UIFontRenderer> FontRender = nullptr;
	std::string Victory = "승리";
	std::string Font = "제주한라산";
	float FontScale = 115;
	float4 FontColor = { 0.2980392156862745f, 0.2196078431372549f, 0.0901960784313725f }; ;
	float4 FontLocPos = {0,65};

	std::shared_ptr<class GameEngineUIRenderer> StarAnimation = nullptr;
	float4 StarAnimationScale = { 215,215,1 };
	float4 StarAnimationLocPos = {0, -100};

	std::shared_ptr<class ContinueButton> AcContinueButton = nullptr;
	float4 ContinueButtonEndLocPos = { 0,-235 };

	BadgeState State = BadgeState::GrowBig;
	float Time = 0.f;
	float Ratio = 0.f;
	void SetBg();
	void SetVictoryFont();
	void SetStarAnimation();
	void GrowBig(float _DeltaTime);
	void FallButton(float _DeltaTime);
};

