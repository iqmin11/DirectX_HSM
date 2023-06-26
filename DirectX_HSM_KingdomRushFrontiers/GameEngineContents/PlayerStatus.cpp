#include "PrecompileHeader.h"
#include "PlayerStatus.h"

#include <GameEngineCore\GameEngineUIRenderer.h>
#include "PlayStageLevel.h"
#include "PlayManager.h"
#include "UIFontRenderer.h"

PlayerStatus::PlayerStatus()
{

}

PlayerStatus::~PlayerStatus()
{

}

void PlayerStatus::Start()
{
	ParentLevel = dynamic_cast<PlayStageLevel*>(GetLevel());

	StatusBg = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_0);
	StatusBg->SetTexture("DisplayPlayerState.png");
	StatusBg->GetTransform()->SetWorldScale(StatusBgScale);

	LifePtr = &PlayManager::MainPlayer->Life;
	LifeRender = CreateComponent<UIFontRenderer>(UIRenderOrder::StageUI_1);
	LifeRender->SetFont("³ª´®¼Õ±Û¾¾ Ææ OTF");
	LifeRender->SetColor(float4::White);
	LifeRender->SetScale(FontScale);
	LifeRender->GetTransform()->SetLocalPosition(LifeLocPos);

	GoldPtr = &PlayManager::MainPlayer->Gold;
	GoldRender = CreateComponent<UIFontRenderer>(UIRenderOrder::StageUI_1);
	GoldRender->SetFont("³ª´®¼Õ±Û¾¾ Ææ OTF");
	GoldRender->SetColor(float4::White);
	GoldRender->SetScale(FontScale);
	GoldRender->GetTransform()->SetLocalPosition(GoldLocPos);

	CurWave = ParentLevel->GetNextWavePtr();
	MaxWave = ParentLevel->GetMaxWavePtr();
	WaveRender = CreateComponent<UIFontRenderer>(UIRenderOrder::StageUI_1);
	WaveRender->SetFont("³ª´®¼Õ±Û¾¾ Ææ OTF");
	WaveRender->SetColor(float4::White);
	WaveRender->SetScale(FontScale);
	WaveRender->GetTransform()->SetLocalPosition(WaveLocPos);
}

void PlayerStatus::Update(float _DeltaTime)
{
	LifeRender->SetText(std::to_string(*LifePtr));
	GoldRender->SetText(std::to_string(*GoldPtr));
	WaveRender->SetText("°ø°Ý " + std::to_string(*CurWave) + "/" + std::to_string(*MaxWave));
}
