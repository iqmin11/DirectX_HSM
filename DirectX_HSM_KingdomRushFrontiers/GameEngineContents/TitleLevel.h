#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class TitleLevel : public GameEngineLevel
{
public:
	// construtor destructor
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class TitleBackground> AcTitleBackground = nullptr;
	std::shared_ptr<class TitleMenuManager> AcTitleMenu = nullptr;
	std::shared_ptr<class Title_MousePointer> AcMousePointer = nullptr;
	float4 TitleMenuLocPos = { -450,-250 };
	//std::shared_ptr<class TitleLogo> AcTitleLogo = nullptr;
	//float4 CameraPos = { 0,0,-550 };
	void LoadTexture();
};

