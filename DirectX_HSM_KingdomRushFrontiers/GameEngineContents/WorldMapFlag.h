#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"
enum class FlagState
{
	Start,
	Update
};

class WorldMapFlag : public GameEngineActor
{
public:
	// construtor destructor
	WorldMapFlag();
	~WorldMapFlag();

	// delete Function
	WorldMapFlag(const WorldMapFlag& _Other) = delete;
	WorldMapFlag(WorldMapFlag&& _Other) noexcept = delete;
	WorldMapFlag& operator=(const WorldMapFlag& _Other) = delete;
	WorldMapFlag& operator=(WorldMapFlag&& _Other) noexcept = delete;

	void FlagOn();
	FlagState GetState() const
	{
		return State;
	}

	static std::shared_ptr <WorldMapFlag> CreateFlag(GameEngineActor* _Parent, std::function<void()> _Click);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	FlagState State = FlagState::Start;
	std::shared_ptr<class GameEngineUIRenderer> FlagAnimation = nullptr;
	float4 RenderScale = { 213,213,1 };
	
	std::shared_ptr<class FlagButton> AcButton = nullptr;

};

