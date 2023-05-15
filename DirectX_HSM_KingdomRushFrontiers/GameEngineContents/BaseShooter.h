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
	std::shared_ptr<class GameEngineSpriteRenderer> BaseShooterRenderer = nullptr;
	std::function<void()> Attack = nullptr;

	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;

	float AttackSpeed = 1.0f;
	float Time = 0.0f;

	float Range = 0.f;
	float4 ParentPos = float4::Zero;

	//void Attack();

	std::shared_ptr<class GameEngineSpriteRenderer> TestTargetRender = nullptr;
	float4 TargetPos = {200,200};
};

// 현재 레벨에서 Update되고있는 몬스터의 정보를 받아야함.
// 그 몬스터들 중 1. 범위안에 들어와있으면서, 2. 목표 지점과 가장 가까운 몬스터의 위치를 타겟 포즈로 설정해야함 (디테일은 좀 나중에)
