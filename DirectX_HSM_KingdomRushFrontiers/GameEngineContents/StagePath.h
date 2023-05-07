#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

//class LinePath
//{
//	int Index;
//	std::vector<float4> Points;
//};

class StagePath : public GameEngineActor
{
public:
	// construtor destructor
	StagePath();
	~StagePath();

	// delete Function
	StagePath(const StagePath& _Other) = delete;
	StagePath(StagePath&& _Other) noexcept = delete;
	StagePath& operator=(const StagePath& _Other) = delete;
	StagePath& operator=(StagePath&& _Other) noexcept = delete;
	
	void AddStageLine();
	void AddLinePoint();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
private:
	const StageEnum* StagePtr = nullptr;
	const StageEditMode* EditModePtr = nullptr;
	//std::vector<LinePath> EditedLines = std::vector<LinePath>();


};

