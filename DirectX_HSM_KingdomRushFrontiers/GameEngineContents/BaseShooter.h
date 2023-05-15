#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BaseShooter : public GameEngineActor
{
public:
	// construtor destructor
	BaseShooter();
	~BaseShooter();

	// delete Function
	BaseShooter(const BaseShooter& _Other) = delete;
	BaseShooter(BaseShooter&& _Other) noexcept = delete;
	BaseShooter& operator=(const BaseShooter& _Other) = delete;
	BaseShooter& operator=(BaseShooter&& _Other) noexcept = delete;

	const float4& GetActorPos() const
	{
		return ActorPos;
	}

	const float4& GetTargetPos() const
	{
		return TargetPos;
	}

	void SetRange(float _Range)
	{
		Range = _Range;
	}

	void SetParentPos(float4 _Pos)
	{
		ParentPos = _Pos;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;
	float4 RenderScalse = {32, 32};

	std::shared_ptr<class GameEngineSpriteRenderer> BaseShooterRenderer = nullptr;
	float AttackSpeed = 1.0f;
	float Time = 0.0f;

	float Range = 0.f;
	float4 ParentPos = float4::Zero;

	void Attack();

	std::shared_ptr<class GameEngineSpriteRenderer> TestTargetRender = nullptr;
	float4 TargetPos = {200,200};
};

