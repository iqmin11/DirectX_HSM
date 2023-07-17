#include "PrecompileHeader.h"
#include "BaseStgObj.h"

#include <GameEngineCore\GameEngineLevel.h>
#include "Stg0_Obj.h"



BaseStgObj::BaseStgObj()
{

}

BaseStgObj::~BaseStgObj()
{

}

std::shared_ptr<BaseStgObj> BaseStgObj::CreateStgObj(class GameEngineLevel* _Level, int _Stage)
{
	switch (_Stage)
	{
	case 0:
		return _Level->CreateActor<Stg0_Obj>();
		break;
	
	default:
		return nullptr;
		break;
	}
}
