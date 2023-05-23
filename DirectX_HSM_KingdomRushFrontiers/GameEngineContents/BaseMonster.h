#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"
#include "ContentsData.h"

class BaseMonster : public GameEngineActor
{
public:
	static std::list<std::shared_ptr<BaseMonster>> LiveMonsterList;
	// construtor destructor
	BaseMonster();
	~BaseMonster();

	// delete Function
	BaseMonster(const BaseMonster& _Other) = delete;
	BaseMonster(BaseMonster&& _Other) noexcept = delete;
	BaseMonster& operator=(const BaseMonster& _Other) = delete;
	BaseMonster& operator=(BaseMonster&& _Other) noexcept = delete;

	void SetPathInfo(std::vector<float4>& _PathInfo)
	{
		PathInfo = &_PathInfo;
		CurPoint = PathInfo->begin();
		NextPoint = ++(PathInfo->begin());
		LastPoint = --(PathInfo->end());
	}

	const float4& GetLastPoint() const
	{
		return *LastPoint;
	}

	static std::shared_ptr<BaseMonster> CreateMonster(const std::shared_ptr<GameEngineLevel> _Level, const MonsterEnum _Monster, std::vector<float4>& _PathInfo);
	float CalDistance();

	const float4& GetMonsterDir() const
	{
		return ActorDir;
	}

	const float GetMonsterSpeed() const
	{
		return Data.Speed;
	}

	std::shared_ptr<class GameEngineCollision> GetMonsterCol() const
	{
		return MonsterCol;
	}
	
	float CurHP = 0;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void WalkToNextPoint(float _DeltaTime);
	void WalkPath(float _DeltaTime);

	std::shared_ptr<class GameEngineSpriteRenderer> MonsterRenderer = nullptr;
	std::shared_ptr<class GameEngineCollision> MonsterCol = nullptr;
	MonsterData Data = MonsterData();

private:
	float4 ActorPos = float4::Zero;
	float4 PrevActorPos = float4::Zero;
	float4 ActorDir = float4::Zero;

	std::vector<float4>* PathInfo = nullptr;
	std::vector<float4>::iterator CurPoint = std::vector<float4>::iterator();
	std::vector<float4>::iterator NextPoint = std::vector<float4>::iterator();
	std::vector<float4>::iterator LastPoint = std::vector<float4>::iterator();

	std::shared_ptr<class GameEngineSpriteRenderer> LifeBarBg = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> LifeBar = nullptr;
	float4 LifeBarScale = { 20,2,1 };
	float4 LifeBarBgLocalPos = { 0,20,1 };
	float4 LifeBarLocalPos = { 0,20 };

	float Time = 0;
	float Ratio = 0;

	void LiveMonsterListRelease();
	void CalMonsterDir();

	void UpdateLiveBar();
};

