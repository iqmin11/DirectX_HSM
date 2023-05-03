#include "PrecompileHeader.h"
#include "MapEdit.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

MapEdit::MapEdit()
{

}

MapEdit::~MapEdit()
{

}

void MapEdit::Start()
{
	MapRenderer.reserve(6);
	for (size_t i = 0; i < MapRenderer.capacity(); i++)
	{
		MapRenderer.emplace_back();
		MapRenderer[i] = CreateComponent<GameEngineSpriteRenderer>();
		MapRenderer[i]->SetPipeLine("2DTexture");
		MapRenderer[i]->SetTexture("Stage_" + std::to_string(i+1) + ".png");
		MapRenderer[i]->GetTransform()->SetWorldScale(MapRendererScale);
	}
	
	//MapRenderer = CreateComponent<GameEngineSpriteRenderer>();
	//MapRenderer->SetPipeLine
	StateToMapRenderer();
}

void MapEdit::Update(float _DeltaTime)
{
}

void MapEdit::Render(float _DeltaTime)
{
	if (GameEngineInput::IsDown("LeftArrow"))
	{
		PrevState();
	}

	if (GameEngineInput::IsDown("RightArrow"))
	{
		NextState();
	}

	if (GameEngineInput::IsDown("Z"))
	{
		PushbackPath();
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

void MapEdit::StateToMapRenderer()
{
	for (size_t i = 0; i < MapRenderer.size(); i++)
	{
		if (static_cast<size_t>(State) != i)
		{
			MapRenderer[i]->Off();
		}
		else
		{
			MapRenderer[i]->On();
		}
	}
}

void MapEdit::NextState()
{
	int i = static_cast<int>(State);
	++i;
	if (5 < i)
	{
		i = 0;
	}
	State = static_cast<StageState>(i);
	StateToMapRenderer();
}

void MapEdit::PrevState()
{
	int i = static_cast<int>(State);
	--i;
	if (0 > i)
	{
		i = 5;
	}
	State = static_cast<StageState>(i);
	StateToMapRenderer();
}

void MapEdit::PushbackPath()
{
	PathIndex++;
	MonsterPaths.insert(std::make_pair(PathIndex, std::list<PathPoint>()));
}

void MapEdit::PushbackPathPoint()
{
	if (MonsterPaths.size() == 0)
	{
		return;
	}

	float4 MousePosition = float4{ 1,-1,1,1 } *(GameEngineWindow::GetMousePosition() - GameEngineWindow::GetScreenSize().half());
	PathPoint& AddedPathPoint = MonsterPaths.find(PathIndex)->second.emplace_back();
	AddedPathPoint.Position = MousePosition;
	AddedPathPoint.Renderer = CreateComponent<GameEngineSpriteRenderer>();
	AddedPathPoint.Renderer->SetPipeLine("2DTexture");
	AddedPathPoint.Renderer->SetTexture("Check.png");
	AddedPathPoint.Renderer->GetTransform()->SetWorldScale({ 10,10 });
	AddedPathPoint.Renderer->GetTransform()->SetWorldPosition(MousePosition);
}

void MapEdit::SaveData()
{
	SaveMonsterPath.Write(static_cast<int>(MonsterPaths.find(PathIndex)->second.size()));

	for (auto i : MonsterPaths.find(PathIndex)->second)
	{
		SaveMonsterPath.Write(&i.Position, sizeof(float4));
	}

	GameEnginePath filepath;
	filepath.SetPath("..//ContentsData//Stage" + std::to_string(static_cast<int>(State)+1) + "MonsterPath" + std::to_string(PathIndex) + ".txt");

	GameEngineFile file = GameEngineFile(filepath.GetFullPath());
	file.SaveBin(SaveMonsterPath);
}


