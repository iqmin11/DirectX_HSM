#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"

class Hero_Portrate : public GameEngineActor
{
public:
	// construtor destructor
	Hero_Portrate();
	~Hero_Portrate();

	// delete Function
	Hero_Portrate(const Hero_Portrate& _Other) = delete;
	Hero_Portrate(Hero_Portrate&& _Other) noexcept = delete;
	Hero_Portrate& operator=(const Hero_Portrate& _Other) = delete;
	Hero_Portrate& operator=(Hero_Portrate&& _Other) noexcept = delete;

	std::weak_ptr<class GameEngineUIRenderer> GetAlricPortate();

protected:
	void Start() override;

private:
	std::shared_ptr<class GameEngineUIRenderer> HeroPortrateFrame = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> AlricPortrate = nullptr;

	std::shared_ptr<class Button_Hero> HeroButton = nullptr;
	float4 HeroPortrateFrameScale = { 119,119,1 };
};

