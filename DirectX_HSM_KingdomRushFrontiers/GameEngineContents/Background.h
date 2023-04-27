#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Background : public GameEngineActor
{
public:
	// construtor destructor
	Background();
	~Background();

	// delete Function
	Background(const Background& _Other) = delete;
	Background(Background&& _Other) noexcept = delete;
	Background& operator=(const Background& _Other) = delete;
	Background& operator=(Background&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;
	std::shared_ptr<class GameEngineSpriteRenderer> Bg = nullptr;
	float4 BgScale = { 1280, 1080 };
};

