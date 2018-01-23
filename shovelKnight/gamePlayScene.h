#pragma once
#include "gameNode.h"

#include "enemyManager.h"
#include "gameObjectManager.h"
#include "itemManager.h"
#include "bgManager.h"
#include "npcManager.h"
#include "skillManager.h"
#include "playerManager.h"

#include "gameCollision.h"

class gamePlayScene : public gameNode
{
private:
	enemyManager* _enemy;
	gameObjectManager* _gameObject;
	itemManager* _item;
	bgManager* _bg;
	npcManager* _npc;
	skillManager* _skill;
	playerManager* _player;
	gameCollision* _gameCollision;

public:
	gamePlayScene();
	~gamePlayScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

