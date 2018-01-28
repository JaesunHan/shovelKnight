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
	SCENEMANAGER->addScene(_GTS->getSceneName(), _GTS);
	
	_GMS = new gameMenuScene;
	SCENEMANAGER->addScene(_GMS->getSceneName(), _GMS);
	_GTS->setGameMenuSceneAddressLink(_GMS);
	
	SCENEMANAGER->changeScene(_GTS->getSceneName());

	_GTS->setGameMenuSceneAddressLink(_GMS);

	_GPS = new gamePlayScene;
	SCENEMANAGER->addScene(_GPS->getSceneName(), _GPS);
	//SCENEMANAGER->changeScene(_GPS->getSceneName());
	_GMS->setGamePlaySceneAdressLink(_GPS);

	SOUNDMANAGER->addSound("GamePlayBGM", "./sound/ost/Shovel Knight Soundtrack - 04 - Strike the Earth! (Plains of Passage).mp3", true, true);
	SOUNDMANAGER->addSound("BardKnightChange1", "./sound/ost/Shovel Knight Soundtrack - 05 - The Rival (Black Knight - First Battle).mp3", true, true);
	SOUNDMANAGER->addSound("BardKnightChange2", "./sound/ost/Shovel Knight Soundtrack - 06 - For Shovelry! (Boss Victory).mp3", true, true);
	SOUNDMANAGER->addSound("BardKnightChange3", "./sound/ost/Shovel Knight Soundtrack - 17 - The Local Happenstance (Village Basement).mp3", true, true);


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


	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		SOUNDMANAGER->stop("MainTheme");
		SOUNDMANAGER->play("GamePlayBGM", 0.3f);
		SCENEMANAGER->changeScene(_GPS->getSceneName());
	}

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
