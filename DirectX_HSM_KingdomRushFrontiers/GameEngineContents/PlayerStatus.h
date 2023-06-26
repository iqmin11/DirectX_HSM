#pragma once
#include <GameEngineCore\GameEngineActor.h>

class PlayerStatus : public GameEngineActor
{
public:
	// construtor destructor
	PlayerStatus();
	~PlayerStatus();

	// delete Function
	PlayerStatus(const PlayerStatus& _Other) = delete;
	PlayerStatus(PlayerStatus&& _Other) noexcept = delete;
	PlayerStatus& operator=(const PlayerStatus& _Other) = delete;
	PlayerStatus& operator=(PlayerStatus&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	class PlayStageLevel* ParentLevel = nullptr;

	std::shared_ptr<class GameEngineUIRenderer> StatusBg = nullptr;
	float4 StatusBgScale = { 390,76,1 };

	float FontScale = 27.f;
	
	int* LifePtr = nullptr;
	std::shared_ptr<class UIFontRenderer> LifeRender = nullptr;
	float4 LifeLocPos = { -112,0 };
	
	int* GoldPtr = nullptr;
	std::shared_ptr<class UIFontRenderer> GoldRender = nullptr;
	float4 GoldLocPos = { -50,0 };

	const int* CurWave = nullptr;
	const int* MaxWave = nullptr;
	std::shared_ptr<class UIFontRenderer> WaveRender = nullptr;
	float4 WaveLocPos = { 60,0 };

};

