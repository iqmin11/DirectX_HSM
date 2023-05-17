#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class BuildArea : public GameEngineActor
{
public:
	// construtor destructor
	BuildArea();
	~BuildArea();

	// delete Function
	BuildArea(const BuildArea& _Other) = delete;
	BuildArea(BuildArea&& _Other) noexcept = delete;
	BuildArea& operator=(const BuildArea& _Other) = delete;
	BuildArea& operator=(BuildArea&& _Other) noexcept = delete;

	static std::shared_ptr<BuildArea> CreateBuildArea(class GameEngineLevel* _Level, const float4& _ActorPos);
	void ReleaseChildTower();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;
	std::shared_ptr<class GameEngineSpriteRenderer> BuildAreaRenderer = nullptr;
	float4 RenderScale = {128,128};
	
	std::shared_ptr<class GameEngineCollision> BuildAreaCol = nullptr;
	float4 ColScale = { 105,60 };

	std::shared_ptr<class BaseTower> ChildTower = nullptr;

	bool IsAreaClick();
};
// �̰� �������� ���߿� �ǹ����� �̹����� ��������.
// Ÿ���� �ٴ��� ������ �߽��ΰ� �Ǵٰ� �ϱ�� �Ѱž�