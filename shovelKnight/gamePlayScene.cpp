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
	_item = new itemManager;
	_Store = new StoreManager;
	_skill = new skillManager;
	_player = new playerManager;
	_gameCollision = new gameCollision;
	_stage = new stageManager;
	_gamePlayUI = new gamePlayUI;
	_object = new frontObjectManager;

	_gameCollision->getEmemyMemoryAdress(_enemy);
	_gameCollision->getItemMemoryAdress(_item);
	_gameCollision->getStoreMemoryAdress(_Store);
	_gameCollision->getSkillMemoryAdress(_skill);
	_gameCollision->getPlayerMemoryAdress(_player);
	_stage->setPlayerManagerMemoryAddressLink(_player);
	_stage->setStoreManagerMemoryAddressLink(_Store);
	_stage->setFrontObjectManagerMemoryAddressLink(_object);
	_stage->setEnemyManagerMemoryAddressLink(_enemy);
	_player->setStageManagerMemoryAddressLink(_stage);
	_player->setGameCollisinMemoryAddressLink(_gameCollision);
	_player->setGamePlayUIMemoryAddressLink(_gamePlayUI);
	_player->setFrontObjectManagerMemoryAddressLink(_object);
	_object->setPlayerManagerMemoryAddressLink(_player);
	_object->setStageManagerMemoryAddressLink(_stage);

	_enemy->init();
	_item->init();
	_Store->init();
	_skill->init();
	
	_gameCollision->init();
	_stage->init();
	_selectPlayerIdx;
	_gamePlayUI->init();
	_object->init();
	_player->init();

	_object->setGamePlayUIMemoryAddressLink(_gamePlayUI);


	return S_OK;
}

void gamePlayScene::release()
{
	_enemy->release();
	_item->release();
	_Store->release();
	_skill->release();
	_player->release();
	_gameCollision->release();
	_stage->release();
	_gamePlayUI->release();
	_object->release();
}

void gamePlayScene::update()
{

	_stage->update();
	_item->update();
	_enemy->update();
	_player->update();
	_Store->update();
	_skill->update();
	_gameCollision->update();
	_gamePlayUI->update();
	_object->update();
}

void gamePlayScene::render()
{
	renderTestGround();

	_stage->render();
	_Store->render();
	_enemy->render();
	_object->render();
	_player->render();
	_item->render();
	_skill->render();
	_gameCollision->render();
	_gamePlayUI->render(getMemDC());
}

void gamePlayScene::renderTestGround()
{
	RECT rc = { 0, 0, WINSIZEX, WINSIZEY };
	HBRUSH hBrush = CreateSolidBrush(RGB(70, 70, 70));
	HBRUSH oldBrush = (HBRUSH)SelectObject(BACKBUFFER, hBrush);
	HPEN hPen = CreatePen(1, 2, RGB(70, 70, 70));
	HPEN oldPen = (HPEN)SelectObject(BACKBUFFER, hPen);
	RectangleMakeRect(BACKBUFFER, rc);
	SelectObject(BACKBUFFER, oldBrush);
	DeleteObject(hBrush);
	SelectObject(BACKBUFFER, oldPen);
	DeleteObject(hPen);
}
