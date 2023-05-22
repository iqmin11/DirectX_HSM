#include "PrecompileHeader.h"
#include "Artillery_Tower.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Artillery_Bullet.h"

Artillery_Tower::Artillery_Tower()
{

}

Artillery_Tower::~Artillery_Tower()
{

}

std::shared_ptr<Artillery_Tower> Artillery_Tower::CreateTower(GameEngineLevel* _Level, const float4& _BuildPos)
{
	std::shared_ptr<Artillery_Tower> LocalAc = nullptr;
	LocalAc = _Level->CreateActor<Artillery_Tower>();
	LocalAc->ActorPos = _BuildPos;
	LocalAc->GetTransform()->SetWorldPosition(LocalAc->ActorPos);
	return LocalAc;
}

void Artillery_Tower::Start()
{
	BaseShootingTower::Start();
	Data.SetData(TowerEnum::ArtilleryTower_Level1);

	TowerRenderer->CreateAnimation({ .AnimationName = "1_Attack", .SpriteName = "ArtilleryTower_Level1_Attack",.FrameInter = 0.08f,.Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "1_Idle", .SpriteName = "ArtilleryTower_Level1_Idle",.FrameInter = 0.08f,.Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "2_Attack", .SpriteName = "ArtilleryTower_Level2_Attack",.FrameInter = 0.08f,.Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "2_Idle", .SpriteName = "ArtilleryTower_Level2_Idle",.FrameInter = 0.08f,.Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "3_Attack", .SpriteName = "ArtilleryTower_Level3_Attack",.FrameInter = 0.08f,.Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "3_Idle", .SpriteName = "ArtilleryTower_Level3_Idle",.FrameInter = 0.08f,.Loop = false });

	TowerRenderer->SetAnimationStartEvent("1_Attack",4,std::bind(&Artillery_Tower::ArtilleryAttack,this));
	TowerRenderer->SetAnimationStartEvent("2_Attack",4,std::bind(&Artillery_Tower::ArtilleryAttack,this));
	TowerRenderer->SetAnimationStartEvent("3_Attack",4,std::bind(&Artillery_Tower::ArtilleryAttack,this));

	TowerRenderer->ChangeAnimation("1_Idle");
	TowerRenderer->GetTransform()->SetWorldScale(RenderScale);

	//TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
}

void Artillery_Tower::Update(float _DeltaTime)
{
	BaseShootingTower::Update(_DeltaTime);
	if (GameEngineInput::IsUp("Space"))
	{
		ChangeTower(TowerEnum::ArtilleryTower_Level3);
	}

	if (IsThereTarget())
	{
		Time += _DeltaTime;
		if (Time >= Data.FireRate)
		{
			Time = 0;
			TowerRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Attack");
		}
	}
	else
	{
		TowerRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Idle");
	}
}

void Artillery_Tower::ChangeTower(TowerEnum _Tower)
{
	Data.SetData(_Tower);
	if (TowerEnum::MagicTower != Data.TowerType)
	{
		return;
	}
	ChangeTowerRender(Data.Level);
}

void Artillery_Tower::ChangeTowerRender(int _TowerLevel)
{
	TowerRenderer->ChangeAnimation(std::to_string(_TowerLevel) + "_Idle");
	//TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
}

void Artillery_Tower::ArtilleryAttack()
{
	Artillery_Bullet::ShootingBullet(GetLevel(), this);
}
