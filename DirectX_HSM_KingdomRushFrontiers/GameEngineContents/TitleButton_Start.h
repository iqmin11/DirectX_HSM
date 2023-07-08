#pragma once
#include "ContentsButton.h"

class TitleButton_Start : public ContentsButton
{
public:
	// construtor destructor
	TitleButton_Start();
	~TitleButton_Start();

	// delete Function
	TitleButton_Start(const TitleButton_Start& _Other) = delete;
	TitleButton_Start(TitleButton_Start&& _Other) noexcept = delete;
	TitleButton_Start& operator=(const TitleButton_Start& _Other) = delete;
	TitleButton_Start& operator=(TitleButton_Start&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

