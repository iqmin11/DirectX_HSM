#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"

class TitleMenuManager : public GameEngineActor
{
public:
	// construtor destructor
	TitleMenuManager();
	~TitleMenuManager();

	// delete Function
	TitleMenuManager(const TitleMenuManager& _Other) = delete;
	TitleMenuManager(TitleMenuManager&& _Other) noexcept = delete;
	TitleMenuManager& operator=(const TitleMenuManager& _Other) = delete;
	TitleMenuManager& operator=(TitleMenuManager&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<class GameEngineUIRenderer> ButtonBg = nullptr;

	std::shared_ptr<class  ContentsButton> StartButton = nullptr;
	std::shared_ptr<class  GameEngineUIRenderer> OptionButton = nullptr;
	std::shared_ptr<class  GameEngineUIRenderer> ProducerButton = nullptr;
	std::shared_ptr<class  ContentsButton> ExitButton = nullptr;

};

