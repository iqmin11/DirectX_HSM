#include "PrecompileHeader.h"
#include "ContentsUIRenderer.h"

ContentsUIRenderer::ContentsUIRenderer()
{

}

ContentsUIRenderer::~ContentsUIRenderer()
{

}

void ContentsUIRenderer::SetProgress(float _Ratio)
{
	Buffer.Progress = _Ratio;
}

void ContentsUIRenderer::Start()
{
	PushCameraRender(100);
	SetMesh("Rect");
	SetPipeLine("ProgressUI_Circle");

	AtlasData.x = 0.0f;
	AtlasData.y = 0.0f;
	AtlasData.z = 1.0f;
	AtlasData.w = 1.0f;

	ColorOptionValue.MulColor = float4::One;
	ColorOptionValue.PlusColor = float4::Null;

	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
	GetShaderResHelper().SetConstantBufferLink("ProgressCircleBuffer", Buffer);
}
