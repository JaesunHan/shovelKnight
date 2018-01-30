#pragma once
#include "enemyManager.h"
#include "itemManager.h"
#include "StoreManager.h"
#include "skillManager.h"
#include "playerManager.h"

class gameCollision
{
private:
	enemyManager* _enemy;
	itemManager* _item;
	StoreManager* _store;		//npcManager->StoreManager수정했습니다.^_^v -괴도재환 01.25
	skillManager* _skill;
	playerManager* _player;



	bool _playerMeetNPC;
	int _countDragonEffect;
	float _dragonTime;

	int _countDragonAttackEffect;
	float _dragonAttackTime;

public:
	gameCollision();
	~gameCollision();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void getEmemyMemoryAdress(enemyManager* enemy) { _enemy = enemy; }
	void getItemMemoryAdress(itemManager* item) { _item = item; }
	void getStoreMemoryAdress(StoreManager* store) { _store = store; }
	void getSkillMemoryAdress(skillManager* skill) { _skill = skill; }
	void getPlayerMemoryAdress(playerManager* player) { _player = player; }

	bool getPlayerMeetNPC() {	return _playerMeetNPC;	}


	void enemyDead();
	void PlayerMeetNPC();
	void PlayerAndEnemy();
	void EnemyAction();

	void PlayerAndSkill();
};


//void collisionPlayerMapDown();
//void collisionPlayerMapUp();
//void collisionPlayerMapRight();
//void collisionPlayerMapLeft();
//void collisionPlayerInAir();
//BOOL collisionPlayerInAir2(int probeX, int probeY);