#include "PrecompileHeader.h"
#include "StageBg.h"

#include "StageEditLevel.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

StageBg::StageBg()
{

}

StageBg::~StageBg()
{

}

void StageBg::Start()
{
	GetTransform()->SetWorldPosition(ActorPos);
	StageBgRenderer.resize(6);
	for (size_t i = 0; i < StageBgRenderer.size(); i++)
	{
		StageBgRenderer[i] = CreateComponent<GameEngineSpriteRenderer>();
		StageBgRenderer[i]->SetTexture("Stage_" + std::to_string(i+1) + ".png");
		StageBgRenderer[i]->GetTransform()->SetWorldScale(TextureScale);
		StageBgRenderer[i]->Off();
	}
}

void StageBg::Update(float _DeltaTime)
{
}

void StageBg::RenderStage(int _Stage /*= -1*/)
{
	if (_Stage == -1)
	{
		for (size_t i = 0; i < StageBgRenderer.size(); i++)
		{
			StageBgRenderer[i]->Off();
		}
		return;
	}

	for (size_t i = 0; i < StageBgRenderer.size(); i++)
	{
		if (_Stage == i)
		{
			StageBgRenderer[i]->On();
		}
		else
		{
			StageBgRenderer[i]->Off();
		}
	}
}

