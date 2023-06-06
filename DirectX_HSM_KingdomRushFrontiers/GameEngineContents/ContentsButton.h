#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
// ���� :

class GameEngineUIRenderer;
class GameEngineCollision;
class ContentsButton : public GameEngineActor
{
public:
	// constrcuter destructer
	ContentsButton();
	~ContentsButton();

	// delete Function
	ContentsButton(const ContentsButton& _Other) = delete;
	ContentsButton(ContentsButton&& _Other) noexcept = delete;
	ContentsButton& operator=(const ContentsButton& _Other) = delete;
	ContentsButton& operator=(ContentsButton&& _Other) noexcept = delete;

	void SetEvent(std::function<void()> _Click)
	{
		Click = _Click;
	}

	static std::shared_ptr<ContentsButton> CreateButton(GameEngineActor * _ParentActor, const std::string_view & _Release, const std::string_view & _Hover, const std::string_view & _Press);
	static std::shared_ptr<ContentsButton> CreateButton(GameEngineLevel* _ParentLevel, const std::string_view& _Release, const std::string_view& _Hover, const std::string_view& _Press);

	void SetParentActor(GameEngineActor* _Actor);
	void SetTextureName(const std::string_view& _Release, const std::string_view& _Hover, const std::string_view& _Press);

	ButtonState GetState()
	{
		return State;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

	std::string ReleaseTextureName = std::string();
	std::string HoverTextureName = std::string();
	std::string PressTextureName = std::string();
	std::string CurTextureName = std::string();

	ButtonState State = ButtonState::Release;
	std::shared_ptr<GameEngineUIRenderer> Render;

private:
	GameEngineActor* ParentActor = nullptr;
	std::function<void()> Click;


	// std::shared_ptr<GameEngineCollision> Collision;
};
