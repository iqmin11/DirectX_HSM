#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <memory>

class StageEditor;
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

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class PathEdit> AcPathEdit = nullptr;

	std::shared_ptr<class StageEditor> Editor;

	void SetKey();

};

