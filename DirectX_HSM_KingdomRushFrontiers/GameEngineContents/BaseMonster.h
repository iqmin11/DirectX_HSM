#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class BaseMonster : public GameEngineActor
{
public:
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
	}

	static void CreateMonster(const std::shared_ptr<GameEngineLevel> _Level, const MonsterEnum _Monster, std::vector<float4>& _PathInfo);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void WalkToNextPoint(float _DeltaTime);
	void WalkPath(float _DeltaTime);

	std::shared_ptr<class GameEngineSpriteRenderer> MonsterRenderer = nullptr;

private:
	float4 ActorPos = float4::Zero;

	std::vector<float4>* PathInfo = nullptr;
	std::vector<float4>::iterator CurPoint = std::vector<float4>::iterator();
	std::vector<float4>::iterator NextPoint = std::vector<float4>::iterator();
	float Speed = 100;
	float Time = 0;
	float Ratio = 0;
};

