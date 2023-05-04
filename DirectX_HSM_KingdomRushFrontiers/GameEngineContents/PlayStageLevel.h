#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum class StageState
{
	NullState = -1,
	Stage1,
	Stage2,
	Stage3,
	Stage4,
	Stage5,
	Stage6
};

class PlayStageLevel : public GameEngineLevel
{
public:
	// construtor destructor
	PlayStageLevel();
	~PlayStageLevel();

	// delete Function
	PlayStageLevel(const PlayStageLevel& _Other) = delete;
	PlayStageLevel(PlayStageLevel&& _Other) noexcept = delete;
	PlayStageLevel& operator=(const PlayStageLevel& _Other) = delete;
	PlayStageLevel& operator=(PlayStageLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	StageState Stage = StageState::NullState;
	
	std::shared_ptr<class StageMap> AcStageMap = nullptr;
	std::shared_ptr<class PlayStageUI> AcPlayStageUI = nullptr;
	std::shared_ptr<class BaseMonster> AcBaseMonster = nullptr;
	std::shared_ptr<class MonsterPath> AcMonsterPath = nullptr;


	void KeySet();
	
};

