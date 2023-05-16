#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include "PlayStageUI.h"

class Stage0 : public GameEngineActor
{
public:
	// construtor destructor
	Stage0();
	~Stage0();

	// delete Function
	Stage0(const Stage0& _Other) = delete;
	Stage0(Stage0&& _Other) noexcept = delete;
	Stage0& operator=(const Stage0& _Other) = delete;
	Stage0& operator=(Stage0&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

