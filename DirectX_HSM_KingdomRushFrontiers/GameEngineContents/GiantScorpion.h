#pragma once
#include "BaseMonster.h"
class GiantScorpion : public BaseMonster
{
public:
	// construtor destructor
	GiantScorpion();
	~GiantScorpion();

	// delete Function
	GiantScorpion(const GiantScorpion& _Other) = delete;
	GiantScorpion(GiantScorpion&& _Other) noexcept = delete;
	GiantScorpion& operator=(const GiantScorpion& _Other) = delete;
	GiantScorpion& operator=(GiantScorpion&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderScale = { 128,128,1 };
	float4 ColLocalPos = { 0,0,0 };
	float4 ColScale = { 30,30,1 };
	static GameEngineSoundPlayer DeathSound;

	void AttackStateInit();
};

