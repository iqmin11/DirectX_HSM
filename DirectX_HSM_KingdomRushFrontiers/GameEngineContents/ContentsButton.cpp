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

std::shared_ptr<ContentsButton> ContentsButton::IsFocusPtr = nullptr;

std::shared_ptr<ContentsButton> ContentsButton::CreateButton(GameEngineActor* _ParentActor, const std::string_view& _Release, const std::string_view& _Hover, const std::string_view& _Press)
{
	if (_ParentActor == nullptr)
	{
		MsgAssert("버튼을 만들 부모액터가 nullptr입니다.")
	}
	std::weak_ptr<ContentsButton> ResultButton(_ParentActor->GetLevel()->CreateActor<ContentsButton>());
	ResultButton.lock()->SetParentActor(_ParentActor);
	ResultButton.lock()->SetTextureName(_Release, _Hover, _Press);

	return ResultButton.lock();
}

std::shared_ptr<ContentsButton> ContentsButton::CreateButton(GameEngineLevel* _ParentLevel, const std::string_view& _Release, const std::string_view& _Hover, const std::string_view& _Press)
{
	if (_ParentLevel == nullptr)
	{
		MsgAssert("버튼을 만들 부모레벨이 nullptr입니다.")
	}

	std::weak_ptr<ContentsButton> ResultButton(_ParentLevel->CreateActor<ContentsButton>());
	ResultButton.lock()->SetTextureName(_Release, _Hover, _Press);

	return ResultButton.lock();
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

UIRenderOrder ContentsButton::GetRenderOrder()
{
	return static_cast<UIRenderOrder>(Render->GetOrder());
}


void ContentsButton::Start()
{
	ButtonCollision = CreateComponent<GameEngineCollision>(ColOrder::Button);
}

void ContentsButton::Update(float _Delta)
{
	if (ButtonCollision->GetTransform()->GetWorldScale() != Render->GetTransform()->GetWorldScale())
	{
		ButtonCollision->GetTransform()->SetWorldScale(Render->GetTransform()->GetWorldScale());
	}

	float4 Scale = Render->GetTransform()->GetWorldScale();
	float4 Pos = Render->GetTransform()->GetWorldPosition();
	
	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);

	// 랜더러 
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
			}
		}
		else if (true == GameEngineInput::IsFree("EngineMouseLeft"))
		{
			if (State != ButtonState::Hover)
			{
				State = ButtonState::Hover;
				PlayButtonSound(HoverSound);
			}
		}
	}
	else
	{
		if (State != ButtonState::Release)
		{
			State = ButtonState::Release;
		}
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

void ContentsButton::PlayButtonSound(const std::string_view& _Sound)
{
	if (_Sound == "")
	{
		return;
	}

	ButtonSound = GameEngineSound::Play(_Sound);
	ButtonSound.SetVolume(0.2f);
}



