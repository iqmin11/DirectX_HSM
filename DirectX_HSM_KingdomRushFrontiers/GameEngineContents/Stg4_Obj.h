#pragma once
#include "BaseStgObj.h"

class Stg4_Obj : public BaseStgObj
{
public:
	// construtor destructor
	Stg4_Obj();
	~Stg4_Obj();

	// delete Function
	Stg4_Obj(const Stg4_Obj& _Other) = delete;
	Stg4_Obj(Stg4_Obj&& _Other) noexcept = delete;
	Stg4_Obj& operator=(const Stg4_Obj& _Other) = delete;
	Stg4_Obj& operator=(Stg4_Obj&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Obj0 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Obj1 = nullptr;
};

