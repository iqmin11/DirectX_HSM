#pragma once
#include "BaseMonster.h"
class Executioner : public BaseMonster
{
public:
	// construtor destructor
	Executioner();
	~Executioner();

	// delete Function
	Executioner(const Executioner& _Other) = delete;
	Executioner(Executioner&& _Other) noexcept = delete;
	Executioner& operator=(const Executioner& _Other) = delete;
	Executioner& operator=(Executioner&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderScale = { 256,256,1 };
	float4 ColLocalPos = { 0,0,0 };
	float4 ColScale = { 30,30,1 };

	static GameEngineSoundPlayer DeathSound;
};

