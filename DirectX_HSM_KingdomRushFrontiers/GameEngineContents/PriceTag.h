#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"

class PriceTag : public GameEngineActor
{
public:
	const static float4 ValidFontColor;
	const static float4 InvalidFontColor;

	// construtor destructor
	PriceTag();
	~PriceTag();

	// delete Function
	PriceTag(const PriceTag& _Other) = delete;
	PriceTag(PriceTag&& _Other) noexcept = delete;
	PriceTag& operator=(const PriceTag& _Other) = delete;
	PriceTag& operator=(PriceTag&& _Other) noexcept = delete;

	void SetPrice(int _Price);
	void SetColor(float4 _RGBA);


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> PriceTagBg = nullptr;
	float4 BgScale = { 40, 25, 1 };

	std::shared_ptr<class UIFontRenderer> PriceRender = nullptr;
	float4 FontLocPos = { 0,8 };
	float FontScale = 21;
};

