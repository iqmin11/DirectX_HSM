#include "PrecompileHeader.h"
#include "FlagButton.h"

#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore\GameEngineUIRenderer.h>
#include "WorldMapFlag.h"
#include "WorldMapLevel.h"

FlagButton::FlagButton()
{

}

FlagButton::~FlagButton()
{

}

std::shared_ptr<FlagButton> FlagButton::CreateButton(WorldMapFlag* _Parent, std::function<void()> _Click)
{
	std::shared_ptr<FlagButton> LocButton(_Parent->GetLevel()->CreateActor<FlagButton>());
	LocButton->SetParentActor(_Parent);
	LocButton->GetTransform()->SetParent(_Parent->GetTransform());
	LocButton->GetTransform()->SetLocalPosition({0,29});
	LocButton->SetEvent(_Click);
	return LocButton;
}

void FlagButton::Start()
{
	Render = CreateComponent<GameEngineUIRenderer>();
	Render->SetTexture("InvisibleTexture.png");
	GetTransform()->SetWorldScale(ButtonScale);
	SetTextureName("InvisibleTexture.png", "InvisibleTexture.png", "InvisibleTexture.png");
	HoverSound = "Sound_GUIMouseOverTowerIcon.ogg";

}

void FlagButton::Update(float _DeltaTime)
{
	if (GetParentActor()->DynamicThis<WorldMapFlag>()->GetState() == FlagState::Update)
	{
		if (!WorldMapLevel::IsPause)
		{
			ContentsButton::Update(_DeltaTime);
		}
		else
		{
			State = ButtonState::Release;
		}
	}
}
