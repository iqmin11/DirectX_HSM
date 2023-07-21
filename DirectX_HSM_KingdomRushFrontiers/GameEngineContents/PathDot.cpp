#include "PrecompileHeader.h"
#include "PathDot.h"

#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore\GameEngineUIRenderer.h>

PathDot::PathDot()
{

}

PathDot::~PathDot()
{

}

std::shared_ptr<PathDot> PathDot::CreatPathDot(GameEngineActor* _Parent, const std::string_view& _DotColor)
{
	std::shared_ptr<PathDot> LocPathDot(_Parent->GetLevel()->CreateActor<PathDot>());
	LocPathDot->GetTransform()->SetParent(_Parent->GetTransform());
	LocPathDot->DotRenderer->ChangeAnimation(_DotColor);
	return LocPathDot;
}

void PathDot::Start()
{
	DotRenderer = CreateComponent<GameEngineUIRenderer>(WorldMapUIOrder::WorldMapPath);
	DotRenderer->CreateAnimation({.AnimationName = "Red", .SpriteName = "PathDot_Red", .FrameInter = 0.05f, .Loop = false});
	DotRenderer->CreateAnimation({.AnimationName = "Blue", .SpriteName = "PathDot_Blue", .FrameInter = 0.05f, .Loop = false });
	DotRenderer->GetTransform()->SetWorldScale(RenderScale);
	
	DotRenderer->SetAnimationStartEvent("Red", 9, [this]()
		{
			NextActor->On();
		});
	DotRenderer->SetAnimationStartEvent("Blue", 9, [this]()
		{
			NextActor->On();
		});

	Off();
}

void PathDot::Update(float _DeltaTime)
{
}
