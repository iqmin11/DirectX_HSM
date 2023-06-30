#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"

class Effect_OneStar : public GameEngineActor
{
public:
	// construtor destructor
	Effect_OneStar();
	~Effect_OneStar();

	// delete Function
	Effect_OneStar(const Effect_OneStar& _Other) = delete;
	Effect_OneStar(Effect_OneStar&& _Other) noexcept = delete;
	Effect_OneStar& operator=(const Effect_OneStar& _Other) = delete;
	Effect_OneStar& operator=(Effect_OneStar&& _Other) noexcept = delete;
	
	static void CreatStar(class GameEngineLevel* _Level, const float4& _StartPos, const float4 _Dir, float _Gravity, float _Speed);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class _101UIRenderer> StarRender = nullptr;
	float4 RenderScale = { 25,22,1 };
	float4 StartPos = float4::Zero;
	float4 Dir = {1.f,0.f,0.f,0.f};

	float Gravity = 0.f;
	float MaxGravity = 3000.f;
	float Acceleration = 1400.f;

	float Speed = 200.f;
	float Time = 0.f;

};

