#include "PrecompileHeader.h"
#include "TitleButton_Start.h"

#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineCore\GameEngineUIRenderer.h>

TitleButton_Start::TitleButton_Start()
{

}

TitleButton_Start::~TitleButton_Start()
{

}

void TitleButton_Start::Start()
{
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_1);
	Render->GetTransform()->SetWorldScale({160,77,1});
	SetTextureName("TitleButton_Start_Release.png", "TitleButton_Start_Hover.png", "TitleButton_Start_Press.png");
	SetEvent([]()
		{
			GameEngineCore::ChangeLevel("WorldMapLevel");
		});
}
