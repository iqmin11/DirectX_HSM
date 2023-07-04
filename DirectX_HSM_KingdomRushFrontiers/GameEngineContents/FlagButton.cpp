#include "PrecompileHeader.h"
#include "FlagButton.h"

#include <GameEngineCore\GameEngineLevel.h>
#include "WorldMapFlag.h"

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
	LocButton->SetEvent(_Click);
	return LocButton;
}

void FlagButton::Start()
{
	GetTransform()->SetWorldScale(ButtonScale);
	SetTextureName("InvisibleTexture.png", "InvisibleTexture.png", "InvisibleTexture.png");
}

void FlagButton::Update(float _DeltaTime)
{
	if (GetParentActor()->DynamicThis<WorldMapFlag>()->GetState() == FlagState::Update)
	{
		ContentsButton::Update(_DeltaTime);
	}
}
