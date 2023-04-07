#include "TestActor.h"
#include <GameEnginePlatform/GameEngineWindow.h>

TestActor::TestActor()
{

}

TestActor::~TestActor()
{

}

void TestActor::Update(float _Delta)
{
}

float Angle = 0.0f;
float Scale = 100.0f;

void TestActor::Render(float _Delta)
{
	HDC Dc = GameEngineWindow::GetWindowBackBufferHdc();

	// Rectangle(Dc, 0, 0, 100, 100);

	const int VertexCount = 24;

	float4 Pos = { 640, 360 };

	float4 ArrVertex[VertexCount];
	ArrVertex[0] = { -0.5f, -0.5f, 0.5f };
	ArrVertex[1] = { 0.5f, -0.5f, 0.5f };
	ArrVertex[2] = { 0.5f, 0.5f, 0.5f };
	ArrVertex[3] = { -0.5f, 0.5f, 0.5f };

	ArrVertex[4] = ArrVertex[0].RotaitonXDegReturn(180.0f);
	ArrVertex[5] = ArrVertex[1].RotaitonXDegReturn(180.0f);
	ArrVertex[6] = ArrVertex[2].RotaitonXDegReturn(180.0f);
	ArrVertex[7] = ArrVertex[3].RotaitonXDegReturn(180.0f);

	ArrVertex[8] = ArrVertex[0].RotaitonYDegReturn(90.0f);
	ArrVertex[9] = ArrVertex[1].RotaitonYDegReturn(90.0f);
	ArrVertex[10] = ArrVertex[2].RotaitonYDegReturn(90.0f);
	ArrVertex[11] = ArrVertex[3].RotaitonYDegReturn(90.0f);

	ArrVertex[12] = ArrVertex[0].RotaitonYDegReturn(-90.0f);
	ArrVertex[13] = ArrVertex[1].RotaitonYDegReturn(-90.0f);
	ArrVertex[14] = ArrVertex[2].RotaitonYDegReturn(-90.0f);
	ArrVertex[15] = ArrVertex[3].RotaitonYDegReturn(-90.0f);

	ArrVertex[16] = ArrVertex[0].RotaitonXDegReturn(90.0f);
	ArrVertex[17] = ArrVertex[1].RotaitonXDegReturn(90.0f);
	ArrVertex[18] = ArrVertex[2].RotaitonXDegReturn(90.0f);
	ArrVertex[19] = ArrVertex[3].RotaitonXDegReturn(90.0f);

	ArrVertex[20] = ArrVertex[0].RotaitonXDegReturn(-90.0f);
	ArrVertex[21] = ArrVertex[1].RotaitonXDegReturn(-90.0f);
	ArrVertex[22] = ArrVertex[2].RotaitonXDegReturn(-90.0f);
	ArrVertex[23] = ArrVertex[3].RotaitonXDegReturn(-90.0f);

	POINT ArrPoint[VertexCount];

	Angle += _Delta * 10.0f;
	Scale += _Delta * 1.0f;

	// ũ���̰���

	// ũ�⸦ Ű���
	// ȸ����Ų����
	// �̵��ϰ�
	// ������Ű��
	// �θ��� ��ȯ�� �����Ų��.
	// ������ȯ�� ����.

	for (size_t i = 0; i < VertexCount; i++)
	{
		ArrVertex[i] *= Scale;
		ArrVertex[i].RotaitonXDeg(Angle);
		ArrVertex[i].RotaitonYDeg(Angle);
		ArrVertex[i].RotaitonZDeg(Angle);
		ArrVertex[i] += Pos;
		ArrPoint[i] = ArrVertex[i].ToWindowPOINT();
	}

	for (size_t i = 0; i < 6; i++)
	{
		size_t Index = i * 4;

		float4 Vector0 = ArrVertex[Index + 0];
		float4 Vector1 = ArrVertex[Index + 1];
		float4 Vector2 = ArrVertex[Index + 2];

		float4 Dir0 = Vector0 - Vector1;
		float4 Dir1 = Vector1 - Vector2;

		//float4 Cross = float4::CrossReturn(Dir0, Dir1);
		//if (0 <= Cross.z)
		//{
		//	continue;
		//}

		Polygon(Dc, &ArrPoint[i * 4], 4);
	}

	//Polygon(Dc, ArrPoint, VertexCount);
}