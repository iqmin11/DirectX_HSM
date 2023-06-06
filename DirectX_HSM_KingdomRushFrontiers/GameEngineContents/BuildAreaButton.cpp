#include "PrecompileHeader.h"
#include "BuildAreaButton.h"

#include <GameEngineCore/GameEngineLevel.h>
#include "BuildArea.h"
#include "BuildTowerUI.h"

BuildAreaButton::BuildAreaButton()
{

}

BuildAreaButton::~BuildAreaButton()
{

}

std::shared_ptr<BuildAreaButton> BuildAreaButton::CreateButton(BuildArea* _ParentArea)
{
	std::shared_ptr<BuildAreaButton> ResultAreaButton = _ParentArea->GetLevel()->CreateActor<BuildAreaButton>();
	ResultAreaButton->GetTransform()->SetWorldPosition(_ParentArea ->GetTransform()->GetWorldPosition());
	ResultAreaButton->SetParentActor(_ParentArea);
	ResultAreaButton->SetEvent(
		[_ParentArea]()
		{
			_ParentArea->BuildUI->OnUI();
			//BuildTowerUI
		});
	return ResultAreaButton;
}

void BuildAreaButton::Start()
{
	ContentsButton::Start();
	GetTransform()->SetWorldScale(Scale);
	ReleaseTextureName = "InvisibleTexture.png";
	HoverTextureName = "InvisibleTexture.png";
	PressTextureName = "InvisibleTexture.png";
}

void BuildAreaButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
}
