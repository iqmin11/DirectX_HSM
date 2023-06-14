#pragma once
#include "ContentsButton.h"

class RallyButton : public ContentsButton
{
public:
	// construtor destructor
	RallyButton();
	~RallyButton();

	// delete Function
	RallyButton(const RallyButton& _Other) = delete;
	RallyButton(RallyButton&& _Other) noexcept = delete;
	RallyButton& operator=(const RallyButton& _Other) = delete;
	RallyButton& operator=(RallyButton&& _Other) noexcept = delete;

	static std::shared_ptr<RallyButton> CreateButton(class UpgradeTowerUI_ex* _UI);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 Scale = { 47, 42, 1 };

};

