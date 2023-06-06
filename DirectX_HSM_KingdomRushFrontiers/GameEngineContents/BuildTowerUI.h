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

	BuildArea* GetParentArea()
	{
		return ParentArea;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	BuildArea* ParentArea = nullptr;

	std::shared_ptr<class BuildRangedButton> AcBuildRangedButton = nullptr;
	std::shared_ptr<class BuildMeleeButton> AcBuildMeleeButton = nullptr;

	std::shared_ptr<class BuildMagicButton> AcBuildMagicButton = nullptr;
	std::shared_ptr<class BuildArtilleryButton> AcBuildArtilleryButton = nullptr;

	float4 Button0LocPos = { -58,58,-1000 };
	float4 Button1LocPos = { 58,58,-1000 };
	float4 Button2LocPos = { -58,-58,-1000 };
	float4 Button3LocPos = { 58,-58,-1000 };

};

