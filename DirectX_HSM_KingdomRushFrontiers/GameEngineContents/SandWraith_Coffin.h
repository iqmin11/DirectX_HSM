#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "BaseMonster.h"
#include <GameEngineCore\GameEngineFSM.h>
#include <GameEnginePlatform\GameEngineSound.h>

enum class CoffinState
{
	Spawn,
	Update,
	Death
};

class SandWraith_Coffin : public GameEngineActor
{
public:
	// construtor destructor
	SandWraith_Coffin();
	~SandWraith_Coffin();

	// delete Function
	SandWraith_Coffin(const SandWraith_Coffin& _Other) = delete;
	SandWraith_Coffin(SandWraith_Coffin&& _Other) noexcept = delete;
	SandWraith_Coffin& operator=(const SandWraith_Coffin& _Other) = delete;
	SandWraith_Coffin& operator=(SandWraith_Coffin&& _Other) noexcept = delete;

	static void SummonCoffin(class SandWraith* _ParentActor);
	void SummonFallen();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	BaseMonster::WalkData Walk = BaseMonster::WalkData();
	std::shared_ptr<class GameEngineSpriteRenderer> CoffinRenderer = nullptr;
	float4 RenderScale = {256,256};

	CoffinState State = CoffinState::Spawn;
	GameEngineFSM CoffinFSM = GameEngineFSM();

	int SpawnMobCount = 4;
	float SpawnMobTime = 2.f;
	float Time = 0.f;

	void CoffinSpawnInit();
	void CoffinUpdateInit();
	void CoffinDeathInit();

	GameEngineSound CoffinSound = GameEngineSound();
};

