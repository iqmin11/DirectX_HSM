#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"

class BaseStgObj : public GameEngineActor
{
public:
	// construtor destructor
	BaseStgObj();
	~BaseStgObj();

	// delete Function
	BaseStgObj(const BaseStgObj& _Other) = delete;
	BaseStgObj(BaseStgObj&& _Other) noexcept = delete;
	BaseStgObj& operator=(const BaseStgObj& _Other) = delete;
	BaseStgObj& operator=(BaseStgObj&& _Other) noexcept = delete;

	static std::shared_ptr<BaseStgObj> CreateStgObj(class GameEngineLevel* _Level, int _Stage);

protected:
	int Stage = -1;

private:
};

