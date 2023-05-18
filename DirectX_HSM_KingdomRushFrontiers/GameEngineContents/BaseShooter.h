#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>
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

	const float4& GetTargetPos() const
	{
		return *TargetPos;
	}

	void SetTargetPos(float4& _TargetPos)
	{
		TargetPos = &_TargetPos;
	}

	void SetTowerData(TowerData* _Data)
	{
		Data = _Data;
	}
	
protected:
	std::shared_ptr<class GameEngineSpriteRenderer> BaseShooterRenderer = nullptr;
	std::function<void(float)> Attack = nullptr;
	TowerData* Data = nullptr;
	std::string Dir_x = std::string();
	std::string Dir_y = std::string();

	GameEngineFSM ShooterFSM = GameEngineFSM();
	std::function<void()> IdleStateInit = nullptr;
	std::function<void()> AttackStateInit = nullptr;

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float Time = 0.0f;
	float4* TargetPos = nullptr;

	void CheckDir();
};

// ���� �������� Update�ǰ��ִ� ������ ������ �޾ƾ���.
// �� ���͵� �� 1. �����ȿ� ���������鼭, 2. ��ǥ ������ ���� ����� ������ ��ġ�� Ÿ�� ����� �����ؾ��� (�������� �� ���߿�)
