#include "PrecompileHeader.h"
#include "StageEditor.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "StageEditLevel.h"
#include "BaseMonster.h"


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

static std::vector<std::shared_ptr<GameEngineSpriteRenderer>> PointRenderers;

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
            PathEditTap(_Level);
            WaveEditTap(_Level, _DeltaTime);
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

        if (GameEngineInput::IsDown("Space"))
        {
            PathTest(_Level);
        }
        
        if (IsValidWaveTest)
        {
            UpdateWaveTest(_Level, _DeltaTime);
        }

        ImGui::EndChild();
        
        ImGui::EndGroup();
    }
}

void StageEditor::ChangeStage(std::shared_ptr<class GameEngineLevel> _Level, int _Selected)
{
    ImGui::Text("Stage %d", _Selected);
    std::dynamic_pointer_cast<StageEditLevel>(_Level)->SetStageLevel(_Selected);
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

void StageEditor::PathEditTap(std::shared_ptr<class GameEngineLevel> _Level)
{
    if (static_cast<int>(Data[SelectedStage].Lines.size()) <= SelectedLine)
    {
        SelectedLine = -1;
    }

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
        ImGui::SameLine();
        if (ImGui::Button("LoadPath"))
        {
            LoadPathBinData();
        }
        ImGui::SameLine();
        if (ImGui::Button("SavePath"))
        {
            SavePathBinData();
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
            ImGui::SameLine();
            if (SelectedLine != -1)
            {
                std::vector<float4>& PointVec = Data[SelectedStage].Lines[SelectedLine].Points;
                {
                    ImGui::BeginChild("PathPointWindow", ImVec2(150, 0), true);
                    if (ImGui::Button("PathTest"))
                    {
                        PathTest(_Level);
                    }
                    for (int i = 0; i < PointVec.size(); i++)
                    {
                        int PointX = static_cast<int>(PointVec[i].x);
                        int PointY = static_cast<int>(PointVec[i].y);
                        std::string PointLabel = "Point " + std::to_string(i) + ": " + std::to_string(PointX) + ", " + std::to_string(PointY);
                        ImGui::Text(PointLabel.c_str());
                    }

                    ImGui::EndChild();
                    ImGui::SameLine();
                    
                }
            }
            
        }
        ImGui::EndTabItem();

        
    }
    
}

void StageEditor::Pushback_Path()
{
    Data[SelectedStage].Lines.push_back(LinePath());
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
    if (SelectedLine == -1 || Data[SelectedStage].Lines.size() == 0 || Data[SelectedStage].Lines[SelectedLine].Points.size() == 0)
    {
        return;
    }
    Data[SelectedStage].Lines[SelectedLine].Points.pop_back();
}

void StageEditor::Popback_Path()
{
    if (0 == Data[SelectedStage].Lines.size())
    {
        return;
    }
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
                        PointRenderers.push_back(LineActor->CreateComponent<GameEngineSpriteRenderer>());
                    }
                }

                for (size_t i = 0; i < PointRenderers.size(); i++)
                {
                    if (i < Line.size())
                    {
                        PointRenderers[i]->SetTexture("Check.png");
                        PointRenderers[i]->GetTransform()->SetLocalScale({ 10.0f, 10.0f, 10.0f });
                        PointRenderers[i]->GetTransform()->SetLocalPosition(Line[i]);
                        PointRenderers[i]->On();
                    }
                    else
                    {
                        PointRenderers[i]->Off();
                    }
                }
            }
        }
        else
        {
            for (size_t i = 0; i < PointRenderers.size(); i++)
            {
                PointRenderers[i]->Off();
            }
        }
    }
}

void StageEditor::SerializeOneLine(GameEngineSerializer& _Serializer, int _StageLevel, int _PathIndex)
{
    std::vector<float4>& SavePoints = Data[_StageLevel].Lines[_PathIndex].Points;
    _Serializer.Write(static_cast<int>(SavePoints.size()));
    for (int i = 0; i < SavePoints.size(); i++)
    {
        _Serializer.Write(&SavePoints[i], sizeof(float4));
    }
}

void StageEditor::SerializeOneStageLines(GameEngineSerializer& _Serializer, int _StageLevel)
{
    std::vector<LinePath>& SaveLines = Data[_StageLevel].Lines;
    _Serializer.Write(static_cast<int>(SaveLines.size()));
    for (int i = 0; i < SaveLines.size(); i++)
    {
        //_Serializer.Write(SaveLines[i].Index);
        SerializeOneLine(_Serializer, _StageLevel, i);
    }
}

void StageEditor::SerializeAllPathData(GameEngineSerializer& _Serializer)
{
    _Serializer.Write(static_cast<int>(Data.size()));
    for (int i = 0; i < Data.size(); i++)
    {
        //PathsSavedBinData.Write(&Data[i].Lines, sizeof(std::vector<LinePath>));
        SerializeOneStageLines(_Serializer, i);
    }
}

void StageEditor::SavePathBinData()
{
    GameEngineSerializer SaveSerializer = GameEngineSerializer();

    SerializeAllPathData(SaveSerializer);

    GameEnginePath filepath;
    filepath.SetPath("..//ContentsData//PathData.txt");

    GameEngineFile file = GameEngineFile(filepath.GetFullPath());
    file.SaveBin(SaveSerializer);
}

void StageEditor::LoadPathBinData()
{
    GameEngineSerializer LoadSerializer = GameEngineSerializer();

    GameEngineFile File("..//ContentsData//PathData.txt");
    LoadSerializer.BufferResize(8000);
    File.LoadBin(LoadSerializer);

    int StgSize = 0;
    LoadSerializer.Read(StgSize);

    StageCount = StgSize;
    Data.resize(StageCount);
    for (int i = 0; i < Data.size(); i++)
    {
        LoadOneStageLines(LoadSerializer, i);
    }
}

void StageEditor::LoadOneStageLines(GameEngineSerializer& _Serializer, int _StageLevel)
{
    int LineSize = 0;
    _Serializer.Read(LineSize);
    Data[_StageLevel].Lines.resize(LineSize);
    for (int i = 0; i < Data[_StageLevel].Lines.size(); i++)
    {
        //_Serializer.Read(&Data[_StageLevel].Lines[i].Index, sizeof(int));
        LoadOneLine(_Serializer, _StageLevel, i);
    }
}



void StageEditor::LoadOneLine(GameEngineSerializer& _Serializer, int _StageLevel, int _PathIndex)
{
    int PointSize = 0;
    _Serializer.Read(PointSize);
    Data[_StageLevel].Lines[_PathIndex].Points.resize(PointSize);
    for (size_t i = 0; i < Data[_StageLevel].Lines[_PathIndex].Points.size(); i++)
    {
        _Serializer.Read(&Data[_StageLevel].Lines[_PathIndex].Points[i], sizeof(float4));
    }
}

void StageEditor::WaveEditTap(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime)
{
    StageData& Stage = Data[SelectedStage];
    if (Stage.Lines.size() != 0)
    {
        if (ImGui::BeginTabItem("WaveEdit"))
        {
            if (ImGui::Button("AddWave"))
            {
                Pushback_Wave();
            }

            ImGui::SameLine();
            if (ImGui::Button("DeleteWave"))
            {
                Popback_Wave();
            }
            ImGui::SameLine();

            if (ImGui::Button("LoadWave"))
            {
                LoadWaveBinData();
            }
            ImGui::SameLine();
            if (ImGui::Button("SaveWave"))
            {
                SaveWaveBinData();
            }

            {
                ImGui::BeginChild("Wave Select", ImVec2(150, 0), true);
                for (int i = 0; i < Stage.Waves.size(); i++)
                {
                    // FIXME: Good candidate to use ImGuiSelectableFlags_SelectOnNav
                    char label[128];
                    sprintf_s(label, "Wave %d", i);
                    if (ImGui::Selectable(label, SelectedWave == i))
                        SelectedWave = i;
                }
                ImGui::EndChild();

            }
            
            ImGui::EndTabItem();
            ImGui::SameLine();

            if (SelectedWave != -1 && SelectedWave < Stage.Waves.size())
            {
                ImGui::BeginChild("SetMonsterSpawn", ImVec2(200, 0), true);

                ImGui::Combo("Monster", &SelectedWaveMonster, "DesertThug\0DuneRaider\0DesertArcher\0SandHound\0WarHound\0Immortal\0Fallen\0Executioner\0GiantScorpion\0GiantWasp\0GiantWaspQueen\0DuneTerror\0SandWraith\0");
                const char* LineList[] = { "Line0", "Line1", "Line2", "Line3", "Line4", "Line5", "Line6", "Line7", "Line8", "Line9", "Line10" };
                const char* combo_preview_value = LineList[SelectedWaveLineIndex];
                if (ImGui::BeginCombo("Line", combo_preview_value, ImGuiComboFlags_None))
                {
                    for (int n = 0; n < Stage.Lines.size(); n++)
                    {
                        const bool is_selected = (SelectedWaveLineIndex == n);
                        if (ImGui::Selectable(LineList[n], is_selected))
                            SelectedWaveLineIndex = n;

                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
                ImGui::InputFloat("Time", &StartTimeInWave);
                if (ImGui::Button("AddSpawnData"))
                {
                    Pushback_MonsterSpawnData(static_cast<MonsterEnum>(SelectedWaveMonster), SelectedWaveLineIndex, StartTimeInWave);
                }
                if (ImGui::Button("DeleteSpawnData"))
                {
                    Popback_MonsterSpawnData();
                }
                ImGui::EndChild();
                ImGui::SameLine();
                if (Stage.Waves.size() > 0)
                {
                    std::vector<MonsterSpawnData>& LocalMonsterSpawnData = Stage.Waves[SelectedWave].MonsterSpawn;
                    if (LocalMonsterSpawnData.size() > 0)
                    {
                        ImGui::BeginChild("MonsterSpawnView", ImVec2(150, 0), true);
                        if (!IsValidWaveTest)
                        {
                            if (ImGui::Button("WaveTest"))
                            {
                                IsValidWaveTest = true;
                            }
                        }
                        else
                        {
                            ImGui::BeginDisabled();
                            if (ImGui::Button("WaveTest")) {}
                            ImGui::EndDisabled();
                        }
                        for (size_t i = 0; i < LocalMonsterSpawnData.size(); i++)
                        {
                            std::string Label = std::to_string(i) + ". " + MonsterEnumToString(LocalMonsterSpawnData[i].Monster);
                            ImGui::Text(Label.c_str());
                            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
                            {
                                Label = "Line : " + std::to_string(LocalMonsterSpawnData[i].LineIndex) + "\n" +
                                    "StartTime : " + std::to_string(LocalMonsterSpawnData[i].StartTime);
                                ImGui::BeginTooltip();
                                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                                ImGui::TextUnformatted(Label.c_str());
                                ImGui::PopTextWrapPos();
                                ImGui::EndTooltip();
                            }
                        }

                        ImGui::EndChild();
                        ImGui::SameLine();
                    }
                }
            }
            
        }
    }

}

void StageEditor::Pushback_Wave()
{
    Data[SelectedStage].Waves.push_back(WaveData());
}

void StageEditor::Popback_Wave()
{
    std::vector<WaveData>& LocalWave = Data[SelectedStage].Waves;
    if (0 == LocalWave.size())
    {
        return;
    }
    SelectedWave = -1;
    LocalWave.pop_back();
}

void StageEditor::PathTest(std::shared_ptr<class GameEngineLevel> _Level)
{
    if (SelectedLine == -1)
    {
        return;
    }
    
    BaseMonster::CreateMonster(_Level, MonsterEnum::DuneRaider, Data[SelectedStage].Lines[SelectedLine].Points);
    //_Level->CreateActor<DuneRaider>()->SetPathInfo(Data[SelectedStage].Lines[SelectedLine].Points);
}

void StageEditor::Pushback_MonsterSpawnData(MonsterEnum _Monster, int _LineIndex, float _StartTime)
{
    Data[SelectedStage].Waves[SelectedWave].MonsterSpawn.emplace_back(_Monster, _LineIndex, _StartTime);
}

void StageEditor::Popback_MonsterSpawnData()
{
    std::vector<MonsterSpawnData>& LocalSpawnData = Data[SelectedStage].Waves[SelectedWave].MonsterSpawn;
    if (0 == LocalSpawnData.size())
    {
        return;
    }
    Data[SelectedStage].Waves[SelectedWave].MonsterSpawn.pop_back();
}

std::string StageEditor::MonsterEnumToString(MonsterEnum _Monster)
{
    switch (_Monster)
    {
    case MonsterEnum::Null:
        break;
    case MonsterEnum::DesertThug:
        return "DesertThug";
        break;
    case MonsterEnum::DuneRaider:
        return "DuneRaider";
        break;
    case MonsterEnum::DesertArcher:
        return "DesertArcher";
        break;
    case MonsterEnum::SandHound:
        return "SandHound";
        break;
    case MonsterEnum::WarHound:
        return "WarHound";
        break;
    case MonsterEnum::Immortal:
        return "Immortal";
        break;
    case MonsterEnum::Fallen:
        return "Fallen";
        break;
    case MonsterEnum::Executioner:
        return "Executioner";
        break;
    case MonsterEnum::GiantScorpion:
        return "GiantScorpion";
        break;
    case MonsterEnum::GiantWasp:
        return "GiantWasp";
        break;
    case MonsterEnum::GiantWaspQueen:
        return "GiantWaspQueen";
        break;
    case MonsterEnum::DuneTerror:
        return "DuneTerror";
        break;
    case MonsterEnum::SandWraith:
        return "SandWraith";
        break;
    default:
        break;
    }
    return "\0";
}

void StageEditor::SerializeOneWaveData(GameEngineSerializer& _Serializer, int _StageLevel, int _WaveIndex)
{
    std::vector<MonsterSpawnData>& LocalData = Data[_StageLevel].Waves[_WaveIndex].MonsterSpawn;
    _Serializer.Write(static_cast<int>(LocalData.size()));
    for (size_t i = 0; i < LocalData.size(); i++)
    {
        _Serializer.Write(&LocalData[i].Monster, sizeof(MonsterEnum));
        _Serializer.Write(LocalData[i].LineIndex);
        _Serializer.Write(&LocalData[i].StartTime, sizeof(float));
    }
}

void StageEditor::SerializeOneStageWave(GameEngineSerializer& _Serializer, int _StageLevel)
{
    std::vector<WaveData>& LocalData = Data[_StageLevel].Waves;
    _Serializer.Write(static_cast<int>(LocalData.size()));
    for (int i = 0; i < LocalData.size(); i++)
    {
        SerializeOneWaveData(_Serializer, _StageLevel, i);
    }
}

void StageEditor::SerializeAllWaveData(GameEngineSerializer& _Serializer)
{
    _Serializer.Write(static_cast<int>(Data.size()));
    for (int i = 0; i < Data.size(); i++)
    {
        SerializeOneStageWave(_Serializer, i);
    }
}

void StageEditor::SaveWaveBinData()
{
    GameEngineSerializer SaveSerializer = GameEngineSerializer();
    SerializeAllWaveData(SaveSerializer);

    GameEnginePath filepath;
    filepath.SetPath("..//ContentsData//WaveData.txt");

    GameEngineFile file = GameEngineFile(filepath.GetFullPath());
    file.SaveBin(SaveSerializer);
}

void StageEditor::LoadWaveBinData()
{
    GameEngineSerializer LoadSerializer = GameEngineSerializer();

    GameEngineFile File("..//ContentsData//WaveData.txt");
    LoadSerializer.BufferResize(8000);
    File.LoadBin(LoadSerializer);

    int StgSize = 0;
    LoadSerializer.Read(StgSize);

    StageCount = StgSize;
    Data.resize(StageCount);
    for (int i = 0; i < Data.size(); i++)
    {
        LoadOneStageWave(LoadSerializer, i);
    }
}

void StageEditor::LoadOneStageWave(GameEngineSerializer& _Serializer, int _StageLevel)
{
    int WaveSize = 0;
    _Serializer.Read(WaveSize);
    Data[_StageLevel].Waves.resize(WaveSize);
    for (int i = 0; i < Data[_StageLevel].Waves.size(); i++)
    {
        LoadOneWave(_Serializer, _StageLevel, i);
    }
}

void StageEditor::LoadOneWave(GameEngineSerializer& _Serializer, int _StageLevel, int _WaveIndex)
{
    int MonsterSpawnDataSize = 0;
    _Serializer.Read(MonsterSpawnDataSize);
    std::vector<MonsterSpawnData>& LocalData = Data[_StageLevel].Waves[_WaveIndex].MonsterSpawn;
    LocalData.resize(MonsterSpawnDataSize);
    for (size_t i = 0; i < LocalData.size(); i++)
    {
        _Serializer.Read(&LocalData[i].Monster, sizeof(MonsterEnum));
        _Serializer.Read(LocalData[i].LineIndex);
        _Serializer.Read(&LocalData[i].StartTime, sizeof(float));
    }
}

void StageEditor::UpdateWaveTest(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime)
{
    WaveTestTime += _DeltaTime;
    static std::list<MonsterSpawnData> SpawnList = std::list<MonsterSpawnData>();
    if (SpawnList.size() <= 0)
    {
        std::vector<MonsterSpawnData>& SpawnVecRef = Data[SelectedStage].Waves[SelectedWave].MonsterSpawn;
        std::copy(SpawnVecRef.begin(), SpawnVecRef.end(), std::back_inserter(SpawnList));
    }

    auto StartIter = SpawnList.begin();
    auto EndIter = SpawnList.end();
    for (; StartIter != EndIter; )
    {
        if (StartIter->StartTime <= WaveTestTime)
        {
            BaseMonster::CreateMonster(_Level, StartIter->Monster, Data[SelectedStage].Lines[StartIter->LineIndex].Points);
            StartIter = SpawnList.erase(StartIter);
            if (SpawnList.size() == 0)
            {
                IsValidWaveTest = false;
                WaveTestTime = 0;
                return;
            }
            continue;
        }
        ++StartIter;
    }

}

