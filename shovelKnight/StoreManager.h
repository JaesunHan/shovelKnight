#pragma once
#include "gameNode.h"
#include "MagicGirl.h"
#include "HealtyGuy.h"
#include "BardKnight.h"
#include <vector>

//상호참조를 위한 전방전언
class playerManager;

class StoreManager
{
private:
	typedef vector<npcBase*> vNPC;
	typedef vector<npcBase*>::reverse_iterator viNPC;


private:
	vNPC _vNpc;									//npc벡터
	viNPC _viNpc;								//npc벡터이터레이터

	playerManager* _pm;							//플레이어매니저 할당

public:
	StoreManager();
	~StoreManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

