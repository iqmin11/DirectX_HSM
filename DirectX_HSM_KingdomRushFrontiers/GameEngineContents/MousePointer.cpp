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
#include "ContentsButton.h"

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

void MousePointer::ButtonClick()
{
	std::vector<std::shared_ptr<GameEngineCollision>> HoverButtonCols;
	if (MousePointerCol->CollisionAll(ColOrder::Button, HoverButtonCols, ColType::AABBBOX2D, ColType::AABBBOX2D))
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
			if (true == GetLevel()->DynamicThis<PlayStageLevel>()->IsPause)
			{
				if (HoverButtons[0]->GetOrder() == 1)
				{
					HoverButtons[0]->GetEvent()();
					HoverButtons[0]->PlayButtonSound(HoverButtons[0]->UpSound);
				}
				else
				{
					return;
				}
			}
			else
			{
				HoverButtons[0]->GetEvent()();
				HoverButtons[0]->PlayButtonSound(HoverButtons[0]->UpSound);
			}
			
		}
	}
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

	UICam = GetLevel()->GetCamera(100);
}

void MousePointer::Update(float _DeltaTime)
{
	CalMousePos();
	GetTransform()->SetWorldPosition(MousePos);
	ButtonClick();
	MouseFSM.Update(_DeltaTime);
}

void MousePointer::CalMousePos()
{
	UICamViewPort = UICam->GetViewPort();
	UICamProj = UICam->GetProjection();
	UICamView = UICam->GetView();

	MousePos = GameEngineInput::GetMousePosition();
	MousePos *= UICamViewPort.InverseReturn();
	MousePos *= UICamProj.InverseReturn();
	MousePos *= UICamView.InverseReturn();
}


