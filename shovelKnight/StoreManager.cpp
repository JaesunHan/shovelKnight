#include "stdafx.h"
#include "StoreManager.h"
#include "playerManager.h" //전방선언 헤더파일 선언


StoreManager::StoreManager()
{
}


StoreManager::~StoreManager()
{
}

HRESULT StoreManager::init()
{
	return S_OK;
}

void StoreManager::release()
{
}

void StoreManager::update()
{
	for (_viNpc = _vNpc.begin(); _viNpc != _vNpc.end(); ++_viNpc)
	{
		(*_viNpc)->update();
	}
	
}

void StoreManager::render()
{
	for (_viNpc = _vNpc.begin(); _viNpc != _vNpc.end(); ++_viNpc)
	{
		(*_viNpc)->render();
	}
}

void StoreManager::playerCollisionNpc()
{
	//콜리전 매니저에서 받아오는걸로. 


}

void StoreManager::sellPlayerSkill()
{
	
}

void StoreManager::SellPlayerHp()
{
}

void StoreManager::sellGameBgm()
{
}

void StoreManager::sellEffectSound()
{
}
