#pragma once
#include "ContentsButton.h"

class TowerButton : public ContentsButton
{
public:
	// construtor destructor
	TowerButton();
	~TowerButton();

	// delete Function
	TowerButton(const TowerButton& _Other) = delete;
	TowerButton(TowerButton&& _Other) noexcept = delete;
	TowerButton& operator=(const TowerButton& _Other) = delete;
	TowerButton& operator=(TowerButton&& _Other) noexcept = delete;

	static std::shared_ptr<TowerButton> CreateButton(class BaseTower* _ParentTower);

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	float4 ActorPos = float4::Zero;
	float4 Scale = { 110,95,1 };
};

