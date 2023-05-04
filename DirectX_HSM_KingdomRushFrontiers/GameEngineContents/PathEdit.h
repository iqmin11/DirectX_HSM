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

struct StageMapData_Desc
{
	int Stage = -1;
	std::map<int, std::list<PathPoint>> MonsterPaths = std::map<int, std::list<PathPoint>>();
	//std::vector<float4> TowerPos = std::vector<float4>();
};

class PathEdit : public GameEngineActor
{
public:
	// construtor destructor
	PathEdit();
	~PathEdit();

	// delete Function
	PathEdit(const PathEdit& _Other) = delete;
	PathEdit(PathEdit&& _Other) noexcept = delete;
	PathEdit& operator=(const PathEdit& _Other) = delete;
	PathEdit& operator=(PathEdit&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;
	StageState StageStateValue = StageState::Stage1;
	float4 MapRendererScale = {1200,1000};
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> MapRenderer = std::vector<std::shared_ptr<GameEngineSpriteRenderer>>();

	StageMapData_Desc Desc = StageMapData_Desc();
	std::vector<std::vector<std::shared_ptr<class GameEngineSpriteRenderer>>> NumRenderer = std::vector<std::vector<std::shared_ptr<class GameEngineSpriteRenderer>>>();
	UINT PathIndex = 0;

	GameEngineSerializer SaveMapData = GameEngineSerializer();

	void StateToMapRenderer();
	void StageStateToDesc();
	void NextState();
	void PrevState();
	void ChangeState(StageState _Value);

	void IncreasPathIndex();
	void ReducePathIndex();
	void IndexToNumRenderer();
	void InsertOrFindPath();
	void PushbackPathPoint();

	

	void SaveData();


};

//구조 생각...오른쪽 왼쪽키로 맵 랜더러 결정 가능..


