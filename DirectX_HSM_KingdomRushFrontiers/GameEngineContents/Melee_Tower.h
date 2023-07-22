#pragma once
#include "BaseTower.h"
#include "ContentsEnum.h"

class Melee_Tower : public BaseTower
{
public:
	// construtor destructor
	Melee_Tower();
	~Melee_Tower();

	// delete Function
	Melee_Tower(const Melee_Tower& _Other) = delete;
	Melee_Tower(Melee_Tower&& _Other) noexcept = delete;
	Melee_Tower& operator=(const Melee_Tower& _Other) = delete;
	Melee_Tower& operator=(Melee_Tower&& _Other) noexcept = delete;

	static std::shared_ptr<Melee_Tower> CreateTower(GameEngineLevel* _Level, BuildArea* _BuildArea);
	bool SetRallyMod = false;

	void ChangeTower(TowerEnum _Tower) override;
	bool SetRally();

	void PlayTauntSound(int _Level) override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderScale = { 256,256,1 };
	std::shared_ptr<class Melee_RallyPoint> AcRallyPoint = nullptr;

	float Time = 0.f;

	void ChangeTowerRender(int _TowerLevel);
	void ChangeFighter(int _TowerLevel);

};

