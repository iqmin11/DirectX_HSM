#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class BuildArea : public GameEngineActor
{
public:
	// construtor destructor
	BuildArea();
	~BuildArea();

	// delete Function
	BuildArea(const BuildArea& _Other) = delete;
	BuildArea(BuildArea&& _Other) noexcept = delete;
	BuildArea& operator=(const BuildArea& _Other) = delete;
	BuildArea& operator=(BuildArea&& _Other) noexcept = delete;

	static std::shared_ptr<BuildArea> CreateBuildArea(class GameEngineLevel* _Level, const float4& _ActorPos, const float4& _RallyPos);
	void ReleaseChildTower();

	void CreateRangedTower();
	void CreateMeleeTower();
	void CreateMagicTower();
	void CreateArtilleryTower();
	
	std::shared_ptr<class BuildTowerUI> BuildUI = nullptr;

	const float4& GetRallyPos() const
	{
		return RallyPos;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;
	float4 RallyPos = float4::Zero;
	std::shared_ptr<class GameEngineSpriteRenderer> BuildAreaRenderer = nullptr;
	float4 RenderScale = {128,128,1};
	
	std::shared_ptr<class GameEngineCollision> BuildAreaCol = nullptr;
	float4 ColScale = { 105,60,1 };

	std::shared_ptr<class BaseTower> ChildTower = nullptr;

	std::shared_ptr<class BuildAreaButton> AreaButton = nullptr;

	float4 BuildUILocPos = { 0,0,0 };

	std::string ReleaseTextureName = "build_terrain_0004.png";
	std::string HoverTextureName = "build_terrain_0004_Hover.png";
};
// 이걸 기준으로 나중에 건물들의 이미지를 조정하자.
// 타워의 바닥이 액터의 중심인게 옳다고 하기로 한거야
