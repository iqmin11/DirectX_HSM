#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform\GameEngineSound.h>
#include "ContentsEnum.h"
// Ό³Έν :

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

	static std::shared_ptr<ContentsButton> CreateButton(GameEngineActor * _ParentActor, const std::string_view& _Release = "Release.bmp", const std::string_view& _Hover = "Hover.bmp", const std::string_view& _Press = "Press.bmp");
	static std::shared_ptr<ContentsButton> CreateButton(GameEngineLevel* _ParentLevel, const std::string_view& _Release = "Release.bmp", const std::string_view& _Hover = "Hover.bmp", const std::string_view& _Press = "Press.bmp");

	void SetParentActor(GameEngineActor* _Actor);
	void SetTextureName(const std::string_view& _Release, const std::string_view& _Hover, const std::string_view& _Press);

	ButtonState GetState() const
	{
		return State;
	}

	GameEngineActor* GetParentActor() const 
	{
		return ParentActor;
	}

	std::function<void()> GetEvent() const
	{
		return Click;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;


	std::string ReleaseTextureName = "Release.bmp";
	std::string HoverTextureName = "Hover.bmp";
	std::string PressTextureName = "Press.bmp";

	//std::string ReleaseSound = "Release.bmp";
	std::string HoverSound = "";
	std::string UpSound = "Sound_GUIButtonCommon.ogg";

	std::string CurTextureName = std::string();

	ButtonState State = ButtonState::Release;
	std::shared_ptr<class  GameEngineSpriteRenderer> Render = nullptr;
	void PlayButtonSound(const std::string_view& _Sound = "");

private:
	GameEngineActor* ParentActor = nullptr;
	GameEngineSoundPlayer ButtonSound = GameEngineSoundPlayer();
	std::function<void()> Click;


	// std::shared_ptr<GameEngineCollision> Collision;
};

