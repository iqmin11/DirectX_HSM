#include "PrecompileHeader.h"
#include "WorldMapBg.h"

#include <GameEngineCore\GameEngineUIRenderer.h>

WorldMapBg::WorldMapBg()
{

}

WorldMapBg::~WorldMapBg()
{

}

void WorldMapBg::Start()
{
	BgRenderer = CreateComponent<GameEngineUIRenderer>(WorldMapUIOrder::WorldMapBg);
	BgRenderer->GetTransform()->SetWorldScale(Scale);
	BgRenderer->SetTexture("WorldMapBg.png");

	EdgeFade = CreateComponent<GameEngineUIRenderer>(WorldMapUIOrder::WorldMapBg);
	EdgeFade->GetTransform()->SetWorldScale(EdgeFadeScale);
	EdgeFade->SetTexture("WorldMapFade.png");
}
