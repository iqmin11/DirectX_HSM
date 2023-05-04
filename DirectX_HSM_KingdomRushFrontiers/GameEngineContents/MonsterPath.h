#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MonsterPath : public GameEngineActor
{
public:
	// construtor destructor
	MonsterPath();
	~MonsterPath();

	// delete Function
	MonsterPath(const MonsterPath& _Other) = delete;
	MonsterPath(MonsterPath&& _Other) noexcept = delete;
	MonsterPath& operator=(const MonsterPath& _Other) = delete;
	MonsterPath& operator=(MonsterPath&& _Other) noexcept = delete;

	std::list<float4>& GetMonsterPathRef(int _index)
	{
		return MonsterPathVec[_index];
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;
	int Stage = 1;
	int MonsterPathCount = 6;
	std::vector<std::list<float4>> MonsterPathVec = std::vector<std::list<float4>>();

	void LoadMonsterPath();
};

