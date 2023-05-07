#include "PrecompileHeader.h"
#include "StageEditor.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "StageEditLevel.h"


StageEditor::StageEditor() 
{
}

StageEditor::~StageEditor() 
{
}

void StageEditor::Start()
{
    Data.resize(StageCount);
    //ParentLevel = StageEditLevel::MainStageEditLevel;
    //AddStageLine = std::bind(&StagePath::AddStageLine, ParentLevel->GetAcStagePath());
}

static std::vector<std::shared_ptr<GameEngineSpriteRenderer>> Points;

void StageEditor::OnGUI(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime)
{
	//const char8_t* Ptr = u8"배경이 뭐냐";
	//const char* Text = reinterpret_cast<const char*>(Ptr);
	//ImGui::Text(Text);

	//const char8_t* Ptr = u8"배경 이미지 이름";
	//const char* Text = reinterpret_cast<const char*>(Ptr);
	//char Arr[100] = {0};
	//ImGui::InputText(Text, Arr, 100);

    DrawPointRenderer(_Level);
    
    {
        ImGui::BeginChild("left pane", ImVec2(150, 0), true);
        for (int i = 0; i < 6; i++)
        {
            // FIXME: Good candidate to use ImGuiSelectableFlags_SelectOnNav
            char label[128];
            sprintf_s(label, "Stage %d", i);
            if (ImGui::Selectable(label, SelectedStage == i))
                SelectedStage = i;
        }
        ImGui::EndChild();
    }
    ImGui::SameLine();

    // Right
    {
        ImGui::BeginGroup();
        ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
        
        ChangeStage(_Level, SelectedStage);

        ImGui::Separator();
        
        if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
        {
            StageMapBgTap();
            PathEditTap();
            ImGui::EndTabBar();
        }

        if ((GameEngineInput::IsDown("LeftClick") && GameEngineInput::IsPress("Z")))
        {
            Pushback_Point();
        }

        if ((GameEngineInput::IsDown("RightClick") && GameEngineInput::IsPress("Z")))
        {
            Popback_Point();
        }

        ImGui::EndChild();
        if (ImGui::Button("Load"))
        {
            //LoadPathBinData();
        }
        ImGui::SameLine();
        if (ImGui::Button("Save"))
        {
            SerializeAllPathData();
            SavePathBinData();
        }
        ImGui::EndGroup();
    }
}

void StageEditor::ChangeStage(std::shared_ptr<class GameEngineLevel> _Level, int _Selected)
{
    ImGui::Text("Stage %d", _Selected);
    std::dynamic_pointer_cast<StageEditLevel>(_Level)->SetStageLevel(_Selected);
    //ChangeStageInLevel(_Selected);
}
void StageEditor::StageMapBgTap()
{
    if (ImGui::BeginTabItem("StageMapBg"))
    {
        //ParentLevel->SetEditMod(StageEditMode::Null);
        ImGui::Text("TextureFile : Stage_%d.png", SelectedStage);
        ImGui::EndTabItem();
    }
}

void StageEditor::PathEditTap()
{
    if (ImGui::BeginTabItem("PathEdit"))
    {
        if (ImGui::Button("AddPath"))
        {
            Pushback_Path();
        }
        
        ImGui::SameLine();
        if (ImGui::Button("DeletePath"))
        {
            Popback_Path();
        }

        {
            ImGui::BeginChild("left pane", ImVec2(150, 0), true);
            for (int i = 0; i < Data[SelectedStage].Lines.size(); i++)
            {
                // FIXME: Good candidate to use ImGuiSelectableFlags_SelectOnNav
                char label[128];
                sprintf_s(label, "Line %d", i);
                if (ImGui::Selectable(label, SelectedLine == i))
                    SelectedLine = i;
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();
        ImGui::EndTabItem();

        if (SelectedLine != -1)
        {
            std::vector<float4>& PointVec = Data[SelectedStage].Lines[SelectedLine].Points;
            {
                ImGui::BeginChild("left pane", ImVec2(150, 0), true);
                for (int i = 0; i < PointVec.size(); i++)
                {
                    int PointX = static_cast<int>(PointVec[i].x);
                    int PointY = static_cast<int>(PointVec[i].y);
                    std::string PointLabel = "Point " + std::to_string(i) + ": " + std::to_string(PointX) + ", " + std::to_string(PointY);
                    ImGui::Text(PointLabel.c_str());
                }
                ImGui::EndChild();
            }
            ImGui::SameLine();
        }
    }
}

void StageEditor::Pushback_Path()
{
    Data[SelectedStage].Lines.push_back(LinePath(LineSize++));
}

void StageEditor::Pushback_Point()
{
    if (Data[SelectedStage].Lines.size() == 0 || SelectedLine == -1)
    {
        return;
    }
    float4 MousePosition = float4{ 1,-1,1,1 } *(GameEngineWindow::GetMousePosition() - GameEngineWindow::GetScreenSize().half());
    Data[SelectedStage].Lines[SelectedLine].Points.emplace_back(MousePosition);

}

void StageEditor::Popback_Point()
{
    if (Data[SelectedStage].Lines.size() == 0 || Data[SelectedStage].Lines[SelectedLine].Points.size() == 0)
    {
        return;
    }
    Data[SelectedStage].Lines[SelectedLine].Points.pop_back();
}

void StageEditor::Popback_Path()
{
    if (0 == LineSize)
    {
        return;
    }
    LineSize--;
    SelectedLine = -1;
    Data[SelectedStage].Lines.pop_back();
}

void StageEditor::DrawPointRenderer(std::shared_ptr<class GameEngineLevel> _Level)
{
    if (0 != Data.size() && SelectedStage <= Data.size())
    {
        std::vector<LinePath>& Lines = Data[SelectedStage].Lines;

        if (0 != Lines.size() && SelectedLine <= Lines.size())
        {
            std::vector<float4>& Line = Lines[SelectedLine].Points;

            if (0 != Line.size())
            {
                if (nullptr == LineActor)
                {
                    LineActor = _Level->CreateActor<GameEngineActor>();

                    for (size_t i = 0; i < 100; i++)
                    {
                        Points.push_back(LineActor->CreateComponent<GameEngineSpriteRenderer>());
                    }
                }


                for (size_t i = 0; i < Line.size(); i++)
                {
                    Points[i]->SetTexture("Check.png");
                    Points[i]->GetTransform()->SetLocalScale({ 10.0f, 10.0f, 10.0f });
                    Points[i]->GetTransform()->SetLocalPosition(Line[i]);
                }
            }
        }
    }
}

void StageEditor::SerializeOneLine(int _StageLevel, int _PathIndex)
{
    std::vector<float4>& SavePoints = Data[_StageLevel].Lines[_PathIndex].Points;
    PathsSavedBinData.Write(static_cast<int>(SavePoints.size()));
    for (int i = 0; i < SavePoints.size(); i++)
    {
        PathsSavedBinData.Write(&SavePoints[i], sizeof(float4));
    }
}

void StageEditor::SerializeOneStageLines(int _StageLevel)
{
    std::vector<LinePath>& SaveLines = Data[_StageLevel].Lines;
    PathsSavedBinData.Write(static_cast<int>(SaveLines.size()));
    for (int i = 0; i < SaveLines.size(); i++)
    {
        PathsSavedBinData.Write(SaveLines[i].Index);
        PathsSavedBinData.Write(&SaveLines[i].Points, sizeof(std::vector<float4>));
        SerializeOneLine(_StageLevel, i);
    }
}

void StageEditor::SerializeAllPathData()
{
    PathsSavedBinData.Write(static_cast<int>(Data.size()));
    for (int i = 0; i < Data.size(); i++)
    {
        PathsSavedBinData.Write(&Data[i].Lines, sizeof(std::vector<LinePath>));
        SerializeOneStageLines(i);
    }
}

void StageEditor::SavePathBinData()
{
    GameEnginePath filepath;
    filepath.SetPath("..//ContentsData//PathData.txt");

    GameEngineFile file = GameEngineFile(filepath.GetFullPath());
    file.SaveBin(PathsSavedBinData);
}

//void StageEditor::LoadPathBinData()
//{
//    GameEngineFile File("..//ContentsData//PathData.txt");
//    File.LoadBin(PathsLoadedBinData);
//
//    int StgSize = 0;
//    PathsLoadedBinData.Read(StgSize);
//
//    StageCount = StgSize;
//    Data.resize(StageCount);
//    for (size_t i = 0; i < Data.size(); i++)
//    {
//        PathsLoadedBinData.Read(&Data[i].Lines, sizeof(std::vector<LinePath>));
//        LoadOneStageLines(i);
//    }
//
//  
//}
//
//void StageEditor::LoadOneStageLines(int _StageLevel)
//{
//    int LineSize = 0;
//    PathsLoadedBinData.Read(LineSize);
//    Data[_StageLevel].Lines.resize(LineSize);
//    for (size_t i = 0; i < Data[_StageLevel].Lines.size(); i++)
//    {
//        PathsLoadedBinData.Read(Data[_StageLevel].Lines[i].Index);
//        PathsLoadedBinData.Read(&Data[_StageLevel].Lines[i].Points, sizeof(std::vector<float4>));
//        LoadOneLine(_StageLevel, i);
//    }
//}
//
//void StageEditor::LoadOneLine(int _StageLevel, int _PathIndex)
//{
//    int PointSize = 0;
//    PathsLoadedBinData.Read(PointSize);
//    Data[_StageLevel].Lines[_PathIndex].Points.resize(PointSize);
//    for (size_t i = 0; i < Data[_StageLevel].Lines[_PathIndex].Points.size(); i++)
//    {
//        PathsLoadedBinData.Read(&Data[_StageLevel].Lines[_PathIndex].Points[i], sizeof(float4));
//    }
//}




