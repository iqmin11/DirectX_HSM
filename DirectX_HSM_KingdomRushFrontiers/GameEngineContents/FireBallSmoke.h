#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"

class FireBallSmoke : public GameEngineActor
{
public:
	// construtor destructor
	FireBallSmoke();
	~FireBallSmoke();

	// delete Function
	FireBallSmoke(const FireBallSmoke& _Other) = delete;
	FireBallSmoke(FireBallSmoke&& _Other) noexcept = delete;
	FireBallSmoke& operator=(const FireBallSmoke& _Other) = delete;
	FireBallSmoke& operator=(FireBallSmoke&& _Other) noexcept = delete;

	static void CreateSmoke(GameEngineLevel* _Level, const float4& _Pos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> SmokeRenderer = nullptr;
	std::vector<float4> SmokeScales = std::vector<float4>();
	//float4 SmokeScale = {18,14,1}; 

	float Time = 0.f;


};

