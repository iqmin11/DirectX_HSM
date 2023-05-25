#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class RallyPoint;
class BaseFighter : public GameEngineActor
{
public:
	// construtor destructor
	BaseFighter();
	~BaseFighter();

	// delete Function
	BaseFighter(const BaseFighter& _Other) = delete;
	BaseFighter(BaseFighter&& _Other) noexcept = delete;
	BaseFighter& operator=(const BaseFighter& _Other) = delete;
	BaseFighter& operator=(BaseFighter&& _Other) noexcept = delete;

	void SetParentRally(class RallyPoint* _Rally)
	{
		ParentRally = _Rally;
	}

	void SetRallyPos(float4 _Pos)
	{
		RallyPos = _Pos;
	}

	void SetPrevPos(float4 _Pos)
	{
		PrevPos = _Pos;
	}

	void ResetRatio();
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	RallyPoint* ParentRally = nullptr;

	float4 ActorPos = float4::Zero;
	float4 RallyPos = float4::Zero;
	float4 PrevPos = float4::Zero;
	std::shared_ptr<class GameEngineSpriteRenderer> FighterRenderer = nullptr;
	float4 FighterRendererScale = {64,64,1};

	float Speed = 100.f;
	float Time = 0.f;
	float Ratio = 0.f;
	//std::shared_ptr<class GameEngineCollision> BodyCollision = nullptr;
	//std::shared_ptr<class GameEngineCollision> RangeCollision = nullptr;
};

