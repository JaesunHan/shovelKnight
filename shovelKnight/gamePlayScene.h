#pragma once
#include "gameNode.h"

#include "enemyManager.h"
#include "gameObjectManager.h"
#include "itemManager.h"
#include "StoreManager.h"
#include "skillManager.h"
#include "playerManager.h"
#include "stageManager.h"

#include "gameCollision.h"

class gamePlayScene : public gameNode
{
private:
	string _sceneName;				//씬매니저에 등록할 씬 이름

	enemyManager* _enemy;
	gameObjectManager* _gameObject;
	itemManager* _item;
	StoreManager* _Store;					//npcManager->StoreManager수정했습니다.^_^v -괴도재환 01.25
	skillManager* _skill;
	playerManager* _player;
	gameCollision* _gameCollision;
	stageManager* _stage;

public:
	gamePlayScene();
	~gamePlayScene();

	//================================= Start 게터 세터 ============================
	inline string getSceneName() { return _sceneName; }
	inline void setSceneName(string sn) { _sceneName = sn; }
	//================================= End 게터 세터 ==============================

	HRESULT init();
	void release();
	void update();
	void render();
};

