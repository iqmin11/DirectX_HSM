#include "PrecompileHeader.h"
#include "StageMap.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>


StageMap::StageMap()
{

}

StageMap::~StageMap()
{

}

void StageMap::Start()
{
	StageMapRenderer = CreateComponent<GameEngineSpriteRenderer>();
	StageMapRenderer->SetPipeLine("2DTexture");
	StageMapRenderer->SetTexture("Stage_1.png");
	StageMapRenderer->GetTransform()->SetWorldScale(StageMapRendererScale);
}

void StageMap::Update(float _DeltaTime)
{
}
