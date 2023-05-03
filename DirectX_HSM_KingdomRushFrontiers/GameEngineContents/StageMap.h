#pragma once
#include <GameEngineCore/GameEngineActor.h>

class StageMap : public GameEngineActor // �ʰ� ���, ��ž�� ��ġ�� ��� �����ϴ� ����
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
	
	std::list<float4> MonsterPath0 = std::list<float4>();
	std::list<float4> MonsterPath1 = std::list<float4>();
	std::list<float4> MonsterPath2 = std::list<float4>();
	std::list<float4> MonsterPath3 = std::list<float4>();
	std::list<float4> MonsterPath4 = std::list<float4>();
	std::list<float4> MonsterPath5 = std::list<float4>();

	void LoadMonsterPath();
};

