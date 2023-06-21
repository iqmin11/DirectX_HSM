#include "PrecompileHeader.h"
#include "MousePointer.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "PlayStageLevel.h"
#include "StageBg.h"

float4 MousePointer::MousePos = float4::Zero;
MousePointer* MousePointer::MainMouse = nullptr;

MousePointer::MousePointer()
{
	MainMouse = this;
}

MousePointer::~MousePointer()
{

}

const float4 MousePointer::GetMouseWinPosRef()
{
	return GameEngineWindow::GetMousePosition();
}

const float4 MousePointer::GetMouseColmapPos()
{
	return GameEngineWindow::GetMousePosition() + float4{-200, 50};
}

bool MousePointer::IsThereMouseOntheColMap()
{
	float4 MousePos = MousePointer::GetMouseColmapPos();
	std::weak_ptr LocalLevel(GetLevel()->DynamicThis<PlayStageLevel>());
	GameEnginePixelColor Pixel = LocalLevel.lock()->GetStageBg()->GetColmap(LocalLevel.lock()->GetCurStage())->GetPixel(MousePos.ix(), MousePos.iy());
	return GameEnginePixelColor(0, 0, 0, UCHAR_MAX) == Pixel;
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
