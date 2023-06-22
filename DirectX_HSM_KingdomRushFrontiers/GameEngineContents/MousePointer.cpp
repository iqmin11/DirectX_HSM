#include "PrecompileHeader.h"
#include "MousePointer.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "PlayStageLevel.h"
#include "PlayManager.h"
#include "StageBg.h"
#include "Melee_Tower.h"

float4 MousePointer::MousePos = float4::Zero;
MousePointer* MousePointer::MainMouse = nullptr;

MousePointer::MousePointer()
{
	MainMouse = this;
}

MousePointer::~MousePointer()
{

}

const float4 MousePointer::GetMouseWinPosRef()
{
	return GameEngineWindow::GetMousePosition();
}

const float4 MousePointer::GetMouseColmapPos()
{
	return GameEngineWindow::GetMousePosition() + float4{-200, 50};
}

bool MousePointer::IsThereMouseOntheColMap()
{
	float4 MousePos = MousePointer::GetMouseColmapPos();
	std::weak_ptr LocalLevel(GetLevel()->DynamicThis<PlayStageLevel>());
	GameEnginePixelColor Pixel = LocalLevel.lock()->GetStageBg()->GetColmap(LocalLevel.lock()->GetCurStage())->GetPixel(MousePos.ix(), MousePos.iy());
	return GameEnginePixelColor(0, 0, 0, UCHAR_MAX) == Pixel || GameEnginePixelColor::Black == Pixel;
}

void MousePointer::Start()
{
	MousePointerRenderer = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::MousePoint);
	MousePointerRenderer->GetTransform()->SetWorldScale(RendererScale);
	MousePointerRenderer->CreateAnimation({.AnimationName = "Release", .SpriteName = "Mouse_Release"});
	MousePointerRenderer->CreateAnimation({.AnimationName = "Press", .SpriteName = "Mouse_Press"});
	MousePointerRenderer->CreateAnimation({.AnimationName = "RainOfFire", .SpriteName = "Mouse_RainOfFire", .FrameInter = 0.075f, .Loop = true});
	MousePointerRenderer->CreateAnimation({.AnimationName = "CallReinforcement", .SpriteName = "Mouse_CallReinforcement", .FrameInter = 0.075f, .Loop = true });
	MousePointerRenderer->CreateAnimation({.AnimationName = "UnitSelect", .SpriteName = "Mouse_UnitSelect", .FrameInter = 0.075f, .Loop = true });
	MousePointerCol = CreateComponent<GameEngineCollision>(ColOrder::MousePointer);
	MousePointerCol->GetTransform()->SetWorldScale({ 1,1,1 });
	
	ReleaseStateInit();
	PressStateInit();
	RainOfFireStateInit();
	CallReinforcementStateInit();
	UnitPosStateInit();
	InvalidStateInit();

	MouseFSM.ChangeState("Release");
}

void MousePointer::Update(float _DeltaTime)
{
	MousePos = float4{ 1,-1, 1,1 } *(GameEngineWindow::GetMousePosition() - GameEngineWindow::GetScreenSize().half());
	GetTransform()->SetWorldPosition(MousePos);
	MouseFSM.Update(_DeltaTime);
}

