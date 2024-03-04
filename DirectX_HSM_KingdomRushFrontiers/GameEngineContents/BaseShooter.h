#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEnginePlatform\GameEngineSound.h>
#include "ContentsData.h"

enum class ShooterState
{
	Idle,
	Attack
};

class BaseShootingTower;
class BaseShooter : public GameEngineActor
{
public:
	// construtor destructor
	BaseShooter();
	~BaseShooter() = 0 {};

	// delete Function
	BaseShooter(const BaseShooter& _Other) = delete;
	BaseShooter(BaseShooter&& _Other) noexcept = delete;
	BaseShooter& operator=(const BaseShooter& _Other) = delete;
	BaseShooter& operator=(BaseShooter&& _Other) noexcept = delete;

	const float4& GetTargetPos() const
	{
		return *TargetPos;
	}

	const BaseShootingTower* GetParentTower() const
	{
		return ParentTower;
	}

	void SetTargetPos(float4& _TargetPos)
	{
		TargetPos = &_TargetPos;
	}

	void SetParentTower(class BaseShootingTower* _Tower)
	{
		ParentTower = _Tower;
	}

	void ChangeBaseShooterAnimation(const std::string_view& _AnimationName);

	ShooterState StateValue = ShooterState::Idle;
	
protected:
	class BaseShootingTower* ParentTower = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BaseShooterRenderer = nullptr;
	std::function<void()> Attack = nullptr;
	std::string Dir_x = std::string();
	std::string Dir_y = std::string();

	GameEngineFSM ShooterFSM = GameEngineFSM();
	bool IsShootBullet = false;

	void IdleStateInit();
	void AttackStateInit();

	void Start() override;
	void Update(float _DeltaTime) override;

	GameEngineSoundPlayer ShooterSound = GameEngineSoundPlayer();
	std::vector<std::string> ShooterSoundNames = std::vector<std::string>();
	void PlayShooterSound(const std::string_view& _Name);

private:

	float Time = 0.0f;
	float4* TargetPos = nullptr;


	void CheckDir();
};

