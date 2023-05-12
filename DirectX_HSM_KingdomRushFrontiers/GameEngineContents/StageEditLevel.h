#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <memory>

#include "ContentsEnum.h"

class StageEditLevel : public GameEngineLevel
{
public:
	static StageEditLevel* MainStageEditLevel;

	// construtor destructor
	StageEditLevel();
	~StageEditLevel();

	// delete Function
	StageEditLevel(const StageEditLevel& _Other) = delete;
	StageEditLevel(StageEditLevel&& _Other) noexcept = delete;
	StageEditLevel& operator=(const StageEditLevel& _Other) = delete;
	StageEditLevel& operator=(StageEditLevel&& _Other) noexcept = delete;

	//AcGet

	std::shared_ptr<class StageBg> GetAcStageBg() const
	{
		return AcStageBg;
	}

	const int* GetStageLevelPtr() const
	{
		return &StageLevel;
	}

	void SetStageLevel(int _Stage)
	{
		StageLevel = _Stage;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	int StageLevel = 0;
	//StageEditMode EditMod = StageEditMode::Null;

	std::shared_ptr<class StageBg> AcStageBg = nullptr;
	//std::shared_ptr<class StagePath> AcStagePath = nullptr;
	
	std::shared_ptr<class StageEditor> Editor;

	void SetKey();

};

