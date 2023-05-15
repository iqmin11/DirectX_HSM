#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsData.h"

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

	void SetTowerData(TowerData* _Data)
	{
		Data = _Data;
	}

	void SetParentPos(float4 _Pos)
	{
		ParentPos = _Pos;
	}

protected:
	std::shared_ptr<class GameEngineSpriteRenderer> BaseShooterRenderer = nullptr;
	std::function<void()> Attack = nullptr;
	TowerData* Data = nullptr;

	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;

	float Time = 0.0f;

	float4 ParentPos = float4::Zero;

	//void Attack();

	std::shared_ptr<class GameEngineSpriteRenderer> TestTargetRender = nullptr;
	float4 TargetPos = {200,200};
};

// ���� �������� Update�ǰ��ִ� ������ ������ �޾ƾ���.
// �� ���͵� �� 1. �����ȿ� ���������鼭, 2. ��ǥ ������ ���� ����� ������ ��ġ�� Ÿ�� ����� �����ؾ��� (�������� �� ���߿�)
