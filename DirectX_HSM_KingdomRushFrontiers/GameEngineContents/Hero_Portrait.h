#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"

class Hero_Portrait : public GameEngineActor
{
public:
	// construtor destructor
	Hero_Portrait();
	~Hero_Portrait();

	// delete Function
	Hero_Portrait(const Hero_Portrait& _Other) = delete;
	Hero_Portrait(Hero_Portrait&& _Other) noexcept = delete;
	Hero_Portrait& operator=(const Hero_Portrait& _Other) = delete;
	Hero_Portrait& operator=(Hero_Portrait&& _Other) noexcept = delete;

	std::weak_ptr<class GameEngineUIRenderer> GetAlricPortate();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> HeroPortraitFrame = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> AlricPortrait = nullptr;
	std::shared_ptr<class UIFontRenderer> HeroLevelRender = nullptr;
	float LevelFontScale = 18.f;
	float4 LevelFontLocPos = { 19,-15 };

	std::shared_ptr<class Button_Hero> HeroButton = nullptr;
	float4 HeroPortraitFrameScale = { 119,119,1 };
	
	std::shared_ptr<class GameEngineUIRenderer> HeroHpBar = nullptr;
	float4 HeroHpBarScale = { 68, 4, 1 };
	float4 HeroHpBarLocPos= { 0, -40 };

	void UpdateLifeBar();
};

