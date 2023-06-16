#pragma once
#include<GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class StageBg : public GameEngineActor
{
public:
	// construtor destructor
	StageBg();
	~StageBg();

	// delete Function
	StageBg(const StageBg& _Other) = delete;
	StageBg(StageBg&& _Other) noexcept = delete;
	StageBg& operator=(const StageBg& _Other) = delete;
	StageBg& operator=(StageBg&& _Other) noexcept = delete;

	void RenderStage(int _Stage = -1);
	std::shared_ptr<class GameEngineTexture> GetColmap(int _Stage = -1);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;
	float4 TextureScale = {1650, 900, 1};
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> StageBgRenderer = std::vector<std::shared_ptr<class GameEngineSpriteRenderer>>();
	//std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> StageColmapRender = std::vector<std::shared_ptr<class GameEngineSpriteRenderer>>();
	std::vector<std::shared_ptr<class GameEngineTexture>> StageColmap = std::vector<std::shared_ptr<class GameEngineTexture>>();
};

