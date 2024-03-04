#pragma once
#include "ContentsButton.h"
#include "ContentsData.h"
#include "PlayManager.h"

class BaseBuildButton : public ContentsButton
{
public:
	// construtor destructor
	BaseBuildButton();
	~BaseBuildButton();

	// delete Function
	BaseBuildButton(const BaseBuildButton& _Other) = delete;
	BaseBuildButton(BaseBuildButton&& _Other) noexcept = delete;
	BaseBuildButton& operator=(const BaseBuildButton& _Other) = delete;
	BaseBuildButton& operator=(BaseBuildButton&& _Other) noexcept = delete;


	int GetPrice()
	{
		return Price;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SetPrice(int _Price);

	class BuildTowerUI* ParentUI = nullptr;
	int Price = 0;
	std::string InvalidTextureName = std::string();
private:
	std::shared_ptr<class GameEngineUIRenderer> ButtonGlow = nullptr;

	float4 Scale = { 68,60,1 };
	float4 GlowScale = { 75,68,1 };

	std::shared_ptr<class PriceTag> AcPriceTag = nullptr;
	void SetInvalid();
};

