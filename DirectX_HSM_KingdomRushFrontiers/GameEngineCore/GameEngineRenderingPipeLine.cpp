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
		MsgAssert("���ؽ� ���۰� �������� �ʾƼ� ��ǲ�����1 ������ ������ �� �����ϴ�.");
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
		MsgAssert("�������� �ʴ� ���ؽ� ���۸� ����Ϸ��� �߽��ϴ�.")
	}
}
