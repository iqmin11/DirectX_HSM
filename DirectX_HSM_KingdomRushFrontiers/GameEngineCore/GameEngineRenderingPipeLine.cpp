#include "PrecompileHeader.h"
#include "GameEngineRenderingPipeLine.h"
#include <GameEngineCore/GameEngineDevice.h>
#include "GameEngineVertexBuffer.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
{

}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{

}

void GameEngineRenderingPipeLine::InputAssembler1()
{
	if (nullptr == VertexBuffer)
	{
		MsgAssert("버텍스 버퍼가 존재하지 않아서 인풋어셈블러1 과정을 실행할 수 없습니다.");
		return;
	}

	VertexBuffer->Setting();
	//GameEngineDevice::GetContext()->IASetVertexBuffers();
}

void GameEngineRenderingPipeLine::VertexShader()
{
	//GameEngineDevice::GetContext()->VSSetShader;
}

void GameEngineRenderingPipeLine::InputAssembler2()
{
	//GameEngineDevice::GetContext()->IASetIndexBuffer;
}

void GameEngineRenderingPipeLine::Rasterizer()
{
	//GameEngineDevice::GetContext()->RSSetState();
}

void GameEngineRenderingPipeLine::PixelShader()
{
	//GameEngineDevice::GetContext()->PSSetShader();
}

void GameEngineRenderingPipeLine::OutputMerger()
{
	//GameEngineDevice::GetContext()->OMSetRenderTargets();
}

void GameEngineRenderingPipeLine::SetVertexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexBuffer = GameEngineVertexBuffer::Find(UpperName);

	if (nullptr == VertexBuffer)
	{
		MsgAssert("존재하지 않는 버텍스 버퍼를 사용하려고 했습니다.")
	}
}
