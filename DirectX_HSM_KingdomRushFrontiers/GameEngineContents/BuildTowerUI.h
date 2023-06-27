#pragma once
#include "BaseTowerUI.h"
#include "ContentsEnum.h"

class GameEngineUIRenderer;
class BuildArea;
class BuildTowerUI : public BaseTowerUI
{
public:
	// construtor destructor
	BuildTowerUI();
	~BuildTowerUI();

	// delete Function
	BuildTowerUI(const BuildTowerUI& _Other) = delete;
	BuildTowerUI(BuildTowerUI&& _Other) noexcept = delete;
	BuildTowerUI& operator=(const BuildTowerUI& _Other) = delete;
	BuildTowerUI& operator=(BuildTowerUI&& _Other) noexcept = delete;

	static std::shared_ptr<BuildTowerUI> CreateBuildTowerUI(BuildArea* _ParentArea);

	BuildArea* GetParentArea();

	std::weak_ptr<class BuildRangedButton> GetBuildRangedButton()
	{
		return std::weak_ptr<class BuildRangedButton>(AcBuildRangedButton);
	}

	std::weak_ptr<class BuildMeleeButton> GetBuildMeleeButton()
	{
		return std::weak_ptr<class BuildMeleeButton>(AcBuildMeleeButton);
	}

	std::weak_ptr<class BuildMagicButton> GetBuildMagicButton()
	{
		return std::weak_ptr<class BuildMagicButton>(AcBuildMagicButton);
	}

	std::weak_ptr<class BuildArtilleryButton> GetBuildArtilleryButton()
	{
		return std::weak_ptr<class BuildArtilleryButton>(AcBuildArtilleryButton);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class BuildRangedButton> AcBuildRangedButton = nullptr;
	std::shared_ptr<class BuildMeleeButton> AcBuildMeleeButton = nullptr;

	std::shared_ptr<class BuildMagicButton> AcBuildMagicButton = nullptr;
	std::shared_ptr<class BuildArtilleryButton> AcBuildArtilleryButton = nullptr;

	float4 Button0LocPos = { -58,58 };
	float4 Button1LocPos = { 58,58 };
	float4 Button2LocPos = { -58,-58 };
	float4 Button3LocPos = { 58,-58 };

};

