#include "PrecompileHeader.h"
#include "Artillery_Tower.h"

#include <GameEngineBase\GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "TowerButton.h"

#include "Artillery_Bullet.h"
#include "BuildArea.h"
#include "UpgradeTowerUI.h"
#include "BaseMonster.h"
#include "Dwaarp_Effect_HitWave.h"

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

std::shared_ptr<Artillery_Tower> Artillery_Tower::CreateTower(GameEngineLevel* _Level, BuildArea* _BuildArea)
{
	std::shared_ptr<Artillery_Tower> LocalAc = nullptr;
	LocalAc = _Level->CreateActor<Artillery_Tower>();
	LocalAc->ParentArea = _BuildArea;
	LocalAc->GetTransform()->SetWorldPosition(_BuildArea->GetTransform()->GetWorldPosition());
	LocalAc->UpgradeButton = TowerButton::CreateButton(LocalAc.get());
	LocalAc->UpgradeButton->Off();
	LocalAc->UpgradeUI = UpgradeTowerUI::CreateUpgradeTowerUI(LocalAc.get());
	float4 Position = LocalAc->GetTransform()->GetWorldPosition();
	LocalAc->TowerRangeRender->GetTransform()->SetWorldPosition({ Position.x, Position.y, -1000.f });
	LocalAc->NextLvRangeRender->GetTransform()->SetWorldPosition({ Position.x, Position.y, -1000.f });
	return LocalAc;
}

void Artillery_Tower::Start()
{
	BaseShootingTower::Start();
	Data.SetData(TowerEnum::ArtilleryTower_Level1);

	TowerRenderer->CreateAnimation({ .AnimationName = "Construct", .SpriteName = "ArtilleryTower_Construct",.FrameInter = 0.08f,.Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "1_Attack", .SpriteName = "ArtilleryTower_Level1_Attack",.FrameInter = 0.08f,.Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "1_Idle", .SpriteName = "ArtilleryTower_Level1_Idle",.FrameInter = 0.08f,.Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "2_Attack", .SpriteName = "ArtilleryTower_Level2_Attack",.FrameInter = 0.08f,.Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "2_Idle", .SpriteName = "ArtilleryTower_Level2_Idle",.FrameInter = 0.08f,.Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "3_Attack", .SpriteName = "ArtilleryTower_Level3_Attack",.FrameInter = 0.08f,.Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "3_Idle", .SpriteName = "ArtilleryTower_Level3_Idle",.FrameInter = 0.08f,.Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "4_Attack", .SpriteName = "ArtilleryTower_Level4_Attack",.FrameInter = 0.065f,.Loop = false });
	TowerRenderer->CreateAnimation({ .AnimationName = "4_Idle", .SpriteName = "ArtilleryTower_Level4_Idle",.FrameInter = 0.065f,.Loop = false });

	TowerRenderer->SetAnimationStartEvent("1_Attack",4,std::bind(&Artillery_Tower::ArtilleryAttack,this));
	TowerRenderer->SetAnimationStartEvent("2_Attack",4,std::bind(&Artillery_Tower::ArtilleryAttack,this));
	TowerRenderer->SetAnimationStartEvent("3_Attack",4,std::bind(&Artillery_Tower::ArtilleryAttack,this));
	TowerRenderer->SetAnimationStartEvent("4_Attack",6,std::bind(&Artillery_Tower::DwaarpAttack,this));

	TowerRenderer->SetAnimationStartEvent("1_Attack", 9, std::bind(&Artillery_Tower::ChangeIdleState, this));
	TowerRenderer->SetAnimationStartEvent("2_Attack", 9, std::bind(&Artillery_Tower::ChangeIdleState, this));
	TowerRenderer->SetAnimationStartEvent("3_Attack", 9, std::bind(&Artillery_Tower::ChangeIdleState, this));
	TowerRenderer->SetAnimationStartEvent("4_Attack",31, std::bind(&Artillery_Tower::ChangeIdleState, this));

	TowerRenderer->ChangeAnimation("Construct");
	TowerRenderer->GetTransform()->SetWorldScale(RenderScale);

	FireSmokeRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	FireSmokeRenderer->GetTransform()->SetWorldScale(SmokeRenderScale);
	FireSmokeRenderer->GetTransform()->SetLocalPosition(Lv1SmokeLocalPos);
	FireSmokeRenderer->CreateAnimation({.AnimationName = "Fire", .SpriteName = "ArtilleryTower_FireSmoke", .FrameInter = 0.08f,.Loop = false});
	FireSmokeRenderer->ChangeAnimation("Fire");
	FireSmokeRenderer->Off();

	TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	TowerRangeRender->Off();
	NextLvRangeRender->GetTransform()->SetWorldScale({ Data.GetNextLvRange() * 2,Data.GetNextLvRange() * 2 });
	NextLvRangeRender->Off();
	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	RangeCol->Off();
	IsThereTargetFuncPtr = std::bind(&Artillery_Tower::IsThereTarget, this);
	FindTargetMonsterFuncPtr = std::bind(&Artillery_Tower::FindTargetMonster, this);

	TauntSoundName[0] = "Artillery_Ready.ogg";
	TauntSoundName[1] = "Artillery_Taunt1.ogg";
	TauntSoundName[2] = "Artillery_Taunt2.ogg";
	TauntSoundName[3] = "earthquake_taunt_ready.ogg";
}

void Artillery_Tower::Update(float _DeltaTime)
{
	if (Construct == ConstructState::Constructing)
	{
		Time += _DeltaTime;
		BuildBar->GetTransform()->SetWorldScale(float4::LerpClamp({ 0,8,1 }, BuildBarScale, Time));
		BuildBar->GetTransform()->SetLocalPosition(float4::LerpClamp({ -27,50 }, { 0,50 }, Time));

		if (Time >= 1.f)
		{
			Time = 100;
			Construct = ConstructState::Complete;
			BuildBar->Off();
			BuildBarBg->Off();

			RangeCol->On();
			UpgradeButton->On();
			TowerRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Idle");
			PlayTowerCommandSound(TauntSoundName[GameEngineRandom::MainRandom.RandomInt(0, 2)]);
		}
	}
	else
	{
		BaseShootingTower::Update(_DeltaTime);
		if (GameEngineInput::IsUp("M"))
		{
			ChangeTower(TowerEnum::ArtilleryTower_Level4);
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
	TowerRangeRender->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	if (Data.Level < 4)
	{
		NextLvRangeRender->GetTransform()->SetWorldScale({ Data.GetNextLvRange() * 2,Data.GetNextLvRange() * 2 });
	}
	RangeCol->GetTransform()->SetWorldScale({ Data.Range * 2,Data.Range * 2 });
	PlayTauntSound(Data.Level);

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
		FireSmokeRenderer->Off();
		break;
	default:
		break;
	}
}

void Artillery_Tower::ArtilleryAttack()
{
	FireSmokeRenderer->ChangeAnimation("Fire");
	FireSmokeRenderer->On();
	PlayAttackSound("Sound_EngineerShot.ogg");
	Artillery_Bullet::ShootingBullet(GetLevel(), this);
}

void Artillery_Tower::DwaarpAttack()
{
	PlayAttackSound("dwaarp_attack.ogg");
	std::vector<std::shared_ptr<GameEngineCollision>> TempVec = std::vector<std::shared_ptr<GameEngineCollision>>();
	TempVec.reserve(30);
	RangeCol->CollisionAll(ColOrder::Monster, TempVec, ColType::SPHERE2D, ColType::SPHERE2D);
	for (size_t i = 0; i < TempVec.size(); i++)
	{
		int Damage = GameEngineRandom::MainRandom.RandomInt(Data.Damage_min,Data.Damage_MAX);
		std::weak_ptr<BaseMonster> Monster(TempVec[i]->GetActor()->DynamicThis<BaseMonster>());
		Monster.lock()->Hit = HitState::Bomb;
		Monster.lock()->CurHP -= Damage;
		Dwaarp_Effect_HitWave::CreateEffect(this);
	}
}

void Artillery_Tower::ChangeIdleState()
{
	TowerRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Idle");
}

bool Artillery_Tower::IsThereTarget()
{
	if (nullptr == RangeCol->Collision(ColOrder::Monster, ColType::SPHERE2D, ColType::SPHERE2D))
	{
		return false;
	}
	else
	{
		std::vector<std::shared_ptr<GameEngineCollision>> LocalVec;
		LocalVec.reserve(30);
		RangeCol->CollisionAll(ColOrder::Monster, LocalVec, ColType::SPHERE2D, ColType::SPHERE2D);

		for (size_t i = 0; i < LocalVec.size(); i++)
		{
			std::weak_ptr<BaseMonster> TempMonster(LocalVec[i]->GetActor()->DynamicThis<BaseMonster>());
			if (TempMonster.lock()->GetData().IsBurrow == false && TempMonster.lock()->GetData().IsFlying == false)
			{
				return true;
			}
		}
		return false;
	}
}

std::shared_ptr<class BaseMonster> Artillery_Tower::FindTargetMonster()
{
	std::vector<std::shared_ptr<GameEngineCollision>> LocalColVec0 = std::vector<std::shared_ptr<GameEngineCollision>>();
	std::vector<std::shared_ptr<GameEngineCollision>> LocalColVec1 = std::vector<std::shared_ptr<GameEngineCollision>>();
	LocalColVec0.reserve(30);
	RangeCol->CollisionAll(static_cast<int>(ColOrder::Monster), LocalColVec0, ColType::SPHERE2D, ColType::SPHERE2D);
	std::shared_ptr<BaseMonster> TargetMonster = std::shared_ptr<BaseMonster>();

	for (size_t i = 0; i < LocalColVec0.size(); i++)
	{
		std::weak_ptr<BaseMonster> TempMonster(LocalColVec0[i]->GetActor()->DynamicThis<BaseMonster>());
		if (TempMonster.lock()->GetData().IsBurrow == false && TempMonster.lock()->GetData().IsFlying == false)
		{
			LocalColVec1.push_back(LocalColVec0[i]);
		}
	}
	TargetMonster = LocalColVec1[0]->GetActor()->DynamicThis<BaseMonster>();
	float Smallest = TargetMonster->CalDistance();
	for (size_t i = 0; i < LocalColVec1.size(); i++)
	{
		std::shared_ptr<BaseMonster> CompairMonster = LocalColVec1[i]->GetActor()->DynamicThis<BaseMonster>();
		if (Smallest <= std::min<float>(Smallest, CompairMonster->CalDistance()) || CompairMonster->GetData().IsBurrow)
		{
			continue;
		}
		else
		{
			TargetMonster = CompairMonster;
		}
	}
	return TargetMonster;
}

void Artillery_Tower::PlayAttackSound(const std::string_view _Name)
{
	AttackSound = GameEngineSound::Play(_Name);
	AttackSound.SetVolume(0.2f);
}
