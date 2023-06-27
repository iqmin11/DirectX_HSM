#pragma once
#include "BaseBuildButton.h"

class BuildArtilleryButton : public BaseBuildButton
{
public:
	// construtor destructor
	BuildArtilleryButton();
	~BuildArtilleryButton();

	// delete Function
	BuildArtilleryButton(const BuildArtilleryButton& _Other) = delete;
	BuildArtilleryButton(BuildArtilleryButton&& _Other) noexcept = delete;
	BuildArtilleryButton& operator=(const BuildArtilleryButton& _Other) = delete;
	BuildArtilleryButton& operator=(BuildArtilleryButton&& _Other) noexcept = delete;
	
	static std::shared_ptr<BuildArtilleryButton> CreateButton(class BuildTowerUI* _UI);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
};

