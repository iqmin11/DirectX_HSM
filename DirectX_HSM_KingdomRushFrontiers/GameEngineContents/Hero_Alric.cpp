#include "PrecompileHeader.h"
#include "Hero_Alric.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RallyPoint.h"
#include "BaseMonster.h"

Hero_Alric::Hero_Alric()
{

}

Hero_Alric::~Hero_Alric()
{

}

void Hero_Alric::Start()
{
	BaseFighter::Start();
	BaseFighter::AttackTarget = std::bind(&Hero_Alric::AttackTarget, this);
	
	LifeBarScale = { 40,3,1 };
	LifeBarBgLocalPos = { 0,42,1 };
	LifeBarLocalPos = { 0, 42 };
	LifeBar->GetTransform()->SetWorldScale(LifeBarScale);
	LifeBar->GetTransform()->SetLocalPosition(LifeBarLocalPos);
	LifeBarBg->GetTransform()->SetWorldScale(LifeBarScale);
	LifeBarBg->GetTransform()->SetLocalPosition(LifeBarBgLocalPos);

	FighterRenderer->CreateAnimation({ .AnimationName = "Attack0", .SpriteName = "Hero_Alric_Attack_0", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Attack1", .SpriteName = "Hero_Alric_Attack_1", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Death", .SpriteName = "Hero_Alric_Death", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Hero_Alric_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Move", .SpriteName = "Hero_Alric_Move", .FrameInter = 0.04f, .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "Revive", .SpriteName = "Hero_Alric_Revive", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Flurry", .SpriteName = "Hero_Alric_Skill_Flurry", .FrameInter = 0.075f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Summon", .SpriteName = "Hero_Alric_Skill_Summon", .Loop = false });

	FighterRenderer->SetAnimationStartEvent("Attack0", 3, BaseFighter::AttackTarget);
	FighterRenderer->SetAnimationStartEvent("Attack1", 5, BaseFighter::AttackTarget);
	FighterRenderer->SetAnimationStartEvent("Flurry", 11, std::bind(&Hero_Alric::AttackFlurry, this));

	FighterRenderer->GetTransform()->SetWorldScale({217,217,1});

	IdleStateInit();
	MoveStateInit();
	TraceMonsterStateInit();
	AttackStateInit();
	ReturnStateInit();
	DeathStateInit();
	ReviveStateInit();
	CastingSkill0StateInit();
	CastingSkill1StateInit();
}

void Hero_Alric::Update(float _DeltaTime)
{
	BaseFighter::Update(_DeltaTime);
	FighterFSM.Update(_DeltaTime);
}

void Hero_Alric::AttackTarget()
{
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->Hit = HitState::Melee;
}

void Hero_Alric::AttackFlurry()
{
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->Hit = HitState::Melee;
}

int Hero_Alric::CalDamage()
{
	return BaseFighter::CalDamage();
}
