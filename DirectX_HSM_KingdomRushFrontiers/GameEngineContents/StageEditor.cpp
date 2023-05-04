#include "PrecompileHeader.h"
#include "StageEditor.h"

StageEditor::StageEditor() 
{
}

StageEditor::~StageEditor() 
{
}

class LinePath 
{
	int Index;
	std::vector<float4> Points;
};

class MonsterSpawnData 
{
	int LineIndexs;
	int MonsterIndex;
	float Time;
};

class MonsterWaveData 
{
	std::vector<MonsterSpawnData> Monster;

	//int LineIndexs; // 0번 라인을 타고
	//int MonsterIndex; // 0번 몬스터
	//int MonsterCount; // 10 마리 내놓는데
	//float InterTime; // 2.초마다 Monster를 1마리씩 내보내고 
};

class WaveData
{
	std::vector<MonsterWaveData> MonsterWaves;
};


class MonsterData
{
	int Hp;
	int Speed;
};

//  Monster가 3종류가
// 0번 몬스터
// 1번 몬스터
// 2번 몬스터

class StageData 
{
public:
	std::string BackGroundName;
	// 0번 라인
	// 1번 라인
	std::vector<LinePath> Lines;

	std::vector<WaveData> Waves;

	// Monster0
	// Monster1
	// Monster2
	std::vector<MonsterData> MonsterData;
};

void StageEditor::OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime) 
{
	//const char8_t* Ptr = u8"배경이 뭐냐";
	//const char* Text = reinterpret_cast<const char*>(Ptr);
	//ImGui::Text(Text);

	const char8_t* Ptr = u8"배경 이미지 이름";
	const char* Text = reinterpret_cast<const char*>(Ptr);
	char Arr[100] = {0};
	ImGui::InputText(Text, Arr, 100);



	// 

	// ImGui::()
}