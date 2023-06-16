#pragma once
#include <GameEngineCore\GameEngineActor.h>


class CallReinforcement : public GameEngineActor
{
public:
	// construtor destructor
	CallReinforcement();
	~CallReinforcement();

	// delete Function
	CallReinforcement(const CallReinforcement& _Other) = delete;
	CallReinforcement(CallReinforcement&& _Other) noexcept = delete;
	CallReinforcement& operator=(const CallReinforcement& _Other) = delete;
	CallReinforcement& operator=(CallReinforcement&& _Other) noexcept = delete;

	static void CastingSpell(GameEngineLevel* _Level, const float4& _Pos);

protected:


private:
	
};

