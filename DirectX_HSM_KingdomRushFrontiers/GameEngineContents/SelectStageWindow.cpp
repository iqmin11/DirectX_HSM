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
	LeftTitle->SetFont("����ǹ��� ���� OTF");
	LeftTitle->SetScale(LeftTitleFontScale);
	LeftTitle->SetColor(FontColor);
	LeftTitle->SetFontFlag(FW1_CENTER);
	LeftTitle->GetTransform()->SetWorldPosition(LeftTitleLocPos);

	RightTitle = CreateComponent<_101UIFontRenderer>(UIRenderOrder::StageUI_2);
	RightTitle->SetFont("����ǹ��� ���� OTF");
	RightTitle->SetScale(RightTitleFontScale);
	RightTitle->SetColor(FontColor);
	RightTitle->SetFontFlag(FW1_CENTER);
	RightTitle->SetText("ķ����");
	RightTitle->GetTransform()->SetWorldPosition(RightTitleLocPos);

	StageExplain = CreateComponent<_101UIFontRenderer>(UIRenderOrder::StageUI_2);
	StageExplain->SetFont("�����ձ۾� �� OTF");
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
	LeftTitleData.push_back("�ظ�Ȧ��");
	LeftTitleData.push_back("�𷡵����� ����");
	LeftTitleData.push_back("���� ���ƽý�");
	LeftTitleData.push_back("������ �縷");
	LeftTitleData.push_back("���� �ұ�");
	LeftTitleData.push_back("�������� ����");
}

void SelectStageWindow::SetStageExplainData()
{
	StageExplainData.reserve(6);
	StageExplainData.push_back("���ϸ����� ��ȣ�ڿ�!\n���� ������ ��� ��� �ظ�Ȧ�带\n�����ϰ� �־� ����� ������ �ٽ�\n�ѹ� �ʿ��մϴ�! �̰��� �ѵ��� ��ȭ�ο�����,\n���� �ٽñ� �縷 ���� �������� �����ǰ�\n���ҽ��ϴ�! �ձ��� ���븦 ������ �츮��\n�����ֽʽÿ�!");
	StageExplainData.push_back("������ ���󰡸��� ȥ���� ƴŸ\n�ظ�Ȧ���忡�� ������ ������ ��ġ��\n���ĳ½��ϴ�!\n��� ������ �������⿡�� ����ġ�� ���󰡸���\n����������, ���� �׵��� ���󰡸��� ���°�\n�ο�� Ż���� ������Ű�� �ֽ��ϴ�. ���ѷ�\n�׵��� �����ؾ� �մϴ�, ��ɰ���!");
	StageExplainData.push_back("����� ���� �Ʒ� ���� �Ʊ��� �����\n�縷 �ʸӱ��� ������ ���󰡸���\n�߰��߽��ϴ�!\n�׸��� �� Ȳ�������� �幰�� Ǯ�� ���� �� ��\n�ϳ��� ���� ���ƽý��� �̸������ϴ�. �����\n������ ħ���ڿ��� ȣ�������� �����Ƿ�, �縷��\n������ ���ֹ� ������ �ν�ī���� �ڱ��ؼ��� ��\n�˴ϴ�!");
	StageExplainData.push_back("���� ���ƽý��� ������ ���Ǹ� ������\n�����̾��� ���̸�, ������\n���󰡸��� ���� �ұ��� ����\n�����������ϴ�. �츮�� ��¿ �� ����\n����õ���� ������ �縷�� �ǳʾ߸� �մϴ�.\n�縷�� ��ȸ�� �ð��� �����ϴ�. �� �ؿ� �帣��\n�𷡸� �����Ͻʽÿ�. ������ ������ ž�谡����\n�����Ų ��ü�Ҹ��� �������� �� �ӿ�\n���縮�� �ֱ� �����Դϴ�!");
	StageExplainData.push_back("����ϱ� ¦�� ���� ���� �ұ���\n�����߽��ϴ�!\n�־��� �����ڿ� �Ƕ��� ��������\n���� ��������, ������ �ٴٸ� ������ �ְ���\n�������� ã�� �� �ִ� �� ���� �ٷ� �����Դϴ�.\n���� �� ���� ���� �������, �׵��� ������\n���󰡸��� �踦 Ÿ�� �������� ��������\n�����ٴ� ������ �˷��־����ϴ�. ������ ����\n�Դ밡 �ٰ����� �����Ƿ� ���� ����� ���\n����־� �� �� �����ϴ�. ���� �غ�!");
	StageExplainData.push_back("�츮�� ������ ������ �̾��� ����\n���Ƽ� �������� ���, ��������\n������ �����߽��ϴ�. �̰�����\n����� ����� �����ϸ�, ������� �Ҿȿ� ����\n�ֽ��ϴ�. ����ϴ� ������ ���ݲ� �����\n�Ա⿡, �׵� ������ �Ҿ����ϴ� ����\n�ƴմϴ�... ������ �븶���� ��岲��\n������ ������ �������� ��������, ������\n���۵Ǹ� �׵��� �Բ� �ο��� ���Դϴ�.");
}
