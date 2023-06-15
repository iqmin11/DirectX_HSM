#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"

class FireBallExplosion : public GameEngineActor
{
public:
	// construtor destructor
	FireBallExplosion();
	~FireBallExplosion();

	// delete Function
	FireBallExplosion(const FireBallExplosion& _Other) = delete;
	FireBallExplosion(FireBallExplosion&& _Other) noexcept = delete;
	FireBallExplosion& operator=(const FireBallExplosion& _Other) = delete;
	FireBallExplosion& operator=(FireBallExplosion&& _Other) noexcept = delete;

	static void CreateExplosionEffect(GameEngineLevel* _Level, float4 _Pos);

protected:
	void Start() override;

private:
	
	std::shared_ptr<class GameEngineSpriteRenderer> ExplosionRenderer = nullptr;
	float4 RenderScale = { 128,128,1 };
	
};

