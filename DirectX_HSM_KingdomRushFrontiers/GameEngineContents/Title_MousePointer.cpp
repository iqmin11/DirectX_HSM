#include "PrecompileHeader.h"
#include "Title_MousePointer.h"

#include "_101UIRenderer.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore\GameEngineLevel.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include "ContentsButton.h"
#include "WorldMapLevel.h"

Title_MousePointer::Title_MousePointer()
{

}

Title_MousePointer::~Title_MousePointer()
{

}

void Title_MousePointer::ButtonClick()
{
	std::vector<std::shared_ptr<GameEngineCollision>> HoverButtonCols;
	if (MousePointerCol->CollisionAll(ColOrder::Button, HoverButtonCols, ColType::SPHERE2D, ColType::AABBBOX2D))
	{
		std::vector<std::shared_ptr<ContentsButton>> HoverButtons;
		HoverButtons.resize(HoverButtonCols.size());

		for (size_t i = 0; i < HoverButtons.size(); i++)
		{
			HoverButtons[i] = HoverButtonCols[i]->GetActor()->DynamicThis<ContentsButton>();
		}

		std::sort(HoverButtons.begin(), HoverButtons.end(),
			[](std::shared_ptr<ContentsButton>& _Left, std::shared_ptr<ContentsButton>& _Right)
			{
				return _Left->GetRenderOrder() > _Right->GetRenderOrder();
			});

		HoverButtons[0]->FocusOn();

		if (GameEngineInput::IsUp("EngineMouseLeft"))
		{
			if (WorldMapLevel::IsPause)
			{
				if (HoverButtons[0]->GetOrder() == 1)
				{
					HoverButtons[0]->GetEvent()();
				}
				else
				{
					return;
				}
			}
			else
			{
				HoverButtons[0]->GetEvent()();
			}

		}
	}
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
	ButtonClick();
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


