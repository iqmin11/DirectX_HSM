#include "PrecompileHeader.h"
#include "TitleButton_Exit.h"

#include <GameEnginePlatform\GameEngineWindow.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineCore\GameEngineUIRenderer.h>

TitleButton_Exit::TitleButton_Exit()
{

}

TitleButton_Exit::~TitleButton_Exit()
{

}

void TitleButton_Exit::Start()
{
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_1);
	Render->GetTransform()->SetWorldScale({ 74,27,1 });
	SetTextureName("TitleButton_Exit_Release.png", "TitleButton_Exit_Hover.png", "TitleButton_Exit_Press.png");
	SetEvent([]()
		{
			GameEngineWindow::AppOff();
		});
}
