#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"
#include <GameEngineCore\GameEngineFSM.h>

enum class MouseState
{
	Release,
	Press,
	RainOfFire,
	CallReinforcement,
	Hero,
	UnitPos,
	Invalid
};

class MousePointer : public GameEngineActor
{
public:
	static MousePointer* MainMouse;

	// construtor destructor
	MousePointer();
	~MousePointer();

	// delete Function
	MousePointer(const MousePointer& _Other) = delete;
	MousePointer(MousePointer&& _Other) noexcept = delete;
	MousePointer& operator=(const MousePointer& _Other) = delete;
	MousePointer& operator=(MousePointer&& _Other) noexcept = delete;

	static const float4 GetIngameMousePos()
	{
		return float4{ MousePos.x, MousePos.y, MousePos.y};
	}
	static const float4& GetMousePosRef()
	{
		return MousePos;
	}
	static const float4 GetMouseWinPosRef();
	static const float4 GetMouseColmapPos();

	bool IsThereMouseOntheColMap();
	

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static float4 MousePos;
	MouseState State = MouseState::Release;
	std::shared_ptr<class _101UIRenderer> MousePointerRenderer = nullptr;
	float4 RendererScale = { 136,136,1 };
	std::shared_ptr<class GameEngineCollision> MousePointerCol = nullptr;
	GameEngineFSM MouseFSM = GameEngineFSM();

	std::shared_ptr<GameEngineCamera> UICam = nullptr;
	float4x4 UICamViewPort = float4x4();
	float4x4 UICamProj = float4x4();
	float4x4 UICamView = float4x4();

	void CalMousePos();

	void ReleaseStateInit();
	void PressStateInit();
	void RainOfFireStateInit();
	void CallReinforcementStateInit();
	void HeroStateInit();
	void UnitPosStateInit();
	void InvalidStateInit();
};

