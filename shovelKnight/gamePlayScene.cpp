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
	_stage->setPlayerManagerMemoryAddressLink(_player);
	_stage->setStoreManagerMemoryAddressLink(_Store);
	_player->setStageManagerMemoryAddressLink(_stage);
	_player->setGameCollisinMemoryAddressLink(_gameCollision);

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

	_stage->update();
	_gameObject->update();
	_item->update();
	_enemy->update();
	_player->update();
	_Store->update();
	_skill->update();
	_gameCollision->update();
}

void gamePlayScene::render()
{
	renderTestGround();

	_stage->render();
	_Store->render();
	_gameObject->render();
	_enemy->render();
	_player->render();
	_item->render();
	_skill->render();
	_gameCollision->render();
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
