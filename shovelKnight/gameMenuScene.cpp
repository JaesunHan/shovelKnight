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
	_animTarget->setPlayFrame(0, 2, false, true);
	_animTarget->setFPS(1);
	_animTarget->start();

	_pSlotIdx = 0;

//	//플레이어 리스트를 보여주는 메뉴 클래스를 동적할당한다  이 객체의 렌더에서는 플레이어리스트메뉴의 틀만 보여준다.
//	_plm = new playerListMenu;
//	_plm->init();
	_plm = new playerListMenu;
	_plm->init();
	//_plm->init(_vPList[_pSlotIdx].name, _vPList[_pSlotIdx].characterkind, _vPList[_pSlotIdx].hp, _vPList[_pSlotIdx].mana, _vPList[_pSlotIdx].money, _vPList[_pSlotIdx].suit, _vPList[_pSlotIdx].weapon);
	//캐릭터를 만들자는 메뉴 클랙스를 동적할당한다. 이 객체의 렌더에서는 캐릭터 생성 메뉴의 틀만 보여준다.
	_ccm = new createCharacterMenu;
	_ccm->init();


	//INI 데이터 파일 읽어오기
	loadPlayerListData();

	return S_OK;
}
void gameMenuScene::update() 
{
	_animTarget->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		--_pSlotIdx;
		if (_pSlotIdx <= 0)	_pSlotIdx = 0;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		++_pSlotIdx;
		if (_pSlotIdx >= MAXPLAYERLIST - 1)	_pSlotIdx = MAXPLAYERLIST - 1;
	}

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

	//타겟 박스가 현재 가리키는 리스트에 값이 존재하지 않으면 캐릭터 생성화면을 출력하자
	if (_vPList[_pSlotIdx].hp == 0)
	{
		_ccm->render(getMemDC()); 
	}
	//타겟 박스가 현재 가리키는 리스트에 값이 존재하면 플레이어 정보를 출ㄹ력하자
	else 
	{	
		//플레이어 리스트를 보여주는 메뉴 클래스가 없으면 동적할당한다
		//if (_plm)
		//{
		//	_plm = new playerListMenu;
		//	_plm->init(_vPList[_pSlotIdx].name, _vPList[_pSlotIdx].characterkind, _vPList[_pSlotIdx].hp, _vPList[_pSlotIdx].mana, _vPList[_pSlotIdx].money, _vPList[_pSlotIdx].suit, _vPList[_pSlotIdx].weapon);
		//}
		//_plm = new playerListMenu;
		//초기화 할 때는 지금 선택한 정보를 전달하여 초기화하기
		if(_plm->getHP() < 0)
		{
			_plm->init(_vPList[_pSlotIdx].name, _vPList[_pSlotIdx].characterkind, _vPList[_pSlotIdx].hp, _vPList[_pSlotIdx].mana, _vPList[_pSlotIdx].money, _vPList[_pSlotIdx].suit, _vPList[_pSlotIdx].weapon);
		}
		else 
		{
			_plm->render(getMemDC());
		}
	}
	//플레이어리스트 넘머발 타겟 박스는 항상 마지막에 출력하기
	for (int i = 0; i < MAXPLAYERLIST; ++i)
	{
		_pNumberBox[i].img->render(getMemDC(), _pNumberBox[i].numberBox.left, _pNumberBox[i].numberBox.top);
	}
	_targetImg->aniRender(getMemDC(),
		_pNumberBox[_pSlotIdx].numberBox.left + (_pNumberBox[_pSlotIdx].numberBox.right - _pNumberBox[_pSlotIdx].numberBox.left) / 2 - _targetImg->getFrameWidth() / 2,
		_pNumberBox[_pSlotIdx].numberBox.top + (_pNumberBox[_pSlotIdx].numberBox.bottom - _pNumberBox[_pSlotIdx].numberBox.top) / 2 - _targetImg->getFrameHeight() / 2, 
		_animTarget);


}

void gameMenuScene::makePlayerListData()
{
	//파일 만들때는 플레이어 번호만 들어가있는 껍데기 ini 데이터를 저장한다.
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
		p.characterkind = INIDATA->loadDataInterger(fileName, subjectName, "CharacterKind");
		p.hp = INIDATA->loadDataInterger(fileName, subjectName, "HP");
		p.money = INIDATA->loadDataInterger(fileName, subjectName, "Money");
		p.mana = INIDATA->loadDataInterger(fileName, subjectName, "Mana");
		p.suit = INIDATA->loadDataInterger(fileName, subjectName, "Suit");
		p.weapon = INIDATA->loadDataInterger(fileName, subjectName, "Weapon");

		_vPList.push_back(p);
	}

}

