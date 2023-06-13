#include "PrecompileHeader.h"
#include "BuildAreaButton.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
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
	float4 ParentPos = _ParentArea->GetTransform()->GetWorldPosition();
	ResultAreaButton->GetTransform()->SetWorldPosition({ ParentPos.x, ParentPos.y, 0 });
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
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::TowerButton);
	GetTransform()->SetWorldScale(Scale);
	ReleaseTextureName = "InvisibleTexture.png";
	HoverTextureName = "InvisibleTexture.png";
	PressTextureName = "InvisibleTexture.png";
}

void BuildAreaButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
}
