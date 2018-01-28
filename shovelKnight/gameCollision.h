#pragma once
#include "enemyManager.h"
#include "gameObjectManager.h"
#include "itemManager.h"
#include "StoreManager.h"
#include "skillManager.h"
#include "playerManager.h"

class gameCollision
{
private:
	enemyManager* _enemy;
	gameObjectManager* _gameObject;
	itemManager* _item;
	StoreManager* _store;		//npcManager->StoreManager수정했습니다.^_^v -괴도재환 01.25
	skillManager* _skill;
	playerManager* _player;

public:
	gameCollision();
	~gameCollision();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void getEmemyMemoryAdress(enemyManager* enemy) { _enemy = enemy; }
	void getGameObjectMemoryAdress(gameObjectManager* gameObject) { _gameObject = gameObject; }
	void getItemMemoryAdress(itemManager* item) { _item = item; }
	void getStoreMemoryAdress(StoreManager* store) { _store = store; }
	void getSkillMemoryAdress(skillManager* skill) { _skill = skill; }
	void getPlayerMemoryAdress(playerManager* player) { _player = player; }


	void enemyDead();
	void enemyDetectPlayer();
	void PlayerMeetNPC();
};


//void collisionPlayerMapDown();
//void collisionPlayerMapUp();
//void collisionPlayerMapRight();
//void collisionPlayerMapLeft();
//void collisionPlayerInAir();
//BOOL collisionPlayerInAir2(int probeX, int probeY);