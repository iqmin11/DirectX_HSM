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

void StageEditor::OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime)
{
	//const char8_t* Ptr = u8"배경이 뭐냐";
	//const char* Text = reinterpret_cast<const char*>(Ptr);
	//ImGui::Text(Text);

	//const char8_t* Ptr = u8"배경 이미지 이름";
	//const char* Text = reinterpret_cast<const char*>(Ptr);
	//char Arr[100] = {0};
	//ImGui::InputText(Text, Arr, 100);
    {
        ImGui::BeginChild("left pane", ImVec2(150, 0), true);
        for (int i = 1; i <= 6; i++)
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
            float4 MousePosition = float4{ 1,-1,1,1 } *(GameEngineWindow::GetMousePosition() - GameEngineWindow::GetScreenSize().half());
            Data[0].Lines[SelectedLine].Points.emplace_back(MousePosition);
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





    // 

    // ImGui::()
}

void StageEditor::ChangeStage(int _Selected)
{
    ImGui::Text("Stage %d", _Selected);
    ParentLevel->SetStageLevel(_Selected);
    //ChangeStageInLevel(_Selected);
}

void StageEditor::ButtonCheck_AddPath()
{
    if (ImGui::Button("AddPath"))
    {
        Data[0].Lines.push_back(LinePath());
    }
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
        ButtonCheck_AddPath();
        {
            ImGui::BeginChild("left pane", ImVec2(150, 0), true);
            for (int i = 0; i < Data[0].Lines.size(); i++)
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

        if (Data[0].Lines.size() > 0)
        {
            ImGui::BeginChild("left pane", ImVec2(150, 0), true);
            for (int i = 0; i < Data[0].Lines[SelectedLine].Points.size(); i++)
            {
                // FIXME: Good candidate to use ImGuiSelectableFlags_SelectOnNav
                char label[128];
                sprintf_s(label, "Point %d", i);
                ImGui::Text(label);
                //if (ImGui::Selectable(label, selectedPoint == i))
                //    selectedPoint = i;
            }
            ImGui::EndChild();
            ImGui::SameLine();
            //if (true == PathEditMode)
            //{
            //    if (ImGui::Button("EditModeOn"))
            //    {
            //        PathEditMode = false;
            //    }
            //}
            //else
            //{
            //    if (ImGui::Button("EditModeOff"))
            //    {
            //        PathEditMode = true;
            //    }
            //}
        }
    }
}
