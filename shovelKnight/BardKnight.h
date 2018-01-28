#pragma once
#include "npcBase.h"

//바드나이트 -fmod를 가지고 놀아보자
//======바드나이트기능======================= 
//1. 음악의 변경 기능 
//2. 100원을 기부하면 배경음악-> 1분간 배경음악이 다른 음악으로 바뀜
//3. 1000원을 기부하면 기본 삽질 공격 효과음이 바뀜 (타 게임 효과음으로 ex 메탈슬러그 헤비머신건)
//3-1.fmod 이펙트 사운드와 배경음 설정(사운드매니저?)를 바꾸자. 
//3-2. getMoney를 통해 받은 플레이어의 현재 골드와 상점판매품의 가격을 비교 한다.
//3-3. 차감 가능하면 아이템 구매 의사 확인
//3-4. 구매의사 확인후 -> 골드 감소 
//3-5. fmod 함수와의 상호통신함수를 만들어서 노래 변경을 꾀해본다.
//4. [이스터에그] 엔터더건전 처럼 만약 플레이어가 삽질로 3번 상인을 치면 
// 상인이 3회 피격후 "삐져서 장사안함" 팻말을 남기고 사라짐 



class BardKnight :
	public npcBase
{
public:
	BardKnight();
	~BardKnight();


	//==========가격 세팅 변수===========//
	int _bgmPrice;									//배경음 가격
	int _effectSoundPrice;							//이펙트 사운드 가격  -> 삽질 사운드만 
	

	//==========팔렸는지 확인용 변수들==========//
	int _stock;										//몇번이나 상점에서 구매했는지 확인 변수
	bool _isSellBgm;								//브금 팔렸는지
	bool _isSellEffectSound;						//이펙트 사운드 팔렸는지
	//bool _isCollisionNpc;								//NPC와 충돌

	//==========스킬 스토어 관련 함수===============//
	void changeBGM();								//스킬 파는 함수
	void changeEffectSound();
	virtual HRESULT init();
	virtual void render();
	virtual void draw();
	virtual void update();

	virtual void isCollision(bool collision);
	
};

