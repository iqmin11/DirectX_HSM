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
	float4 ActorPos = float4::Zero;
	float ScaleRatio = 720.f / 640.f;
	
	std::shared_ptr<class GameEngineSpriteRenderer> UpgradeBgLeft = nullptr;
	float4 UpgradeBgLeftScale = { 70.f, 656.f };
	std::shared_ptr<GameEngineSpriteRenderer> UpgradeBgMid = nullptr;
	float4 UpgradeBgMidScale = { 618.f, 618.f, 0.f, 1.f };
	float4 UpgradeBgMidPos= {-200.f,0.f };
	std::shared_ptr<GameEngineSpriteRenderer> UpgradeBgRight = nullptr;
	float4 UpgradeBgRightScale = { 70.f, 656.f };

	void SetUpgradeBgPos(float4& _Pos);

};

