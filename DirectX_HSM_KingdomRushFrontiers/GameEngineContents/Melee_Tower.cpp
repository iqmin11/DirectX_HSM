#include "PrecompileHeader.h"
#include "Melee_Tower.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "Melee_RallyPoint.h"
#include "BuildArea.h"
#include "TowerButton.h"

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
	LocalAc->UpgradeButton = TowerButton::CreateButton(LocalAc.get());
	LocalAc->UpgradeButton->Off();
	return LocalAc;
}

void Melee_Tower::Start()
{
	BaseTower::Start();

	Data.SetData(TowerEnum::MeleeTower_Level1);

	TowerRenderer->SetTexture("tower_constructing_0002.png");
	TowerRenderer->GetTransform()->SetWorldScale(RenderScale);
}

void Melee_Tower::Update(float _DeltaTime)
{
	if (Construct == ConstructState::Constructing)
	{
		Time += _DeltaTime;
		BuildBar->GetTransform()->SetWorldScale(float4::LerpClamp({ 0,8,1 }, BuildBarScale, Time));
		BuildBar->GetTransform()->SetLocalPosition(float4::LerpClamp({ -27,50 }, { 0,50 }, Time));

		if (Time >= 1.f)
		{
			Time = 0;
			Construct = ConstructState::Complete;
			BuildBar->Off();
			BuildBarBg->Off();

			TowerRenderer->SetTexture("tower_barracks_lvl1.png");
			UpgradeButton->On();

			AcRallyPoint = Melee_RallyPoint::CreateRallyPoint(GetLevel(), ParentArea->GetTransform()->GetWorldPosition(), 3);
			AcRallyPoint->GetTransform()->SetParent(GetTransform());
			AcRallyPoint->GetTransform()->SetWorldPosition(ParentArea->GetRallyPos());
			AcRallyPoint->SetTowerData(&Data);
		}
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
