#include "PrecompileHeader.h"
#include "MousePointer.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

MousePointer::MousePointer()
{

}

MousePointer::~MousePointer()
{

}

void MousePointer::Start()
{
	MousePointerRenderer = CreateComponent<GameEngineSpriteRenderer>();
	MousePointerRenderer->GetTransform()->SetWorldScale({ 10,10 });
	MousePointerCol = CreateComponent<GameEngineCollision>(ColOrder::MousePointer);
	MousePointerCol->GetTransform()->SetWorldScale({ 10,10 });
}

void MousePointer::Update(float _DeltaTime)
{
	MousePos = float4{ 1,-1,1,1 } *(GameEngineWindow::GetMousePosition() - GameEngineWindow::GetScreenSize().half());
	GetTransform()->SetWorldPosition(MousePos);
}
