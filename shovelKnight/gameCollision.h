#pragma once
#include "enemyManager.h"
#include "gameObjectManager.h"
#include "itemManager.h"
#include "npcManager.h"
#include "skillManager.h"
#include "playerManager.h"

class gameCollision
{
private:
	enemyManager* _enemy;
	gameObjectManager* _gameObject;
	itemManager* _item;
	npcManager* _npc;
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
	void getNPCMemoryAdress(npcManager* npc) { _npc = npc; }
	void getSkillMemoryAdress(skillManager* skill) { _skill = skill; }
	void getPlayerMemoryAdress(playerManager* player) { _player = player; }
};

