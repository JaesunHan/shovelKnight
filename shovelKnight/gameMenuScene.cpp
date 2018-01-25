#include "stdafx.h"
#include "gameMenuScene.h"


gameMenuScene::gameMenuScene()
{
	_sceneName = "GameMenuScene";
}


gameMenuScene::~gameMenuScene()
{

}


HRESULT gameMenuScene::init()
{
	_menuBGImgKeyStr = "menuBackgroundImg";
	_menuBGImgFileName = "./image/title/profileDefault.bmp";
	_backgroundImg = IMAGEMANAGER->addImage(_menuBGImgKeyStr, _menuBGImgFileName, 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	loadPlayerListData();

	return S_OK;
}
void gameMenuScene::update() 
{

}
void gameMenuScene::release()
{

}
void gameMenuScene::render() 
{
	draw();
}
void gameMenuScene::draw()	 
{
	_backgroundImg->render(getMemDC(), 0,0);
}

void gameMenuScene::makePlayerListData()
{
	char* fileName = "playerList";
	char subjectName[256];
	char titleBody[128];
	for (int i = 0; i < MAXPLAYERLIST; ++i)
	{
		wsprintf(subjectName, "palyer%d", i);
		wsprintf(titleBody, "%d", i);
		//번호 저장하기
		INIDATA->addData(subjectName, "palyerNumber", titleBody);
		INIDATA->iniSave(fileName);
	}
}

void gameMenuScene::loadPlayerListData()
{
	char* fileName = "playerList";
	char subjectName[256];
	//playerNumber = 0, playerNumber = 1, .... 
	//playerNumber 타이틀을 읽어와서 0 번이 저장되어있지 않으면
	//파일에 내용이 아예 없는 거니까 이때 파일을 만들기
	if (INIDATA->loadDataInterger(fileName, "player0", "playerNumebr") == NULL)
	{
		makePlayerListData();
	}
	for (int i = 0; i < MAXPLAYERLIST; ++i)
	{
		playerBase* p1 = new player1;
		wsprintf(subjectName, "palyer%d", i);
		INIDATA->loadDataInterger(fileName, subjectName, "Name");
		
	}

}

