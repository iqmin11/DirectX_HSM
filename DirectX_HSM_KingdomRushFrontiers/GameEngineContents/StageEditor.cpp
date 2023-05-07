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
    ParentLevel = StageEditLevel::MainStageEditLevel;
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
                    Points[i]->GetTransform()->SetLocalScale({20.0f, 20.0f, 20.0f});
                    Points[i]->GetTransform()->SetLocalPosition(Line[i]);
                }
            }
        }
    }

    
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
        
        ChangeStage(SelectedStage);

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
        if (ImGui::Button("Revert"))
        {
        }
        ImGui::SameLine();
        if (ImGui::Button("Save"))
        {
        }
        ImGui::EndGroup();
    }
}

void StageEditor::ChangeStage(int _Selected)
{
    ImGui::Text("Stage %d", _Selected);
    ParentLevel->SetStageLevel(_Selected);
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
    if (Data[SelectedStage].Lines.size() == 0)
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
