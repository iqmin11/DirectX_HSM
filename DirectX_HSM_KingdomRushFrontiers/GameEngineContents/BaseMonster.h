#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

	void SetPathInfo(std::list<float4>& _PathInfo)
	{
		PathInfo = &_PathInfo;
		CurPoint = PathInfo->begin();
		NextPoint = ++(PathInfo->begin());
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void WalkToNextPoint(float _DeltaTime);
	void WalkPath(float _DeltaTime);

	std::shared_ptr<class GameEngineSpriteRenderer> MonsterRenderer = nullptr;

private:
	float4 ActorPos = float4::Zero;

	std::list<float4>* PathInfo = nullptr;
	std::list<float4>::iterator CurPoint = std::list<float4>::iterator();
	std::list<float4>::iterator NextPoint = std::list<float4>::iterator();
	float Time = 0;
	float Speed = 100;
	float Ratio = 0;
};
