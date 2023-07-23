#pragma once
#include "BaseMonster.h"
class DuneTerror : public BaseMonster
{
public:
	// construtor destructor
	DuneTerror();
	~DuneTerror();

	// delete Function
	DuneTerror(const DuneTerror& _Other) = delete;
	DuneTerror(DuneTerror&& _Other) noexcept = delete;
	DuneTerror& operator=(const DuneTerror& _Other) = delete;
	DuneTerror& operator=(DuneTerror&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderScale = { 128,128,1 };
	float4 ColLocalPos = { 0,0,0 };
	float4 ColScale = { 30,30,1 };

	static GameEngineSoundPlayer DeathSound;

	void IdleStateInit() override;
	void MoveStateInit() override;
	void AttackStateInit() override;
	void DeathStateInit() override;
	void ComeUpStateInit();
	void GoDownStateInit();
};

