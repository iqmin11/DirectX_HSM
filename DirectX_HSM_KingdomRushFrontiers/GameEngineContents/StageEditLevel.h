#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class StageEditLevel : public GameEngineLevel
{
public:
	// construtor destructor
	StageEditLevel();
	~StageEditLevel();

	// delete Function
	StageEditLevel(const StageEditLevel& _Other) = delete;
	StageEditLevel(StageEditLevel&& _Other) noexcept = delete;
	StageEditLevel& operator=(const StageEditLevel& _Other) = delete;
	StageEditLevel& operator=(StageEditLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class MapEdit> AcMapEdit = nullptr;

	void SetKey();

};

