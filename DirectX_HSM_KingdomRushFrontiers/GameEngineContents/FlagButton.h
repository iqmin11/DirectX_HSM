#pragma once
#include "ContentsButton.h"

class FlagButton : public ContentsButton
{
public:
	// construtor destructor
	FlagButton();
	~FlagButton();

	// delete Function
	FlagButton(const FlagButton& _Other) = delete;
	FlagButton(FlagButton&& _Other) noexcept = delete;
	FlagButton& operator=(const FlagButton& _Other) = delete;
	FlagButton& operator=(FlagButton&& _Other) noexcept = delete;

	static std::shared_ptr<FlagButton> CreateButton(class WorldMapFlag* _Parent, std::function<void()> _Click);


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ButtonScale = { 38, 58, 1 };
};

