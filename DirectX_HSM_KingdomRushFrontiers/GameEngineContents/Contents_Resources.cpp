#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>

void ContentsCore::ContentsResourcesCreate()
{
	// �ؽ�ó �ε常 �� �������� �ϰ� �����ϴ� ������ ���̼���.

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentsResources");
		NewDir.Move("ContentsResources");
		NewDir.Move("Shader");

		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineShader::AutoCompile(Files[i]);
		}
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("ProgressUI_Circle");

		Pipe->SetVertexShader("ProgressUI_Circle.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ProgressUI_Circle.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}


	//{
	//	std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("Fade");
	//
	//	//Pipe->SetVertexBuffer("FullRect");
	//	//Pipe->SetIndexBuffer("FullRect");
	//	Pipe->SetVertexShader("FadeShader.hlsl");
	//	Pipe->SetRasterizer("Engine2DBase");
	//	Pipe->SetPixelShader("FadeShader.hlsl");
	//	Pipe->SetBlendState("AlphaBlend");
	//	Pipe->SetDepthState("EngineDepth");
	//}



}