#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{

}

HRESULT playGround::init()
{
	gameNode::init(true);

	_GTS = new gameTitleScene;
	//_gtsStr = "GameTitleScene";
	SCENEMANAGER->addScene(_GTS->getSceneName(), _GTS);

	_GMS = new gameMenuScene;
	SCENEMANAGER->addScene(_GMS->getSceneName(), _GMS);
	_GTS->setGameMenuSceneAddressLink(_GMS);

	SCENEMANAGER->changeScene(_GTS->getSceneName());
	//SCENEMANAGER->changeScene(_GTS->getSceneName());
	//_GTS->setGameMenuSceneAddressLink(_GMS);

	//_GTS->setSceneName(_gtsStr);
	/*SCENEMANAGER->changeScene(_GTS->getSceneName());*/

	//_GPS = new gamePlayScene;
	//SCENEMANAGER->addScene(_GPS->getSceneName(), _GPS);
	//SCENEMANAGER->changeScene(_GPS->getSceneName());

	
	return S_OK;
}

//메모리 관련 삭제
void playGround::release(void)
{
	gameNode::release();

}

//연산
void playGround::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();

		
}

//그리는거.......
void playGround::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================== 이 위는 손대지 마시오 =========================

	SCENEMANAGER->render();
	
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TIMEMANAGER->render(getMemDC());

	//================== 이 아래는 손대지 마시오 ========================
	this->getBackBuffer()->render(getHDC(), 0, 0);//hdc영역에 그려준다 
}
