#pragma once
#include "BaseMonster.h"
class Fallen : public BaseMonster
{
public:
	// construtor destructor
	Fallen();
	~Fallen();

	// delete Function
	Fallen(const Fallen& _Other) = delete;
	Fallen(Fallen&& _Other) noexcept = delete;
	Fallen& operator=(const Fallen& _Other) = delete;
	Fallen& operator=(Fallen&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderScale = { 128,128,1 };
	float4 ColLocalPos = { 0,0,0 };
	float4 ColScale = { 30,30,1 };

	static GameEngineSoundPlayer DeathSound;
	void BornStateInit();
};

