#pragma once
#include "BaseBuildButton.h"
class BuildMagicButton : public BaseBuildButton
{
public:
	// construtor destructor
	BuildMagicButton();
	~BuildMagicButton();

	// delete Function
	BuildMagicButton(const BuildMagicButton& _Other) = delete;
	BuildMagicButton(BuildMagicButton&& _Other) noexcept = delete;
	BuildMagicButton& operator=(const BuildMagicButton& _Other) = delete;
	BuildMagicButton& operator=(BuildMagicButton&& _Other) noexcept = delete;
	
	static std::shared_ptr<BuildMagicButton> CreateButton(class BuildTowerUI* _UI);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

