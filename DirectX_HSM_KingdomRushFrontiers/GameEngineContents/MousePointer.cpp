#include "PrecompileHeader.h"
#include "MousePointer.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "PlayStageLevel.h"
#include "StageBg.h"

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
	return GameEnginePixelColor(0, 0, 0, UCHAR_MAX) == Pixel;
}

void MousePointer::Start()
{
	MousePointerRenderer = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::MousePoint);
	MousePointerRenderer->GetTransform()->SetWorldScale(RendererScale);
	MousePointerRenderer->CreateAnimation({.AnimationName = "Release", .SpriteName = "Mouse_Release"});
	MousePointerRenderer->CreateAnimation({.AnimationName = "Press", .SpriteName = "Mouse_Press"});
	MousePointerRenderer->CreateAnimation({.AnimationName = "RainOfFire", .SpriteName = "Mouse_RainOfFire", .Loop = true});
	MousePointerRenderer->CreateAnimation({.AnimationName = "CallReinforcement", .SpriteName = "Mouse_CallReinforcement", .Loop = true });
	MousePointerRenderer->CreateAnimation({.AnimationName = "UnitSelect", .SpriteName = "Mouse_UnitSelect", .Loop = true });

	MousePointerCol = CreateComponent<GameEngineCollision>(ColOrder::MousePointer);
	MousePointerCol->GetTransform()->SetWorldScale({ 1,1,1 });
	
	ReleaseStateInit();
	PressStateInit();
	RainOfFireStateInit();
	CallReinforcementStateInit();
	SelectUnitStateInit();
	InvalidStateInit();

	MouseFSM.ChangeState("Release");
}

void MousePointer::Update(float _DeltaTime)
{
	MousePos = float4{ 1,-1, 1,1 } *(GameEngineWindow::GetMousePosition() - GameEngineWindow::GetScreenSize().half());
	GetTransform()->SetWorldPosition(MousePos);
	MouseFSM.Update(_DeltaTime);
}

void MousePointer::ReleaseStateInit()
{
	MouseFSM.CreateState({
		.Name = "Release"
		,.Start = [this]()
		{
			MousePointerRenderer->ChangeAnimation("Release");
		}
		,.Update = [this](float _DeltaTime)
		{
			if (GameEngineInput::IsDown("EngineMouseLeft"))
			{
				State = MouseState::Press;
				MouseFSM.ChangeState("Press");
			}
		}
		,.End = [this]()
		{

		}
		});
}

void MousePointer::PressStateInit()
{
	MouseFSM.CreateState({
	.Name = "Press"
	,.Start = [this]()
	{
		MousePointerRenderer->ChangeAnimation("Press");
	}
	,.Update = [this](float _DeltaTime)
	{
		if (GameEngineInput::IsUp("EngineMouseLeft"))
		{
			State = MouseState::Release;
			MouseFSM.ChangeState("Release");
		}
	}
	,.End = [this]()
	{

	}
		});
}

void MousePointer::RainOfFireStateInit()
{
	MouseFSM.CreateState({
	.Name = "RainOfFire"
	,.Start = [this]()
	{

	}
	,.Update = [this](float _DeltaTime)
	{

	}
	,.End = [this]()
	{

	}
		});
}

void MousePointer::CallReinforcementStateInit()
{
	MouseFSM.CreateState({
	.Name = "CallReinforcement"
	,.Start = [this]()
	{

	}
	,.Update = [this](float _DeltaTime)
	{

	}
	,.End = [this]()
	{

	}
		});
}

void MousePointer::SelectUnitStateInit()
{
	MouseFSM.CreateState({
	.Name = "SelectUnit"
	,.Start = [this]()
	{

	}
	,.Update = [this](float _DeltaTime)
	{

	}
	,.End = [this]()
	{

	}
		});
}

void MousePointer::InvalidStateInit()
{
	MouseFSM.CreateState({
	.Name = "Invalid"
	,.Start = [this]()
	{

	}
	,.Update = [this](float _DeltaTime)
	{

	}
	,.End = [this]()
	{

	}
		});
}
