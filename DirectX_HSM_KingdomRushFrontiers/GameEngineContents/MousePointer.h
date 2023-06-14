#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class MousePointer : public GameEngineActor
{
public:
	// construtor destructor
	MousePointer();
	~MousePointer();

	// delete Function
	MousePointer(const MousePointer& _Other) = delete;
	MousePointer(MousePointer&& _Other) noexcept = delete;
	MousePointer& operator=(const MousePointer& _Other) = delete;
	MousePointer& operator=(MousePointer&& _Other) noexcept = delete;

	static const float4& GetMousePosRef()
	{
		return MousePos;
	}
	static const float4& GetMouseWinPosRef();
	static const float4 GetMouseColmapPos();
	

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static float4 MousePos;
	std::shared_ptr<class GameEngineSpriteRenderer> MousePointerRenderer = nullptr;
	std::shared_ptr<class GameEngineCollision> MousePointerCol = nullptr;
};

