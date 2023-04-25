#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UpgradeMenu : public GameEngineActor
{
public:
	// construtor destructor
	UpgradeMenu();
	~UpgradeMenu();

	// delete Function
	UpgradeMenu(const UpgradeMenu& _Other) = delete;
	UpgradeMenu(UpgradeMenu&& _Other) noexcept = delete;
	UpgradeMenu& operator=(const UpgradeMenu& _Other) = delete;
	UpgradeMenu& operator=(UpgradeMenu&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:


};

