#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class FightObjBase : public GameEngineActor
{
public:
	// construtor destructor
	FightObjBase();
	~FightObjBase();
	
	// delete Function
	FightObjBase(const FightObjBase& _Other) = delete;
	FightObjBase(FightObjBase&& _Other) noexcept = delete;
	FightObjBase& operator=(const FightObjBase& _Other) = delete;
	FightObjBase& operator=(FightObjBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;
	std::shared_ptr<class GameEngineSpriteRenderer> TestRenderer = nullptr;
	float4 TestRendererScale = {64,64,1};
};

