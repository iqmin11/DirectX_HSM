#pragma once
#include "BaseStgObj.h"

class Stg2_Obj : public BaseStgObj
{
public:
	// construtor destructor
	Stg2_Obj();
	~Stg2_Obj();

	// delete Function
	Stg2_Obj(const Stg2_Obj& _Other) = delete;
	Stg2_Obj(Stg2_Obj&& _Other) noexcept = delete;
	Stg2_Obj& operator=(const Stg2_Obj& _Other) = delete;
	Stg2_Obj& operator=(Stg2_Obj&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Obj0 = std::shared_ptr<class GameEngineSpriteRenderer>();
	std::shared_ptr<class GameEngineSpriteRenderer> Obj1 = std::shared_ptr<class GameEngineSpriteRenderer>();

};

