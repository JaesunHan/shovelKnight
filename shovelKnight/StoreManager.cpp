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
		//NPC벡터를 업데이트에서 계속 돌다가


		//if (playerCollisionNpc) // 충돌했으면? <- collision매니저에서 받아서 돌린다.
		//{
			sellPlayerSkill(_viNpc);		//스킬상인과의 상호작용
			SellPlayerHp(_viNpc);			//체력상인과의 상호작용
			sellGameBgm(_viNpc);			//음악상인과의 상호작용
		//}
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

void StoreManager::playerCollisionNpc(vector<npcBase*>::iterator temp)
{
	//콜리전 매니저에서 받아오는걸로. 
	

}

void StoreManager::sellPlayerSkill(vector<npcBase*>::iterator temp)
{
	if ((*temp)->getNpcType() == MAGICGIRL)	//NPC타입이 매직걸일때
	{
		if ((*temp)->getStock() == 0)		//한번도 구매를 안했으면  (stock이 구매횟수 변수)
		{
			//텍스트 아웃으로 "너 이거 살래? Yes or No(bool값<-변수 하나 추가해야함 1.25)
			//아래는 Yes 선택했을때의 함수
			_pm->getMoney() > 1000;
			//플레이어에 셋골드해서 골드 차감하고 
			//해당 스킬 키값 받아서 
			//셋으로 true로 바꿔준다.
			(*temp)->setStock(1);			//한번 구매했으니까 stock을 1로 반환해준다.
		}
		if ((*temp)->getStock() == 1) 
		{
			_pm->getMoney() > 3000;
		}
	}
	
}

void StoreManager::SellPlayerHp(vector<npcBase*>::iterator temp)
{
	if ((*temp)->getStock() == 0)
	{
		//텍스트 아웃으로 "
	}
}

void StoreManager::sellGameBgm(vector<npcBase*>::iterator temp)
{
}


