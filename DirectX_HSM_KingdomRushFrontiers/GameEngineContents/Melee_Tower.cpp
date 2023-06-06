#include "PrecompileHeader.h"
#include "Melee_Tower.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "Melee_RallyPoint.h"
#include "BuildArea.h"

Melee_Tower::Melee_Tower()
{

}

Melee_Tower::~Melee_Tower()
{

}

std::shared_ptr<Melee_Tower> Melee_Tower::CreateTower(GameEngineLevel* _Level, BuildArea* _BuildArea)
{
	std::shared_ptr<Melee_Tower> LocalAc = nullptr;
	LocalAc = _Level->CreateActor<Melee_Tower>();
	LocalAc->ParentArea = _BuildArea;
	LocalAc->GetTransform()->SetWorldPosition(_BuildArea->GetTransform()->GetWorldPosition());
	LocalAc->AcRallyPoint = Melee_RallyPoint::CreateRallyPoint(_Level, _BuildArea->GetTransform()->GetWorldPosition(), 3);
	LocalAc->AcRallyPoint->GetTransform()->SetParent(LocalAc->GetTransform());
	LocalAc->AcRallyPoint->GetTransform()->SetWorldPosition(_BuildArea->GetRallyPos());
	LocalAc->AcRallyPoint->SetTowerData(&(LocalAc->Data));
	return LocalAc;
}

void Melee_Tower::Start()
{
	BaseTower::Start();

	Data.SetData(TowerEnum::MeleeTower_Level1);

	TowerRenderer->SetTexture("tower_barracks_lvl1.png");
	TowerRenderer->GetTransform()->SetWorldScale(RenderScale);
}

void Melee_Tower::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("M"))
	{
		ChangeTower(TowerEnum::MeleeTower_Level3);
	}
}

void Melee_Tower::ChangeTower(TowerEnum _Tower)
{
	Data.SetData(_Tower);
	if (TowerEnum::MeleeTower != Data.TowerType)
	{
		return;
	}
	ChangeTowerRender(Data.Level);
	ChangeFighter(Data.Level);
}

void Melee_Tower::ChangeTowerRender(int _TowerLevel)
{
	TowerRenderer->SetTexture("tower_barracks_lvl" + std::to_string(_TowerLevel) + ".png");
	//TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	//RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
}

void Melee_Tower::ChangeFighter(int _TowerLevel)
{
	if (AcRallyPoint == nullptr)
	{
		MsgAssert("랠리포인트가 nullptr입니다")
	}
	AcRallyPoint->ChangeFighters(_TowerLevel);
}
