#pragma once
#include <GameEngineCore\GameEngineActor.h>

class PlayManager : public GameEngineActor
{
public:
	// construtor destructor
	PlayManager();
	~PlayManager();

	// delete Function
	PlayManager(const PlayManager& _Other) = delete;
	PlayManager(PlayManager&& _Other) noexcept = delete;
	PlayManager& operator=(const PlayManager& _Other) = delete;
	PlayManager& operator=(PlayManager&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
		

};

