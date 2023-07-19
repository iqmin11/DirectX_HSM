#include "PrecompileHeader.h"
#include "Title_MousePointer.h"

#include "_101UIRenderer.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore\GameEngineLevel.h>
#include <GameEnginePlatform\GameEngineInput.h>

Title_MousePointer::Title_MousePointer()
{

}

Title_MousePointer::~Title_MousePointer()
{

}

void Title_MousePointer::Start()
{
	MousePointerRenderer = CreateComponent<_101UIRenderer>(UIRenderOrder::MousePoint);
	MousePointerRenderer->GetTransform()->SetWorldScale(RendererScale);
	MousePointerRenderer->CreateAnimation({ .AnimationName = "Release", .SpriteName = "Mouse_Release" });
	MousePointerRenderer->CreateAnimation({ .AnimationName = "Press", .SpriteName = "Mouse_Press" });
	MousePointerCol = CreateComponent<GameEngineCollision>(ColOrder::MousePointer);
	MousePointerCol->GetTransform()->SetWorldScale({ 1,1,1 });

	ReleaseStateInit();
	PressStateInit();

	MouseFSM.ChangeState("Release");

	UICam = GetLevel()->GetCamera(100);
}

void Title_MousePointer::Update(float _DeltaTime)
{
	CalMousePos();
	GetTransform()->SetWorldPosition(MousePos);
	MouseFSM.Update(_DeltaTime);
}

void Title_MousePointer::CalMousePos()
{
	UICamViewPort = UICam->GetViewPort();
	UICamProj = UICam->GetProjection();
	UICamView = UICam->GetView();

	MousePos = GameEngineInput::GetMousePosition();
	MousePos *= UICamViewPort.InverseReturn();
	MousePos *= UICamProj.InverseReturn();
	MousePos *= UICamView.InverseReturn();
}

void Title_MousePointer::ReleaseStateInit()
{
	MouseFSM.CreateState({
		.Name = "Release",
		.Start = [this]()
		{
			MousePointerRenderer->ChangeAnimation("Release");
		},
		.Update = [this](float _DeltaTime)
		{
			if (GameEngineInput::IsDown("EngineMouseLeft"))
			{
				State = MouseState::Press;
				MouseFSM.ChangeState("Press");
				return;
			}
		},
		.End = [this]()
		{
		}
		});
}

void Title_MousePointer::PressStateInit()
{
	MouseFSM.CreateState({
	.Name = "Press",
	.Start = [this]()
	{
		MousePointerRenderer->ChangeAnimation("Press");
	},
	.Update = [this](float _DeltaTime)
	{
		if (GameEngineInput::IsUp("EngineMouseLeft"))
		{
			State = MouseState::Release;
			MouseFSM.ChangeState("Release");
			return;
		}
	},
	.End = [this]()
	{
	}
	});
}


