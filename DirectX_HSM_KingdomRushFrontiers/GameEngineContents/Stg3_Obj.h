#pragma once
#include "BaseStgObj.h"
class Stg3_Obj : public BaseStgObj
{
public:
	// construtor destructor
	Stg3_Obj();
	~Stg3_Obj();

	// delete Function
	Stg3_Obj(const Stg3_Obj& _Other) = delete;
	Stg3_Obj(Stg3_Obj&& _Other) noexcept = delete;
	Stg3_Obj& operator=(const Stg3_Obj& _Other) = delete;
	Stg3_Obj& operator=(Stg3_Obj&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Obj0 = std::shared_ptr<class GameEngineSpriteRenderer>();

};

