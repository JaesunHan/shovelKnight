#pragma once
#include "npcBase.h"

//스킬 주는애
//======magicGirl기능======================= 
//1. 스킬판매 기능 -> 플레이어 스킬 추가 -> 스킬매니저에서 false값을 true로 바꿔줌
//2. 스킬 첫구매(파이어볼-가칭) 1000, 두번쨰 구매(선더볼트-가칭)3000, 세번쨰 구매 (메테오-가칭) 6000
//3. 플레이어와 상호작용방법은 매직걸의 렉트와 플레이어 렉트가 충돌했을때 (InterSectRect 사용) W 키 누르면 대화하는 것으로 상호작용
//3-1. _player->getRect()를 통해 렉트를 받아와 상호작용을 위한 렉트를 받아오고, _player->getMoeny를 통해 돈을 받아온다.(플레이어매니저)
//3-2. getMoney를 통해 받은 플레이어의 현재 골드와 상점판매품의 가격을 비교 한다.
//3-3. 차감 가능하면 아이템 구매 의사 확인
//3-4. 구매의사 확인후 -> 골드 감소 
//3-5. setFireBall()등등의 셋함수를 통해 false값을 true로 바꿔준다.
//3-6. stock()함수를 통해 구매횟수 +1 -> 구매횟수 변수의 값으로 첫번째 두번째 세번째 구매제어. 
//3-7. 구매횟수에 따라 차후 플레이어의 구매스킬 변화 
//3-8. 만약 돈이 부족하면 [부모님의 안부]를 물은뒤 대화 다이얼로그 종료.
//4. [이스터에그] 엔터더건전 처럼 만약 플레이어가 삽질로 3번 상인을 치면 
// 상인이 3회 피격후 "삐져서 장사안함" 팻말을 남기고 사라짐 

class MagicGirl :
	public npcBase
{
public:
	MagicGirl();
	~MagicGirl();
	virtual HRESULT init();
	virtual void render();
	virtual void draw();
	virtual void update();

	//==========가격 세팅 변수===========//
	int _fireBallPrice;								//얼마에 팔건지 가격 세팅용
	int _thunderBoltPrice;							//썬더볼트 얼마니
	int _bubblePrice;								//버블스킬 얼마니
	int _idx;										//벡터사용용 인덱스
	//==========팔렸는지 확인용 변수들==========//
	int _stock;										//몇번이나 상점에서 구매했는지 확인 변수
	bool _isSellFireBall;							//파이어볼 팔렸는지
	bool _isSellThunderBolt;						//썬더볼트 팔렸는지
	bool _isSellBubble;								//버블스킬 팔렸는지
	//bool _isCollisionNpc;								//NPC와 충돌
	bool _textOut;									//텍스트 아웃 테스트용
	int _count;										//카운트 체크용
	//==========스킬 스토어 관련 함수===============//
	void sellSkill();								//스킬 파는 함수 
	void stockCount();								//스톡에 따라 판매하는 스킬 정리 함수
	void magicGirlImageControl();							//npc이미지 컨트롤 함수

	virtual void isCollision(bool collision);
	
	//virtual void render();
	//virtual void draw();

};

