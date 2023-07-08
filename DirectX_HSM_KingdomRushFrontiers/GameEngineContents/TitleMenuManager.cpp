#include "PrecompileHeader.h"
#include "TitleMenuManager.h"

#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore\GameEngineUIRenderer.h>
#include "TitleButton_Start.h"
#include "TitleButton_Exit.h"

TitleMenuManager::TitleMenuManager()
{

}

TitleMenuManager::~TitleMenuManager()
{

}

void TitleMenuManager::Start()
{
	ButtonBg = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_0);
	ButtonBg->SetTexture("TitleButtonBg.png");
	ButtonBg->GetTransform()->SetWorldScale({422,432,1});

	StartButton = GetLevel()->CreateActor<TitleButton_Start>();
	StartButton->SetParentActor(this);
	StartButton->GetTransform()->SetLocalPosition({40,120});

	OptionButton = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_1);
	OptionButton->GetTransform()->SetWorldScale({74,43,1});
	OptionButton->GetTransform()->SetLocalPosition({45,35});
	OptionButton->SetTexture("TitleButton_Option_Press.png");

	ProducerButton = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_1);
	ProducerButton->GetTransform()->SetWorldScale({ 79,29,1 });
	ProducerButton->GetTransform()->SetLocalPosition({ 55, -25 });
	ProducerButton->SetTexture("TitleButton_Producer_Press.png");

	ExitButton = GetLevel()->CreateActor<TitleButton_Exit>();
	ExitButton->SetParentActor(this);
	ExitButton->GetTransform()->SetLocalPosition({ 38,-85 });
}
