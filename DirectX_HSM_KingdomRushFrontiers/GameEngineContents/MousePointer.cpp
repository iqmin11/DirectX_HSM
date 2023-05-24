#include "PrecompileHeader.h"
#include "MousePointer.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

float4 MousePointer::MousePos = float4::Zero;

MousePointer::MousePointer()
{

}

MousePointer::~MousePointer()
{

}

void MousePointer::Start()
{
	MousePointerRenderer = CreateComponent<GameEngineSpriteRenderer>();
	MousePointerRenderer->GetTransform()->SetWorldScale({ 1,1 });
	MousePointerCol = CreateComponent<GameEngineCollision>(ColOrder::MousePointer);
	MousePointerCol->GetTransform()->SetWorldScale({ 1,1 });
}

void MousePointer::Update(float _DeltaTime)
{
	MousePos = float4{ 1,-1, 1,1 } *(GameEngineWindow::GetMousePosition() - GameEngineWindow::GetScreenSize().half());
	GetTransform()->SetWorldPosition(MousePos);
}
