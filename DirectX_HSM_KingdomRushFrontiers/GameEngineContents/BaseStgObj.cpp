#include "PrecompileHeader.h"
#include "BaseStgObj.h"

#include <GameEngineCore\GameEngineLevel.h>
#include "Stg0_Obj.h"
#include "Stg1_Obj.h"
#include "Stg2_Obj.h"
#include "Stg3_Obj.h"
#include "Stg4_Obj.h"



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
	case 1:
		return _Level->CreateActor<Stg1_Obj>();
		break;
	case 2:
		return _Level->CreateActor<Stg2_Obj>();
		break;
	case 3:
		return _Level->CreateActor<Stg3_Obj>();
		break;
	case 4:
		return _Level->CreateActor<Stg4_Obj>();
		break;
	
	default:
		return nullptr;
		break;
	}
}
