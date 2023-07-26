#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"
#include <GameEngineCore\GameEngineFSM.h>

class Title_MousePointer : public GameEngineActor
{
public:
	// construtor destructor
	Title_MousePointer();
	~Title_MousePointer();

	// delete Function
	Title_MousePointer(const Title_MousePointer& _Other) = delete;
	Title_MousePointer(Title_MousePointer&& _Other) noexcept = delete;
	Title_MousePointer& operator=(const Title_MousePointer& _Other) = delete;
	Title_MousePointer& operator=(Title_MousePointer&& _Other) noexcept = delete;

	void ButtonClick();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 MousePos = float4::Zero;

	MouseState State = MouseState::Release;
	std::shared_ptr<class _101UIRenderer> MousePointerRenderer = nullptr;
	float4 RendererScale = { 136,136,1 };
	std::shared_ptr<class GameEngineCollision> MousePointerCol = nullptr;
	GameEngineFSM MouseFSM = GameEngineFSM();

	std::shared_ptr<GameEngineCamera> UICam = nullptr;
	float4x4 UICamViewPort = float4x4();
	float4x4 UICamProj = float4x4();
	float4x4 UICamView = float4x4();

	void ReleaseStateInit();
	void PressStateInit();
	void CalMousePos();

};

