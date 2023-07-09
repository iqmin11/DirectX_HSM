#include "PrecompileHeader.h"
#include "StageBg.h"

#include "StageEditLevel.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore\GameEngineTexture.h>

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
		StageBgRenderer[i] = CreateComponent<GameEngineSpriteRenderer>(-1000);
		StageBgRenderer[i]->SetTexture("Stage_" + std::to_string(i+1) + ".png");
		StageBgRenderer[i]->GetTransform()->SetWorldScale(TextureScale);
		StageBgRenderer[i]->GetTransform()->SetWorldPosition({0,0,static_cast<float>(RenderOrder::Bg),1});
		StageBgRenderer[i]->Off();
	}

	//StageColmapRender.resize(6);
	//for (size_t i = 0; i < StageColmapRender.size(); i++)
	//{
	//	StageColmapRender[i] = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(RenderOrder::Bg));
	//	StageColmapRender[i]->SetTexture("Stage_" + std::to_string(i + 1) + "_Colmap.png");
	//	StageColmapRender[i]->GetTransform()->SetWorldScale(TextureScale);
	//	StageColmapRender[i]->GetTransform()->SetWorldPosition({ 0,0,999,1 });
	//	StageColmapRender[i]->Off();
	//}

	StageColmap.resize(6);
	for (size_t i = 0; i < StageColmap.size(); i++)
	{
		StageColmap[i] = GameEngineTexture::Find("Stage_" + std::to_string(i + 1) + "_Colmap.png");
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
			//StageColmapRender[i]->Off();
		}
		return;
	}

	for (size_t i = 0; i < StageBgRenderer.size(); i++)
	{
		if (_Stage == i)
		{
			StageBgRenderer[i]->On();
			//StageColmapRender[i]->On();
		}
		else
		{
			StageBgRenderer[i]->Off();
			//StageColmapRender[i]->Off();
		}
	}
}

std::shared_ptr<GameEngineTexture> StageBg::GetColmap(int _Stage)
{
	return StageColmap[_Stage];
}

