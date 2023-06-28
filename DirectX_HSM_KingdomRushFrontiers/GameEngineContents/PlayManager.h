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

	int Gold = -1;
	int Life = -1;

	void InitPlayManager();

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

	const std::weak_ptr<class Hero_RallyPoint> GetHeroRally() const;

	bool IsAvailable_RainOfFire() const
	{
		return Available_RainOfFire;
	}

	bool IsAvailable_CallReinforcement() const
	{
		return Available_CallReinforcement;
	}

	void RainOfFire_StartCoolTime()
	{
		RainOfFire_Cooltime = 0.f;
		Available_RainOfFire = false;
	}

	void CallReinforcement_StartCoolTime()
	{
		CallReinforcement_Cooltime = 0.f;
		Available_CallReinforcement = false;
	}

	float GetRainOfFireCoolRatio()
	{
		return RainOfFire_Cooltime / RainOfFire_MaxCool;
	}

	float GetCallReinforcementCoolRatio()
	{
		return CallReinforcement_Cooltime / CallReinforcement_MaxCool;
	}
	
	enum class FighterState GetHeroState() const;

	bool DoIHaveEnoughGold(int _Price)
	{
		return _Price <= Gold;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	PlayerState State = PlayerState::Idle;
	GameEngineFSM PlayerFSM = GameEngineFSM();
	PlayerData Data = PlayerData();

	float RainOfFire_Cooltime = 80.f;
	float RainOfFire_MaxCool = 80.f;
	bool Available_RainOfFire = false;

	float CallReinforcement_Cooltime = 10.f;
	float CallReinforcement_MaxCool = 10.f;
	bool Available_CallReinforcement = false;

	void CalCoolTime_RainOfFire(float _DeltaTime);
	void CalCoolTime_CallReinforcement(float _DeltaTime);

	void IdleStateInit();
	void RainOfFireStateInit();
	void CallReinforcementStateInit();
	void HeroStateInit();
	void TowerStateInit();
	void UnitPosStateInit();

};

