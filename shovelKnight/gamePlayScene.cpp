#include "stdafx.h"
#include "gamePlayScene.h"


gamePlayScene::gamePlayScene()
{
	_sceneName = "gamePlayScene";
}


gamePlayScene::~gamePlayScene()
{
}

HRESULT gamePlayScene::init()
{
	_enemy = new enemyManager;
	_gameObject = new gameObjectManager;
	_item = new itemManager;
	_Store = new StoreManager;
	_skill = new skillManager;
	_player = new playerManager;
	_gameCollision = new gameCollision;
	_stage = new stageManager;

	_gameCollision->getEmemyMemoryAdress(_enemy);
	_gameCollision->getGameObjectMemoryAdress(_gameObject);
	_gameCollision->getItemMemoryAdress(_item);
	_gameCollision->getStoreMemoryAdress(_Store);
	_gameCollision->getSkillMemoryAdress(_skill);
	_gameCollision->getPlayerMemoryAdress(_player);
	_stage->setPlayerBaseMemoryAddressLink(_player);

	_enemy->init();
	_gameObject->init();
	_item->init();
	_Store->init();
	_skill->init();
	_player->init();
	_gameCollision->init();
	_stage->init();



	return S_OK;
}

void gamePlayScene::release()
{
	_enemy->release();
	_gameObject->release();
	_item->release();
	_Store->release();
	_skill->release();
	_player->release();
	_gameCollision->release();
	_stage->release();
}

void gamePlayScene::update()
{

	_gameObject->update();
	_item->update();
	_stage->update();
	_enemy->update();
	_player->update();
	_Store->update();
	_skill->update();
	_gameCollision->update();
}

void gamePlayScene::render()
{
	_stage->render();
	_player->render();
	_enemy->render();
	_gameObject->render();
	_item->render();
	_Store->render();
	_skill->render();
	_gameCollision->render();
}
