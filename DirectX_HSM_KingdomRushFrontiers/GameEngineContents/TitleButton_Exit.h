#pragma once
#include "ContentsButton.h"

class TitleButton_Exit : public ContentsButton
{
public:
	// construtor destructor
	TitleButton_Exit();
	~TitleButton_Exit();

	// delete Function
	TitleButton_Exit(const TitleButton_Exit& _Other) = delete;
	TitleButton_Exit(TitleButton_Exit&& _Other) noexcept = delete;
	TitleButton_Exit& operator=(const TitleButton_Exit& _Other) = delete;
	TitleButton_Exit& operator=(TitleButton_Exit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

