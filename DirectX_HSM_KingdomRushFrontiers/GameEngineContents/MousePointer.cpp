#include "PrecompileHeader.h"
#include "MousePointer.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "PlayStageLevel.h"
#include "PlayManager.h"
#include "StageBg.h"
#include "Melee_Tower.h"
#include "_101UIRenderer.h"

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
	return GameEngineWindow::GetMousePosition();
}

bool MousePointer::IsThereMouseOntheColMap()
{
	float4 MousePos = MousePointer::GetMouseColmapPos();
	std::weak_ptr LocalLevel(GetLevel()->DynamicThis<PlayStageLevel>());
	int CurStage = LocalLevel.lock()->GetCurStage();
	GameEnginePixelColor Pixel = LocalLevel.lock()->GetStageBg()->GetColmap(CurStage)->GetPixel(MousePos.ix(), MousePos.iy());
	return GameEnginePixelColor(0, 0, 0, UCHAR_MAX) == Pixel;
}

void MousePointer::Start()
{
	MousePointerRenderer = CreateComponent<_101UIRenderer>(UIRenderOrder::MousePoint);
	MousePointerRenderer->GetTransform()->SetWorldScale(RendererScale);
	MousePointerRenderer->CreateAnimation({.AnimationName = "Release", .SpriteName = "Mouse_Release"});
	MousePointerRenderer->CreateAnimation({.AnimationName = "Press", .SpriteName = "Mouse_Press"});
	MousePointerRenderer->CreateAnimation({.AnimationName = "RainOfFire", .SpriteName = "Mouse_RainOfFire", .FrameInter = 0.025f, .Loop = true});
	MousePointerRenderer->CreateAnimation({.AnimationName = "CallReinforcement", .SpriteName = "Mouse_CallReinforcement", .FrameInter = 0.025f, .Loop = true });
	MousePointerRenderer->CreateAnimation({.AnimationName = "UnitSelect", .SpriteName = "Mouse_UnitSelect", .FrameInter = 0.025f, .Loop = true });
	MousePointerCol = CreateComponent<GameEngineCollision>(ColOrder::MousePointer);
	MousePointerCol->GetTransform()->SetWorldScale({ 1,1,1 });
	
	ReleaseStateInit();
	PressStateInit();
	RainOfFireStateInit();
	CallReinforcementStateInit();
	HeroStateInit();
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

