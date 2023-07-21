#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"
#include <GameEnginePlatform\GameEngineSound.h>

class PathDot : public GameEngineActor
{
public:
	// construtor destructor
	PathDot();
	~PathDot();

	// delete Function
	PathDot(const PathDot& _Other) = delete;
	PathDot(PathDot&& _Other) noexcept = delete;
	PathDot& operator=(const PathDot& _Other) = delete;
	PathDot& operator=(PathDot&& _Other) noexcept = delete;

	static std::shared_ptr<PathDot> CreatPathDot(GameEngineActor* _Parent, const std::string_view& _DotColor); // Red or Blue
	void SetNextActor(GameEngineActor* _nextActor)
	{
		NextActor = _nextActor;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineActor* NextActor = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> DotRenderer = nullptr;
	float4 RenderScale = {13,13,1};
};

