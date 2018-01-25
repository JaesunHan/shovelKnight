#include "stdafx.h"
#include "gamePlayScene.h"


gamePlayScene::gamePlayScene()
{
}


gamePlayScene::~gamePlayScene()
{
}

HRESULT gamePlayScene::init()
{
	_enemy = new enemyManager;
	_gameObject = new gameObjectManager;
	_item = new itemManager;
	_npc = new npcManager;
	_skill = new skillManager;
	_player = new playerManager;
	_gameCollision = new gameCollision;

	_gameCollision->getEmemyMemoryAdress(_enemy);
	_gameCollision->getGameObjectMemoryAdress(_gameObject);
	_gameCollision->getItemMemoryAdress(_item);
	_gameCollision->getNPCMemoryAdress(_npc);
	_gameCollision->getSkillMemoryAdress(_skill);
	_gameCollision->getPlayerMemoryAdress(_player);

	_enemy->init();
	_gameObject->init();
	_item->init();
	_npc->init();
	_skill->init();
	_player->init();
	_gameCollision->init();



	return S_OK;
}

void gamePlayScene::release()
{
	_enemy->release();
	_gameObject->release();
	_item->release();
	_npc->release();
	_skill->release();
	_player->release();
	_gameCollision->release();
}

void gamePlayScene::update()
{
	_enemy->update();
	_gameObject->update();
	_item->update();
	_player->update();
	_npc->update();
	_skill->update();
	_gameCollision->update();
}

void gamePlayScene::render()
{
	_player->render();
	_enemy->render();
	_gameObject->render();
	_item->render();
	_npc->render();
	_skill->render();
	_gameCollision->render();
}
