#pragma once
#include <GameEngineCore\GameEngineActor.h>

enum class PlayerState
{
	Idle,
	RainOfFire,
	CallReinforcement,
	Hero,
	Tower,
};

class PlayManager : public GameEngineActor
{
public:
	static PlayManager* MainPlayer;
	
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	PlayerState State = PlayerState::Idle;

};

