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
	
	TextOut(getMemDC(), 55, 100, str1, strlen(str1));
	TextOut(getMemDC(), 55, 100, str2, strlen(str2));
	TextOut(getMemDC(), 55, 100, str3, strlen(str3));
}

void StoreManager::playerCollisionNpc(vector<npcBase*>::iterator temp)
{
	//콜리전 매니저에서 받아오는걸로. 
	//콜리전 매니저에서 이넘값으로 받아오고
	//해당 이넘값으로 충돌이 확인되면 w키를 눌러 대화가 가능해지는것으로 구현할것
	_isCollisionNpc == true;

}

void StoreManager::sellPlayerSkill(vector<npcBase*>::iterator temp)
{
	if (_isCollisionNpc == true)
	{
		if ((*temp)->getNpcType() == MAGICGIRL)	//NPC타입이 매직걸일때
		{
			if ((*temp)->getStock() == 0)		//한번도 구매를 안했으면  (stock이 구매횟수 변수)
			{
				//텍스트 아웃으로 "너 이거 살래? Yes or No(bool값<-변수 하나 추가해야함 1.25)
				//아래는 Yes 선택했을때의 함수
				sprintf(str1, "Welcome, Welcome My friend");
				sprintf(str2, "you wanna buy some weed?:P");
				sprintf(str3, "if u OK press 'O', or not press 'P'");
				

				if (KEYMANAGER->isOnceKeyDown('O'));				//O눌렀을때
				{
					if ((*temp)->getStock() == 0)					//한번도 상점에서 구매를 하지 않았으면
					{
						if (_pm->getMoney() >= 1000)					//플레이어 골드가 1000원보다 크다면
						{
							_pm->setMoney(-1000);						//플레이어 골드에서 1000원을 감소하고 
							_pm->setMaxHP(+1);							//maxHP를 1 증가준다.
							(*temp)->setStock(1);						//한번 구매했으니까 stock을 1로 반환해준다.
						}
						if (_pm->getMoney() < 1000)						//플레이어 골드가 1000원보다 작다면
						{
							sprintf(str4, "get the fuck off!!!!");
						}
					}


					if ((*temp)->getStock() == 1)						//상점에서 구매가 2회차일떄
					{
						if (_pm->getMoney() >= 3000)					//플레이어 골드가 1000원보다 크다면
						{
							_pm->setMoney(-3000);						//플레이어 골드에서 1000원을 감소하고 
							_pm->setMaxHP(+1);							//maxHP를 1 증가준다.
							(*temp)->setStock(2);						//stock을 2로 반환해준다.
						}
						if (_pm->getMoney() < 3000)						//플레이어 골드가 3000원보다 작다면
						{
							sprintf(str4, "get the fuck off!!!!");
						}
					}
				}
			}
			

			//NO했을때는 텍스트 아웃으로
			//"어 그...그래? 안녕 ㅃㅃ " 다이얼로그 출력 ㅃㅃ
			_isCollisionNpc == false;
		}
	}
}

void StoreManager::SellPlayerHp(vector<npcBase*>::iterator temp)
{
	if ((*temp)->getNpcType() == HEALTYGUY)	//NPC타입이 매직걸일때
	{
		if ((*temp)->getStock() == 0)		//한번도 구매를 안했으면  (stock이 구매횟수 변수)
		{
			//텍스트 아웃으로 "너 이거 살래? Yes or No(bool값<-변수 하나 추가해야함 1.25)
			//아래는 Yes 선택했을때의 함수
			sprintf(str1, "Welcome, Welcome My friend");
			sprintf(str2, "you wanna buy some weed?:P");
			sprintf(str3, "if u OK press 'O', or not press 'P'");


			if (KEYMANAGER->isOnceKeyDown('O'));				//O눌렀을때
			{
				if ((*temp)->getStock() == 0)					//한번도 상점에서 구매를 하지 않았으면
				{
					if (_pm->getMoney() >= 1000)					//플레이어 골드가 1000원보다 크다면
					{
						_pm->setMoney(-1000);						//플레이어 골드에서 1000원을 감소하고 
						_pm->setMaxHP(+1);							//maxHP를 1 증가준다.
						(*temp)->setStock(1);						//한번 구매했으니까 stock을 1로 반환해준다.
					}
					if (_pm->getMoney() < 1000)						//플레이어 골드가 1000원보다 작다면
					{
						sprintf(str4, "get the fuck off!!!!");
					}
				}


				if ((*temp)->getStock() == 1)						//상점에서 구매가 2회차일떄
				{
					if (_pm->getMoney() >= 3000)					//플레이어 골드가 1000원보다 크다면
					{
						_pm->setMoney(-3000);						//플레이어 골드에서 1000원을 감소하고 
						_pm->setMaxHP(+1);							//maxHP를 1 증가준다.
						(*temp)->setStock(2);						//stock을 2로 반환해준다.
					}
					if (_pm->getMoney() < 3000)						//플레이어 골드가 3000원보다 작다면
					{
						sprintf(str4, "get the fuck off!!!!");
					}
				}
			}
		}
		//NO했을때는 텍스트 아웃으로
		//"어 그...그래? 안녕 ㅃㅃ " 다이얼로그 출력 ㅃㅃ
		_isCollisionNpc == false;
	}
}

void StoreManager::sellGameBgm(vector<npcBase*>::iterator temp)
{
	if ((*temp)->getNpcType() == HEALTYGUY)	//NPC타입이 매직걸일때
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
		if ((*temp)->getStock() == 1) //2회차 구매일때 
		{
			_pm->getMoney() > 3000;
		}

		//NO했을때는 텍스트 아웃으로
		//"어 그...그래? 안녕 ㅃㅃ " 다이얼로그 출력 ㅃㅃ
		_isCollisionNpc == false;
	}

}


