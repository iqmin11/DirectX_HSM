#include "PrecompileHeader.h"
#include "PathEdit.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

PathEdit::PathEdit()
{

}

PathEdit::~PathEdit()
{

}

void PathEdit::Start()
{
	MapRenderer.reserve(6);
	for (size_t i = 0; i < MapRenderer.capacity(); i++)
	{
		MapRenderer.emplace_back();
		MapRenderer[i] = CreateComponent<GameEngineSpriteRenderer>();
		MapRenderer[i]->SetPipeLine("2DTexture");
		MapRenderer[i]->SetTexture("Stage_" + std::to_string(i + 1) + ".png");
		MapRenderer[i]->GetTransform()->SetWorldScale(MapRendererScale);
	}

	NumRenderer.resize(2);
	for (size_t i = 0; i < NumRenderer.size(); i++)
	{
		NumRenderer[i].resize(10);
	}

	for (size_t i = 0; i < NumRenderer.size(); i++)
	{
		for (size_t j = 0; j < NumRenderer[i].size(); j++)
		{
			NumRenderer[i][j] = CreateComponent<GameEngineSpriteRenderer>();
			NumRenderer[i][j]->SetPipeLine("2DTexture");
			NumRenderer[i][j]->SetTexture("Num" + std::to_string(j) + ".png");
			NumRenderer[i][j]->GetTransform()->SetWorldPosition({ 600 + static_cast<float>(i) * 38,300 });
			NumRenderer[i][j]->GetTransform()->SetWorldScale({ 38,51 });
			NumRenderer[i][j]->Off();
		}
	}

	ChangeState(StageStateValue);
}

void PathEdit::Update(float _DeltaTime)
{
}

void PathEdit::Render(float _DeltaTime)
{
	IndexToNumRenderer();

	if (GameEngineInput::IsDown("LeftArrow"))
	{
		PrevState();
	}

	if (GameEngineInput::IsDown("RightArrow"))
	{
		NextState();
	}

	if (GameEngineInput::IsDown("UpArrow"))
	{
		IncreasPathIndex();
	}

	if (GameEngineInput::IsDown("DownArrow"))
	{
		ReducePathIndex();
	}

	if (GameEngineInput::IsDown("Z"))
	{
		InsertOrFindPath();
	}

	if (GameEngineInput::IsUp("RightClick"))
	{
		PushbackPathPoint();
	}

	if (GameEngineInput::IsDown("Enter"))
	{
		SaveData();
	}


}

void PathEdit::StateToMapRenderer()
{
	for (size_t i = 0; i < MapRenderer.size(); i++)
	{
		if (static_cast<size_t>(StageStateValue) != i)
		{
			MapRenderer[i]->Off();
		}
		else
		{
			MapRenderer[i]->On();
		}
	}
}

void PathEdit::StageStateToDesc()
{
	Desc.Stage = static_cast<int>(StageStateValue) + 1;
	//Desc.ImageFileName = "Stage_" + std::to_string(Desc.Stage) + ".png";
}

void PathEdit::NextState()
{
	int i = static_cast<int>(StageStateValue);
	++i;
	if (5 < i)
	{
		i = 0;
	}
	StageStateValue = static_cast<StageState>(i);
	ChangeState(StageStateValue);
}

void PathEdit::PrevState()
{
	int i = static_cast<int>(StageStateValue);
	--i;
	if (0 > i)
	{
		i = 5;
	}
	StageStateValue = static_cast<StageState>(i);
	ChangeState(StageStateValue);
}

void PathEdit::ChangeState(StageState _Value)
{
	StageStateValue = _Value;
	StateToMapRenderer();
	StageStateToDesc();
}

void PathEdit::IncreasPathIndex()
{
	if (PathIndex == 99)
	{
		return;
	}

	PathIndex++;
}

void PathEdit::ReducePathIndex()
{
	if (PathIndex == 0)
	{
		return;
	}
	PathIndex--;
}

void PathEdit::IndexToNumRenderer()
{
	std::vector Num = GameEngineMath::GetDigits(PathIndex);


	if (Num.size() == 1)
	{
		for (size_t i = 0; i < NumRenderer[1].size(); i++)
		{
			if (i == Num[0])
			{
				NumRenderer[1][i]->On();
			}
			else
			{
				NumRenderer[1][i]->Off();
			}
		}

		for (size_t i = 0; i < NumRenderer[0].size(); i++)
		{
			if (i == 0)
			{
				NumRenderer[0][i]->On();
			}
			else
			{
				NumRenderer[0][i]->Off();
			}
		}
	}
	else
	{
		for (size_t i = 0; i < NumRenderer[0].size(); i++)
		{
			if (i == Num[0])
			{
				NumRenderer[0][i]->On();
			}
			else
			{
				NumRenderer[0][i]->Off();
			}
		}

		for (size_t i = 0; i < NumRenderer[1].size(); i++)
		{
			if (i == Num[1])
			{
				NumRenderer[1][i]->On();
			}
			else
			{
				NumRenderer[1][i]->Off();
			}
		}
	}
}

void PathEdit::InsertOrFindPath()
{
	Desc.MonsterPaths[PathIndex];
}

void PathEdit::PushbackPathPoint()
{
	if (Desc.MonsterPaths.find(PathIndex) == Desc.MonsterPaths.end())
	{
		MsgTextBox("경로를 넣을 메모리가 없습니다. Z를 눌러 메모리를 추가해주세요")
			return;
	}

	float4 MousePosition = float4{ 1,-1,1,1 } *(GameEngineWindow::GetMousePosition() - GameEngineWindow::GetScreenSize().half());
	PathPoint& AddedPathPoint = Desc.MonsterPaths.find(PathIndex)->second.emplace_back();
	AddedPathPoint.Position = MousePosition;
	AddedPathPoint.Renderer = CreateComponent<GameEngineSpriteRenderer>();
	AddedPathPoint.Renderer->SetPipeLine("2DTexture");
	AddedPathPoint.Renderer->SetTexture("Check.png");
	AddedPathPoint.Renderer->GetTransform()->SetWorldScale({ 10,10 });
	AddedPathPoint.Renderer->GetTransform()->SetWorldPosition(MousePosition);
}

void PathEdit::SaveData()
{
	for (auto& i : Desc.MonsterPaths)
	{
		SaveMapData.Write(static_cast<const int>(i.second.size()));
		for (auto& j : i.second)
		{
			SaveMapData.Write(&j.Position, sizeof(float4));
		}
	}
	
	//SaveMonsterPath.Write(static_cast<int>(Desc.MonsterPaths.find(PathIndex)->second.size()));
	//for (auto i : MonsterPaths.find(PathIndex)->second)
	//{
	//	SaveMapData.Write(&i.Position, sizeof(float4));
	//}

	GameEnginePath filepath;
	filepath.SetPath("..//ContentsData//Stage" + std::to_string(Desc.Stage) + "PathData.txt");

	GameEngineFile file = GameEngineFile(filepath.GetFullPath());
	file.SaveBin(SaveMapData);
}


