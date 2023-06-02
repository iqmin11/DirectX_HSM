#pragma once
#include "BaseBuildButton.h"
class BuildMeleeButton : public BaseBuildButton
{
public:
	// construtor destructor
	BuildMeleeButton();
	~BuildMeleeButton();

	// delete Function
	BuildMeleeButton(const BuildMeleeButton& _Other) = delete;
	BuildMeleeButton(BuildMeleeButton&& _Other) noexcept = delete;
	BuildMeleeButton& operator=(const BuildMeleeButton& _Other) = delete;
	BuildMeleeButton& operator=(BuildMeleeButton&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

