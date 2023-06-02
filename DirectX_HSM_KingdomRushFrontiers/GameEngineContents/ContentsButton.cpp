#include "PrecompileHeader.h"
#include "ContentsButton.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

ContentsButton::ContentsButton()
{
}

ContentsButton::~ContentsButton()
{
}

std::shared_ptr<ContentsButton> ContentsButton::CreateButton(GameEngineActor* _ParentActor, const std::string_view& _Release, const std::string_view& _Hover, const std::string_view& _Press)
{
	std::shared_ptr<ContentsButton> ResultButton = _ParentActor->GetLevel()->CreateActor<ContentsButton>();
	ResultButton->SetParentActor(_ParentActor);
	ResultButton->SetTextureName(_Release, _Hover, _Press);

	return ResultButton;
}

std::shared_ptr<ContentsButton> ContentsButton::CreateButton(GameEngineLevel* _ParentLevel, const std::string_view& _Release, const std::string_view& _Hover, const std::string_view& _Press)
{
	std::shared_ptr<ContentsButton> ResultButton = _ParentLevel->CreateActor<ContentsButton>();
	ResultButton->SetTextureName(_Release, _Hover, _Press);

	return ResultButton;
}

void ContentsButton::SetParentActor(GameEngineActor* _Actor)
{
	ParentActor = _Actor;
	GetTransform()->SetParent(_Actor->GetTransform());
}

void ContentsButton::SetTextureName(const std::string_view& _Release, const std::string_view& _Hover, const std::string_view& _Press)
{
	ReleaseTextureName = _Release;
	HoverTextureName = _Hover;
	PressTextureName = _Press;
}

void ContentsButton::Start()
{
	Render = CreateComponent<GameEngineUIRenderer>();
}

void ContentsButton::Update(float _Delta)
{
	float4 Scale = Render->GetTransform()->GetWorldScale();
	float4 Pos = Render->GetTransform()->GetWorldPosition();
	
	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetMainCamera();

	// ·£´õ·¯ 
	float4x4 ViewPort = Camera->GetViewPort();
	float4x4 Proj = Camera->GetProjection();
	float4x4 View = Camera->GetView();

	float4 Mouse = GameEngineInput::GetMousePosition();

	Mouse *= ViewPort.InverseReturn();
	Mouse *= Proj.InverseReturn();
	Mouse *= View.InverseReturn();

	CollisionData MouseData;
	MouseData.SPHERE.Center = Mouse.DirectFloat3;
	MouseData.SPHERE.Radius = 0.0f;

	if (true == GameEngineTransform::AABB2DToSpehre2D(Render->GetTransform()->GetCollisionData(), MouseData))
	{
		if (true == GameEngineInput::IsPress("EngineMouseLeft"))
		{
			State = ButtonState::Press;
		}
		else if (true == GameEngineInput::IsUp("EngineMouseLeft"))
		{
			if (nullptr != Click)
			{
				Click();
			}
		}
		else if (true == GameEngineInput::IsFree("EngineMouseLeft"))
		{
			State = ButtonState::Hover;
		}
	}
	else
	{
		State = ButtonState::Release;
	}

	switch (State)
	{
	case ButtonState::Release:
		CurTextureName = ReleaseTextureName;
		break;
	case ButtonState::Press:
		CurTextureName = PressTextureName;
		break;
	case ButtonState::Hover:
		CurTextureName = HoverTextureName;
		break;
	default:
		break;
	}
	Render->SetTexture(CurTextureName);
}


