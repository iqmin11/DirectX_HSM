#include "PrecompileHeader.h"
#include "ExitButton.h"

#include <GameEngineCore\GameEngineLevel.h>
#include "_101UIRenderer.h"
#include "WorldMapLevel.h"

ExitButton::ExitButton()
{

}

ExitButton::~ExitButton()
{

}

std::shared_ptr<ExitButton> ExitButton::CreateButton(GameEngineActor* _Parent)
{
	std::weak_ptr<ExitButton> LocButton(_Parent->GetLevel()->CreateActor<ExitButton>());
	LocButton.lock()->GetTransform()->SetParent(_Parent->GetTransform());
	LocButton.lock()->SetParentActor(_Parent);
	LocButton.lock()->SetEvent([LocButton]()
		{
			LocButton.lock()->GetParentActor()->Off();
			WorldMapLevel::IsPause = false;
			LocButton.lock()->PlayButtonSound(LocButton.lock()->UpSound);
		});
	return LocButton.lock();
}

void ExitButton::Start()
{
	Render = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_2);
	Render->GetTransform()->SetWorldScale(ButtonScale);
	SetTextureName("ExitButton_Release.png", "ExitButton_Hover.png", "ExitButton_Hover.png");
}
