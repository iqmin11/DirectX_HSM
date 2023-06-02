#pragma once
#include "BaseBuildButton.h"

class BuildRangedButton : public BaseBuildButton
{
public:
	// construtor destructor
	BuildRangedButton();
	~BuildRangedButton();

	// delete Function
	BuildRangedButton(const BuildRangedButton& _Other) = delete;
	BuildRangedButton(BuildRangedButton&& _Other) noexcept = delete;
	BuildRangedButton& operator=(const BuildRangedButton& _Other) = delete;
	BuildRangedButton& operator=(BuildRangedButton&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
};

