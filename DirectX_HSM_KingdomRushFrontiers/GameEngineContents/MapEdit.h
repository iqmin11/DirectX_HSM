#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEngineSerializer.h>
#include <GameEngineBase/GameEngineFile.h>


enum class StageState
{
	Stage1,
	Stage2,
	Stage3,
	Stage4,
	Stage5,
	Stage6,
};

struct PathPoint
{
	float4 Position = float4::Zero;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer = nullptr;
};

class MapEdit : public GameEngineActor
{
public:
	// construtor destructor
	MapEdit();
	~MapEdit();

	// delete Function
	MapEdit(const MapEdit& _Other) = delete;
	MapEdit(MapEdit&& _Other) noexcept = delete;
	MapEdit& operator=(const MapEdit& _Other) = delete;
	MapEdit& operator=(MapEdit&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;
	float4 MapRendererScale = {1200,1000};
	StageState State = StageState::Stage1;

	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> MapRenderer = std::vector<std::shared_ptr<GameEngineSpriteRenderer>>();

	std::map<int, std::list<PathPoint>> MonsterPaths = std::map<int, std::list<PathPoint>>();
	int PathIndex = -1;

	GameEngineSerializer SaveMonsterPath = GameEngineSerializer();


	void StateToMapRenderer();
	void NextState();
	void PrevState();

	void PushbackPath();
	void PushbackPathPoint();

	void SaveData();
};

//구조 생각...오른쪽 왼쪽키로 맵 랜더러 결정 가능..


