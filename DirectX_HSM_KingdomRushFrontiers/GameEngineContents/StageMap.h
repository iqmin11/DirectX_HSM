#pragma once
#include <GameEngineCore/GameEngineActor.h>

class StageMap : public GameEngineActor // 맵과 경로, 포탑의 위치를 모두 관리하는 액터
{
public:
	// construtor destructor
	StageMap();
	~StageMap();

	// delete Function
	StageMap(const StageMap& _Other) = delete;
	StageMap(StageMap&& _Other) noexcept = delete;
	StageMap& operator=(const StageMap& _Other) = delete;
	StageMap& operator=(StageMap&& _Other) noexcept = delete;

	static StageMap* MainStageMap;
	//std::list<float4> TestPath = std::list<float4>();
	std::list<float4>& GetMonsterPath(int _Index);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;
	
	int Stage = 1;

	std::shared_ptr<class GameEngineSpriteRenderer> StageMapRenderer = nullptr;
	float4 StageMapRendererScale = {1200,1000};
	
	int MonsterPathCount = 0;
	std::vector<std::list<float4>> MonsterPath = std::vector<std::list<float4>>();

	void LoadMonsterPath();
};

