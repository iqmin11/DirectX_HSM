#include "PrecompileHeader.h"
#include "StageMap.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>

StageMap* StageMap::MainStageMap = nullptr;

StageMap::StageMap()
{
	MainStageMap = this;
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

	//RedDot = CreateComponent<GameEngineRenderer>();
	//RedDot->SetPipeLine("2DTexture");
	//RedDot->GetTransform()->SetWorldScale({10,10});
}

void StageMap::Update(float _DeltaTime)
{

}

void StageMap::Render(float _DeltaTime)
{
	if (GameEngineInput::IsUp("LeftClick") && PathSetMode)
	{
		float4 MousePosition = float4{ 1,-1,1,1 } * (GameEngineWindow::GetMousePosition() - GameEngineWindow::GetScreenSize().half());
		std::shared_ptr<GameEngineRenderer> Test = CreateComponent<GameEngineRenderer>();
		Test->SetPipeLine("2DTexture");
		Test->GetTransform()->SetWorldScale({ 10,10 });
		Test->GetTransform()->SetWorldPosition(MousePosition);
		TestPath.emplace_back(MousePosition);
	}

	if (GameEngineInput::IsDown("F1"))
	{
		PathSetMode = !PathSetMode;
	}

	//if (true)
	//{
	//
	//}
}
