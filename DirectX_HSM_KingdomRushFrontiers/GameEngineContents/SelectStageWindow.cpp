#include "PrecompileHeader.h"
#include "SelectStageWindow.h"

#include <GameEngineCore\GameEngineLevel.h>
#include "StageStartButton.h"
#include "ExitButton.h"
#include "_101UIRenderer.h"
#include "_101UIFontRenderer.h"

SelectStageWindow* SelectStageWindow::MainSelectWindow = nullptr;

SelectStageWindow::SelectStageWindow()
{
	MainSelectWindow = this;
}

SelectStageWindow::~SelectStageWindow()
{

}

void SelectStageWindow::StageWindowOn()
{
	StagePreview->SetTexture("Preview_" + std::to_string(SelectedStage) + ".png");
	LeftTitle->SetText(LeftTitleData[SelectedStage]);
	StageExplain->SetText(StageExplainData[SelectedStage]);
	On();
}

void SelectStageWindow::Start()
{
	WindowBg = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_0);
	WindowBg->SetTexture("SelectStageBook.png");
	WindowBg->GetTransform()->SetWorldScale(BgScale);

	StagePreview = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_1);
	StagePreview->GetTransform()->SetWorldScale(PreviewScale);
	StagePreview->GetTransform()->SetLocalPosition(PreviewLocPos);

	WornOutEffect = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_2);
	WornOutEffect->SetTexture("WornEffect.png");
	WornOutEffect->GetTransform()->SetWorldScale(EffectScale);
	WornOutEffect->GetTransform()->SetLocalPosition(PreviewLocPos);

	AcStageStartButton = StageStartButton::CreateButton(this);
	AcStageStartButton->GetTransform()->SetLocalPosition(StartButtonLocPos);

	ExitWindowButton = ExitButton::CreateButton(this);
	ExitWindowButton->GetTransform()->SetLocalPosition(ExitButtonLocPos);

	SetLeftTitleData();
	SetStageExplainData();

	LeftTitle = CreateComponent<_101UIFontRenderer>(UIRenderOrder::StageUI_2);
	LeftTitle->SetFont("배달의민족 연성 OTF");
	LeftTitle->SetScale(LeftTitleFontScale);
	LeftTitle->SetColor(FontColor);
	LeftTitle->SetFontFlag(FW1_CENTER);
	LeftTitle->GetTransform()->SetWorldPosition(LeftTitleLocPos);

	RightTitle = CreateComponent<_101UIFontRenderer>(UIRenderOrder::StageUI_2);
	RightTitle->SetFont("배달의민족 연성 OTF");
	RightTitle->SetScale(RightTitleFontScale);
	RightTitle->SetColor(FontColor);
	RightTitle->SetFontFlag(FW1_CENTER);
	RightTitle->SetText("캠페인");
	RightTitle->GetTransform()->SetWorldPosition(RightTitleLocPos);

	StageExplain = CreateComponent<_101UIFontRenderer>(UIRenderOrder::StageUI_2);
	StageExplain->SetFont("나눔손글씨 펜 OTF");
	StageExplain->SetScale(StageExplainFontScale);
	StageExplain->SetColor(FontColor);
	StageExplain->SetFontFlag(FW1_LEFT);
	StageExplain->GetTransform()->SetWorldPosition(StageExplainLocPos);

	TitleDeco_Left = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_2);
	TitleDeco_Left->GetTransform()->SetWorldScale({267,16,1});
	TitleDeco_Left->GetTransform()->SetLocalPosition({ -174,200 });
	TitleDeco_Left->SetTexture("TitleDeco_Left.png");

	TitleDeco_Right = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_2);
	TitleDeco_Right->GetTransform()->SetWorldScale({ 186,16,1 });
	TitleDeco_Right->GetTransform()->SetLocalPosition({ 226,212 });
	TitleDeco_Right->SetTexture("TitleDeco_Right.png");

	Off();
}

void SelectStageWindow::SetLeftTitleData()
{
	LeftTitleData.reserve(6);
	LeftTitleData.push_back("해머홀드");
	LeftTitleData.push_back("모래독수리 마을");
	LeftTitleData.push_back("새페 오아시스");
	LeftTitleData.push_back("절망의 사막");
	LeftTitleData.push_back("해적 소굴");
	LeftTitleData.push_back("나제루의 관문");
}

void SelectStageWindow::SetStageExplainData()
{
	StageExplainData.reserve(6);
	StageExplainData.push_back("리니리아의 수호자여!\n악의 세력이 고대 요새 해머홀드를\n공격하고 있어 당신의 도움이 다시\n한번 필요합니다! 이곳은 한동안 평화로웠지만,\n이제 다시금 사막 유랑 부족에게 포위되고\n말았습니다! 왕국의 군대를 지휘해 우리를\n지켜주십시오!");
	StageExplainData.push_back("마도사 말라가르가 혼란을 틈타\n해머홀ㄹ드에서 강력한 세월의 망치를\n훔쳐냈습니다!\n요새 동쪽의 전초지기에서 도망치는 말라가르를\n포착했으며, 지금 그들은 말라가르의 병력과\n싸우며 탈출을 지연시키고 있습니다. 서둘러\n그들을 지원해야 합니다, 사령관님!");
	StageExplainData.push_back("당신의 지휘 아래 모인 아군은 아즈세어\n사막 너머까지 마도사 말라가르를\n추격했습니다!\n그리고 이 황무지에서 드물게 풀이 돋은 곳 중\n하나인 새페 오아시스에 이르렀습니다. 유목민\n부족은 침입자에게 호의적이지 않으므로, 사막의\n위험한 원주민 부족인 두스카르를 자극해서는 안\n됩니다!");
	StageExplainData.push_back("새페 오아시스의 공격은 주의를 돌리기\n위함이었을 뿐이며, 마도사\n말라가르는 해적 소굴을 향해\n빠져나갔습니다. 우리는 어쩔 수 없이\n위험천만한 절망의 사막을 건너야만 합니다.\n사막을 우회할 시간은 없습니다. 발 밑에 흐르는\n모래를 조심하십시오. 수많은 오련한 탑험가들을\n집어삼킨 정체불명의 괴물들이 모래 속에\n도사리고 있기 때문입니다!");
	StageExplainData.push_back("험악하기 짝이 없는 해적 소굴에\n도착했습니다!\n최악의 무법자와 악랄한 해적들이\n모인 곳이지만, 수정의 바다를 항해할 최고의\n선원들을 찾을 수 있는 곳 또한 바로 여기입니다.\n해적 몇 명에게 돈을 쥐어주자, 그들은 마도사\n말라가르가 배를 타고 나제루의 관문으로\n떠났다는 정보를 알려주었습니다. 하지만 적의\n함대가 다가오고 있으므로 선원 고용은 잠시\n접어둬야 할 것 같습니다. 전투 준비!");
	StageExplainData.push_back("우리는 잊혀진 땅으로 이어진 길을\n막아선 전설적인 장소, 나제루의\n관문에 도착했습니다. 이곳에는\n사악한 기운이 진동하며, 병사들은 불안에 떨고\n있습니다. 방랑하는 적들은 지금껏 상대해\n왔기에, 그들 때문에 불안해하는 것은\n아닙니다... 다행히 대마법사 길드께서\n관문을 열도록 지원군을 보냈으며, 전투가\n시작되면 그들이 함께 싸워줄 것입니다.");
}
