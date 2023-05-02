#pragma once
#include <GameEngineCore/GameEngineActor.h>

class StageMap : public GameEngineActor
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
	std::list<float4> TestPath = std::list<float4>();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	float4 ActorPos = float4::Zero;

	std::shared_ptr<class GameEngineSpriteRenderer> StageMapRenderer = nullptr;
	float4 StageMapRendererScale = {1200,1001};


	bool PathSetMode = false;
	//std::vector<float4> NorthPath2 = std::vector<float4>();
	//std::vector<float4> NorthPath3 = std::vector<float4>();
	//
	//std::vector<float4> SouthPath1 = std::vector<float4>();
	//std::vector<float4> SouthPath2 = std::vector<float4>();
	//std::vector<float4> SouthPath3 = std::vector<float4>();
};

