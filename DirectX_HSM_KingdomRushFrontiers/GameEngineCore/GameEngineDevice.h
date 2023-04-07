#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// ���� :
class GameEngineDevice
{
public:
	// delete Function
	GameEngineDevice(const GameEngineDevice& _Other) = delete;
	GameEngineDevice(GameEngineDevice&& _Other) noexcept = delete;
	GameEngineDevice& operator=(const GameEngineDevice& _Other) = delete;
	GameEngineDevice& operator=(GameEngineDevice&& _Other) noexcept = delete;

	static void Initialize();

	static void CreateSwapChain();

	static void Release();

	// HWND
protected:

private:
	// ���̷�Ʈ9������ �� ����̽��� ���� ���߽��ϴ�.
	// ID3D9Device*

	// 11���ʹ� �������̽��� 2���� �и��ߴ�.
	// 1. ���ҽ��� ����̽� �������̽��� �ִ�.
	//    �׷���ī���� ram�� �ش��ϴ� �κп� ���� ������ Device
	static ID3D11Device* Device;

	// 2. �������� ���õ� ������ context��� ���ο� �������̽��� �츮���� �����ϰ� �ٲ�����ϴ�.
	static ID3D11DeviceContext* Context;

	// 3. �� �����츦 ������ ���� �ִ� ��ó��
	//    ���̷�Ʈ x�� ����ϴ� ȭ�鵵 �������� ������ �ִµ� �� ȭ�� 1���� ����ϴ� 
	//    API�� ġ�ڸ� �����DC1���� SwapChain
	static IDXGISwapChain* SwapChain;

	static IDXGIAdapter* GetHighPerformanceAdapter();

	// constrcuter destructer
	GameEngineDevice();
	~GameEngineDevice();
};
