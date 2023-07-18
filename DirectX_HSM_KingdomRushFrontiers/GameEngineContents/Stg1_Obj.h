#pragma once
#include "BaseStgObj.h"

class Stg1_Obj : public BaseStgObj
{
public:
	// construtor destructor
	Stg1_Obj();
	~Stg1_Obj();

	// delete Function
	Stg1_Obj(const Stg1_Obj& _Other) = delete;
	Stg1_Obj(Stg1_Obj&& _Other) noexcept = delete;
	Stg1_Obj& operator=(const Stg1_Obj& _Other) = delete;
	Stg1_Obj& operator=(Stg1_Obj&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<class BaseTower> AcCityTower0 = nullptr;
	std::shared_ptr<class BaseTower> AcCityTower1 = nullptr;
};

