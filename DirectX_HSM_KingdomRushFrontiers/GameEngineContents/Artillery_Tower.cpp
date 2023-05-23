#include "PrecompileHeader.h"
#include "Artillery_Tower.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Artillery_Bullet.h"

const float4 Artillery_Tower::Lv1SmokeLocalPos = { 1,60,-60 }; // 0
const float4 Artillery_Tower::Lv2SmokeLocalPos = { 1,62,-62 }; // 2
const float4 Artillery_Tower::Lv3SmokeLocalPos = { 1,67,-67 }; // 7
const float4 Artillery_Tower::Lv4SmokeLocalPos = { 1,67,-67 }; // 7

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
	LocalAc->GetTransform()->SetWorldPosition(_BuildPos);
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

	FireSmokeRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	FireSmokeRenderer->GetTransform()->SetWorldScale(SmokeRenderScale);
	FireSmokeRenderer->GetTransform()->SetLocalPosition(Lv1SmokeLocalPos);
	FireSmokeRenderer->CreateAnimation({.AnimationName = "Fire", .SpriteName = "ArtilleryTower_FireSmoke", .FrameInter = 0.08f,.Loop = false});
	FireSmokeRenderer->ChangeAnimation("Fire");
	FireSmokeRenderer->Off();

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
	if (TowerEnum::ArtilleryTower != Data.TowerType)
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

	switch (_TowerLevel)
	{
	case 1:
		FireSmokeRenderer->GetTransform()->SetLocalPosition(Lv1SmokeLocalPos);
		break;
	case 2:
		FireSmokeRenderer->GetTransform()->SetLocalPosition(Lv2SmokeLocalPos);
		break;
	case 3:
		FireSmokeRenderer->GetTransform()->SetLocalPosition(Lv3SmokeLocalPos);
		break;
	case 4:
		FireSmokeRenderer->GetTransform()->SetLocalPosition(Lv4SmokeLocalPos);
		break;
	default:
		break;
	}
}

void Artillery_Tower::ArtilleryAttack()
{
	FireSmokeRenderer->ChangeAnimation("Fire");
	FireSmokeRenderer->On();
	Artillery_Bullet::ShootingBullet(GetLevel(), this);
}
