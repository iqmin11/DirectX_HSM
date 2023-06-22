#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>
#include "ContentsData.h"

enum class PlayerState
{
	Idle,
	RainOfFire,
	CallReinforcement,
	Hero,
	Tower,
	UnitPos,
};

class PlayManager : public GameEngineActor
{
public:
	static PlayManager* MainPlayer;
	static class Melee_Tower* SelectedMeleeTower;

	// construtor destructor
	PlayManager();
	~PlayManager();

	// delete Function
	PlayManager(const PlayManager& _Other) = delete;
	PlayManager(PlayManager&& _Other) noexcept = delete;
	PlayManager& operator=(const PlayManager& _Other) = delete;
	PlayManager& operator=(PlayManager&& _Other) noexcept = delete;

	void SetState(PlayerState _State)
	{
		State = _State;
	}

	const PlayerState& GetState() const
	{
		return State;
	}

	const PlayerData& GetData() const
	{
		return Data;
	}

	const std::weak_ptr<class Hero_RallyPoint> GetHero() const;
	

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	PlayerState State = PlayerState::Idle;
	GameEngineFSM PlayerFSM = GameEngineFSM();
	PlayerData Data = PlayerData();

	void IdleStateInit();
	void RainOfFireStateInit();
	void CallReinforcementStateInit();
	void HeroStateInit();
	void TowerStateInit();
	void UnitPosStateInit();
};

