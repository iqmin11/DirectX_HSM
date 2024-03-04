#pragma once
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform\GameEngineSound.h>

class ContentsCore : public GameEngineCore
{
public:
	
	// constrcuter destructer
	ContentsCore();
	~ContentsCore();

	// delete Function
	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;

	static void ContentsResourcesCreate();

	static void GameStart();
	static void GameEnd();
	
	static GameEngineSoundPlayer BGM;
	static void BGMPlay(const std::string_view& _File);
	static void BGMStop();

protected:

private:
	static void InstallFont();
	static void RemoveFont();
	static void LoadSound();
};

