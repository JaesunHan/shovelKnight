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

	//INI 데이터 파일 읽어오기
	loadPlayerListData();

	for (int i = 0; i < MAXPLAYERLIST; ++i)
	{
		//214, 134
		//숫자 박스가 들어갈 위치를 렉트로 지정해놓기
		_pNumberBox[i].numberBox = RectMakeCenter(210 + i * 40, 134, 28, 28);
		//렉트 박스 안에 들어갈 이미지 파일 을 이미지 매니저에 등록해놓기
		char nImagFileNmae[258];
		wsprintf(nImagFileNmae, "./image/title/number%d.bmp", i+1);
		char nImageKeyStr[128];
		wsprintf(nImageKeyStr, "number%d", i + 1);
		_pNumberBox[i].img = IMAGEMANAGER->addImage(nImageKeyStr, nImagFileNmae, 0, 0, 28, 28, true, RGB(255, 0, 255));
	}

	_targetImg = IMAGEMANAGER->addFrameImage("targetBox", "./image/title/selectBoxFrame.bmp", 0, 0, 80, 37, 2, 1, true, RGB(255, 0, 255));
	_animTarget = new animation;
	_animTarget->init(_targetImg->getWidth(), _targetImg->getHeight(), _targetImg->getFrameWidth(), _targetImg->getFrameHeight());

	_pSlotIdx = 0;

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
	//기본이미지 렌더
	_backgroundImg->render(getMemDC(), 0,0);
	for (int i = 0; i < MAXPLAYERLIST; ++i)
	{
		_pNumberBox[i].img->render(getMemDC(), _pNumberBox[i].numberBox.left, _pNumberBox[i].numberBox.top);
	}
}

void gameMenuScene::makePlayerListData()
{
	//파일 만들때는 플레이어 번호만 들어가있는 ini 데이터를 저장한다.
	char* fileName = "playerList";
	char subjectName[256];
	char titleBody[128];
	for (int i = 0; i < MAXPLAYERLIST; ++i)
	{
		wsprintf(subjectName, "palyer%d", i);
		wsprintf(titleBody, "%d", i);
		//플레이어 번호 저장하기
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
		makePlayerListData();//파일 만드는 함수를 호출
	}
	//파일에 있는 플레이어를 벡터에 담기
	for (int i = 0; i < MAXPLAYERLIST; ++i)
	{
		playerList p;
		wsprintf(subjectName, "palyer%d", i);
	
		p.pNum = INIDATA->loadDataInterger(fileName, subjectName, "playerNumber");
		p.name = INIDATA->loadDataString(fileName, subjectName, "playerName");
		p.hp = INIDATA->loadDataInterger(fileName, subjectName, "HP");
		p.money = INIDATA->loadDataInterger(fileName, subjectName, "Money");
		p.mana = INIDATA->loadDataInterger(fileName, subjectName, "Mana");

		_vPList.push_back(p);
	}

}

