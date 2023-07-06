#include "PrecompileHeader.h"
#include "WorldMapFlagManager.h"

#include <GameEnginePlatform\GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include "WorldMapFlag.h"
#include "PathDot.h"

WorldMapFlagManager::WorldMapFlagManager()
{

}

WorldMapFlagManager::~WorldMapFlagManager()
{

}

void WorldMapFlagManager::OnStage(int _Index)
{
	if (_Index < 0 || _Index > 5)
	{
		MsgAssert("½ºÅ×ÀÌÁö ÀÎµ¦½º¸¦ ¹þ¾î³µ½À´Ï´Ù.")
	}
	//Flags[_Index]->On();
	if (_Index == 0)
	{
		Flags[0]->On();
	}
	else
	{
		WorldMapPath[_Index - 1][0]->On();
	}
}

void WorldMapFlagManager::Start()
{
	SetFlagPosData();
	SetFlag();
	SetPathPosData();
	SetPathDot();
}

void WorldMapFlagManager::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("Z"))
	{
		static int a = 0;
		OnStage(a++);
	}
}

float4 WorldMapFlagManager::WinToDec(const float4& _Win)
{
	return float4{ _Win.x - GameEngineWindow::GetScreenSize().hx(), GameEngineWindow::GetScreenSize().hy() - _Win.y};
}

void WorldMapFlagManager::SetFlagPosData()
{
	FlagPosData.reserve(6);
	FlagPosData.push_back(WinToDec({ 256,287 }));
	FlagPosData.push_back(WinToDec({ 388,305 }));
	FlagPosData.push_back(WinToDec({ 374,398 }));
	FlagPosData.push_back(WinToDec({ 279,435 }));
	FlagPosData.push_back(WinToDec({ 230,570 }));
	FlagPosData.push_back(WinToDec({ 533,733 }));
}

void WorldMapFlagManager::SetFlag()
{
	Flags.reserve(6);
	for (size_t i = 0; i < Flags.capacity(); i++)
	{
		Flags.push_back(WorldMapFlag::CreateFlag(this, []()
			{

			}));
		Flags[i]->GetTransform()->SetLocalPosition(FlagPosData[i]);
	}
}

void WorldMapFlagManager::SetPathPosData()
{
	PathDotPosData.resize(5);
	PathDotPosData[0].reserve(8);
	PathDotPosData[0].push_back(WinToDec({274,277}));
	PathDotPosData[0].push_back(WinToDec({290,269}));
	PathDotPosData[0].push_back(WinToDec({305,264}));
	PathDotPosData[0].push_back(WinToDec({321,260}));
	PathDotPosData[0].push_back(WinToDec({337,265}));
	PathDotPosData[0].push_back(WinToDec({353,271}));
	PathDotPosData[0].push_back(WinToDec({368,277}));
	PathDotPosData[0].push_back(WinToDec({377,291}));

	PathDotPosData[1].reserve(7);
	PathDotPosData[1].push_back(WinToDec({400,318}));
	PathDotPosData[1].push_back(WinToDec({411,328}));
	PathDotPosData[1].push_back(WinToDec({415,342}));
	PathDotPosData[1].push_back(WinToDec({415,356}));
	PathDotPosData[1].push_back(WinToDec({415,369}));
	PathDotPosData[1].push_back(WinToDec({407,382}));
	PathDotPosData[1].push_back(WinToDec({392,392}));

	PathDotPosData[2].reserve(4);
	PathDotPosData[2].push_back(WinToDec({352,405}));
	PathDotPosData[2].push_back(WinToDec({336,415}));
	PathDotPosData[2].push_back(WinToDec({320,420}));
	PathDotPosData[2].push_back(WinToDec({299,425}));

	PathDotPosData[3].reserve(8);
	PathDotPosData[3].push_back(WinToDec({261,448}));
	PathDotPosData[3].push_back(WinToDec({249,462}));
	PathDotPosData[3].push_back(WinToDec({243,476}));
	PathDotPosData[3].push_back(WinToDec({239,490}));
	PathDotPosData[3].push_back(WinToDec({235,508}));
	PathDotPosData[3].push_back(WinToDec({233,521}));
	PathDotPosData[3].push_back(WinToDec({232,539}));
	PathDotPosData[3].push_back(WinToDec({231,555}));

	PathDotPosData[4].reserve(24);
	PathDotPosData[4].push_back(WinToDec({222,606}));
	PathDotPosData[4].push_back(WinToDec({221,619}));
	PathDotPosData[4].push_back(WinToDec({220,634}));
	PathDotPosData[4].push_back(WinToDec({218,649}));
	PathDotPosData[4].push_back(WinToDec({216,663}));
	PathDotPosData[4].push_back(WinToDec({213,677}));
	PathDotPosData[4].push_back(WinToDec({213,692}));
	PathDotPosData[4].push_back(WinToDec({218,708}));
	PathDotPosData[4].push_back(WinToDec({228,721}));
	PathDotPosData[4].push_back(WinToDec({241,733}));
	PathDotPosData[4].push_back(WinToDec({257,743}));
	PathDotPosData[4].push_back(WinToDec({273,752}));
	PathDotPosData[4].push_back(WinToDec({290,759}));
	PathDotPosData[4].push_back(WinToDec({310,765}));
	PathDotPosData[4].push_back(WinToDec({328,769}));
	PathDotPosData[4].push_back(WinToDec({349,772}));
	PathDotPosData[4].push_back(WinToDec({369,772}));
	PathDotPosData[4].push_back(WinToDec({398,772}));
	PathDotPosData[4].push_back(WinToDec({427,768}));
	PathDotPosData[4].push_back(WinToDec({446,762}));
	PathDotPosData[4].push_back(WinToDec({464,756}));
	PathDotPosData[4].push_back(WinToDec({480,752}));
	PathDotPosData[4].push_back(WinToDec({498,747}));
	PathDotPosData[4].push_back(WinToDec({516,740}));
}

void WorldMapFlagManager::SetPathDot()
{
	WorldMapPath.resize(5);
	WorldMapPath[0].reserve(8);
	SetOnePathDot(0);

	WorldMapPath[1].reserve(7);
	SetOnePathDot(1);

	WorldMapPath[2].reserve(4);
	SetOnePathDot(2);

	WorldMapPath[3].reserve(8);
	SetOnePathDot(3);

	WorldMapPath[4].reserve(24);
	SetOnePathDot(4);
}

void WorldMapFlagManager::SetOnePathDot(int _Index)
{
	for (size_t i = 0; i < WorldMapPath[_Index].capacity(); i++)
	{
		if (_Index == 4 && i <= 17)
		{
			WorldMapPath[_Index].push_back(PathDot::CreatPathDot(this, "Blue"));
		}
		else
		{
			WorldMapPath[_Index].push_back(PathDot::CreatPathDot(this, "Red"));
		}
		WorldMapPath[_Index][i]->GetTransform()->SetWorldPosition(PathDotPosData[_Index][i]);
	}

	for (size_t i = 0; i < WorldMapPath[_Index].size(); i++)
	{
		if (i == WorldMapPath[_Index].size() - 1)
		{
			WorldMapPath[_Index][i]->SetNextActor(Flags[_Index + 1].get());
		}
		else
		{
			WorldMapPath[_Index][i]->SetNextActor(WorldMapPath[_Index][i + 1].get());
		}
	}
}
