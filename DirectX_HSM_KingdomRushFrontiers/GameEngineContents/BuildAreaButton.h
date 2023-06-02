#pragma once
#include "ContentsButton.h"

class BuildAreaButton : public ContentsButton
{
public:
	// construtor destructor
	BuildAreaButton();
	~BuildAreaButton();

	// delete Function
	BuildAreaButton(const BuildAreaButton& _Other) = delete;
	BuildAreaButton(BuildAreaButton&& _Other) noexcept = delete;
	BuildAreaButton& operator=(const BuildAreaButton& _Other) = delete;
	BuildAreaButton& operator=(BuildAreaButton&& _Other) noexcept = delete;

	static std::shared_ptr<BuildAreaButton> CreateButton(class BuildArea* _ParentArea);

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	float4 Scale = { 101,41,1 };
};

