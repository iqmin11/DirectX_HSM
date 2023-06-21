#include "PrecompileHeader.h"
#include "PlayManager.h"

PlayManager* PlayManager::MainPlayer = nullptr;

PlayManager::PlayManager()
{
	if (MainPlayer != nullptr)
	{
		return;
	}
	MainPlayer = this;
}

PlayManager::~PlayManager()
{

}

void PlayManager::Start()
{

}

void PlayManager::Update(float _DeltaTime)
{

}
