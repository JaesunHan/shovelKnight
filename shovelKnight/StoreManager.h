#pragma once
#include "gameNode.h"
#include "MagicGirl.h"
#include "HealtyGuy.h"
#include "BardKnight.h"
#include <vector>

enum STORESTATUS
{
	STORECOLLISION,
	ENDSTORESTATUS
};

//상호참조를 위한 전방전언
class playerManager;

class StoreManager
{
private:
	typedef vector<npcBase*> vNPC;
	typedef vector<npcBase*>::iterator viNPC;


private:
	vNPC _vNpc;									//npc벡터
	viNPC _viNpc;								//npc벡터이터레이터

	playerManager* _pm;							//플레이어매니저 할당

	bool _isCollisionNpc;						//NPC랑 충돌했늬

public:
	StoreManager();
	~StoreManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	void playerCollisionNpc(vector<npcBase*>::iterator temp);					//NPC랑 충돌검출
	void sellPlayerSkill(vector<npcBase*>::iterator temp);						//플레이어 스킬판매
	void SellPlayerHp(vector<npcBase*>::iterator temp);							//플레이어 최대체력 추가판매
	void sellGameBgm(vector<npcBase*>::iterator temp);							//BGM판매

	//스토어 매니저에서 있어야 하는 함수
	//1. 플레이어와 NPC와의 렉트충돌이 되었는지
	//2. 렉트충돌시 W키로 상호작용
	//3. 상호작용시 어떤 NPC랑 상호작용하는지 체크(2번에서 렉트충돌시 NPC타입 받아와서 어떤NPC인지 체크)
	//4. 해당 NPC의 상점함수 호출
	//5. 골드 체크(구매가능한지 확인)
	//6. 체크단계 지나면 구매가능하면 구매, 
	//
};

