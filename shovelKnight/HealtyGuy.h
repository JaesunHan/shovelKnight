#pragma once
#include "npcBase.h"
//체력 주는애
//======healthGuy기능======================= 
//1. 상점 기능 -> 플레이어 최대체력을 늘려주는 닭고기 -> 플레이어의 최대체력 변수를 받아와서 +1 해줘야함
//2. 닭고기 구매하면 골드 차감. 처음은 1000골드 , 두번째는 4500골드, 3번째는 10000골드
//3. 플레이어와 상호작용방법은 헬스가이의 렉트와 플레이어 렉트가 충돌했을때 (InterSectRect 사용) W 키 누르면 대화하는 것으로 상호작용
//3-1. _player->getRect()를 통해 렉트를 받아오고, _player->getMoeny를 통해 돈을 받아온다.
//3-2. getMoney를 통해 받은 플레이어의 현재 골드와 상점판매품의 가격을 비교 한다.
//3-3. 차감 가능하면 아이템 구매 의사 확인
//3-4. 구매의사 확인후 -> 골드 감소 
//3-5. setMaxHealth() 함수를 통해 플레이어의 최대 체력 +1
//3-6. stock()함수를 통해 구매횟수 +1
//3-7. 구매횟수에 따라 차후 플레이어의 닭고기 구매가격 증가.
//4. [이스터에그] 엔터더건전 처럼 만약 플레이어가 삽질로 3번 상인을 치면 
// 상인이 3회 피격후 "삐져서 장사안함" 팻말을 남기고 사라짐 
class HealtyGuy :
	public npcBase
{
public:
	HealtyGuy();
	~HealtyGuy();
	virtual HRESULT init();


	//==========가격 세팅 변수===========//
	int _chicken;								//치킨가격
	int _drgonTail;								//용꼬리 가격
	//int _bubblePrice;							//버블스킬 얼마니

	//==========팔렸는지 확인용 변수들==========//
	int _stock;										//몇번이나 상점에서 구매했는지 확인 변수
	bool _isSellChicken;							//치킨팔렸니
	bool _isSellDragonTail;							//용꼬리 팔렸니
	//bool _isCollisionNpc;								//NPC와 충돌

	//==========스킬 스토어 관련 함수===============//
	void sellHpItem();								//스킬 파는 함수 
	
	virtual void render();
	virtual void draw();
	virtual void update();

	virtual void isCollision(bool collision);
};

