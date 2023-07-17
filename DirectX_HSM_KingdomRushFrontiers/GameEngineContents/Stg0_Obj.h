#pragma once
#include "BaseStgObj.h"

class Stg0_Obj : public BaseStgObj
{
public:
	// construtor destructor
	Stg0_Obj();
	~Stg0_Obj();

	// delete Function
	Stg0_Obj(const Stg0_Obj& _Other) = delete;
	Stg0_Obj(Stg0_Obj&& _Other) noexcept = delete;
	Stg0_Obj& operator=(const Stg0_Obj& _Other) = delete;
	Stg0_Obj& operator=(Stg0_Obj&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> HammerObj = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> WallObj = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> CastleFlag0 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> CastleFlag1 = nullptr;
	std::shared_ptr<class BaseTower> AcCityTower0 = nullptr;
	std::shared_ptr<class BaseTower> AcCityTower1 = nullptr;
};

