#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"
enum class FlagState
{
	Start,
	Update
};

class ClearData
{
public:
	bool Clear = false;
	int StarCount = 0;
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

	void SetClearData(int _StarCount);
	int GetStarCount()
	{
		return Data.StarCount;
	}

	void SetNextStageOnTrigger(GameEngineActor* _NextOn)
	{
		NextStageOnTrigger = _NextOn;
	}

	FlagState GetState() const
	{
		return State;
	}

	void SetState(FlagState _State)
	{
		State = _State;
	}

	void On() override;

	static std::shared_ptr <WorldMapFlag> CreateFlag(GameEngineActor* _Parent, std::function<void()> _Click);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static FlagState State;

	ClearData Data = ClearData();

	std::shared_ptr<class GameEngineUIRenderer> FlagAnimation = nullptr;
	float4 RenderScale = { 213,213,1 };

	std::vector<std::shared_ptr<class GameEngineUIRenderer>> StarRenderers = std::vector<std::shared_ptr<class GameEngineUIRenderer>>();
	
	std::shared_ptr<class FlagButton> AcButton = nullptr;
	bool ClearAndFirstUpdate = true;

	GameEngineActor* NextStageOnTrigger = nullptr;
};

