#include "PrecompileHeader.h"
#include "TestActor.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>


TestActor::TestActor()
{

}

TestActor::~TestActor()
{

}

void TestActor::Start()
{
	// 나는 스케일을 1로 고정해 놓는게 좋다.
	//Render0 = CreateComponent<GameEngineRenderer>();
	//Render0->SetPipeLine("2DTexture");
	Render1 = CreateComponent<GameEngineRenderer>();
	Render1->SetPipeLine("2DTexture");
	//Render2 = CreateComponent<GameEngineRenderer>();
	//Render2->SetPipeLine("2DTexture");

	Render1->GetTransform()->DebugOn();

	//Render0->GetTransform()->SetLocalPosition({ -200.0f, 0.0f, 0.0f });
	//Render2->GetTransform()->SetLocalPosition({ 200.0f, 0.0f, 0.0f });
}

void TestActor::Update(float _Delta)
{

}

void TestActor::Render(float _Delta)
{

}
