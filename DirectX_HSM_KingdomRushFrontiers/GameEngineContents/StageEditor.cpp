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

	//int LineIndexs; // 0�� ������ Ÿ��
	//int MonsterIndex; // 0�� ����
	//int MonsterCount; // 10 ���� �����µ�
	//float InterTime; // 2.�ʸ��� Monster�� 1������ �������� 
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

//  Monster�� 3������
// 0�� ����
// 1�� ����
// 2�� ����

class StageData 
{
public:
	std::string BackGroundName;
	// 0�� ����
	// 1�� ����
	std::vector<LinePath> Lines;

	std::vector<WaveData> Waves;

	// Monster0
	// Monster1
	// Monster2
	std::vector<MonsterData> MonsterData;
};

void StageEditor::OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime) 
{
	//const char8_t* Ptr = u8"����� ����";
	//const char* Text = reinterpret_cast<const char*>(Ptr);
	//ImGui::Text(Text);

	const char8_t* Ptr = u8"��� �̹��� �̸�";
	const char* Text = reinterpret_cast<const char*>(Ptr);
	char Arr[100] = {0};
	ImGui::InputText(Text, Arr, 100);



	// 

	// ImGui::()
}