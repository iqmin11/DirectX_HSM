#include "PrecompileHeader.h"
#include "StageStartButton.h"

#include <GameEngineCore\GameEngineLevel.h>
#include "_101UIRenderer.h"

StageStartButton::StageStartButton()
{

}

StageStartButton::~StageStartButton()
{

}

std::shared_ptr<StageStartButton> StageStartButton::CreateButton(GameEngineActor* _Parent)
{
	std::shared_ptr<StageStartButton> LocButton(_Parent->GetLevel()->CreateActor<StageStartButton>());
	LocButton->GetTransform()->SetParent(_Parent->GetTransform());
	LocButton->SetParentActor(_Parent);
	LocButton->SetEvent([]()
		{

		});
	return LocButton;
}

void StageStartButton::Start()
{
	Render = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_1);
	Render->GetTransform()->SetWorldScale(ButtonScale);
	SetTextureName("SelectButton_Release.png","SelectButton_Hover.png","SelectButton_Hover.png");
}
