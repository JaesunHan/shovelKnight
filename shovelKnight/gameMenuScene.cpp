#include "stdafx.h"
#include "gameMenuScene.h"
#include "gamePlayScene.h"

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
	for (int i = 0; i < MAXPLAYERLIST; ++i)
	{
		_plm[i] = new playerListMenu;
		_plm[i]->init();
	}
	
	//_plm->init(_vPList[_pSlotIdx].name, _vPList[_pSlotIdx].characterkind, _vPList[_pSlotIdx].hp, _vPList[_pSlotIdx].mana, _vPList[_pSlotIdx].money, _vPList[_pSlotIdx].suit, _vPList[_pSlotIdx].weapon);
	//캐릭터를 만들자는 메뉴 클랙스를 동적할당한다. 이 객체의 렌더에서는 캐릭터 생성 메뉴의 틀만 보여준다.
	_ccm = new createCharacterMenu;
	_ccm->init();

	//스크립트 테스트 용
	_testScript = new image;
	_testScript = IMAGEMANAGER->addImage("scriptWindow", "./image/UI/Script_window.bmp", 0, 0, 800, 96, true, RGB(255, 0, 255));
	DIALOGUEMANAGER->setScriptNScriptWindow("this is test Script ", _testScript, 255, 255, 255);
	//INI 데이터 파일 읽어오기
	loadPlayerListData();

	return S_OK;
}
void gameMenuScene::update() 
{
	//타겟 박스는 애니렌더이므로 프레임을 업뎃하기
	_animTarget->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
	//타겟 박스는 방향키로 움직인다(좌우)
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		--_pSlotIdx;
		if (_pSlotIdx <= 0)	_pSlotIdx = 0;
		//DIALOGUEMANAGER->setScriptNScriptWindow("this is test Script "+_pSlotIdx, _testScript, 255, 255, 255);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		++_pSlotIdx;
		if (_pSlotIdx >= MAXPLAYERLIST - 1)	_pSlotIdx = MAXPLAYERLIST - 1;
		//DIALOGUEMANAGER->setScriptNScriptWindow("this is test Script 5", _testScript, 255, 255, 255);
	}

	//타겟 박스가 현재 가리키는 리스트에 값이 존재하지 않으면 캐릭터 생성화면 객체를 업데이트
	if (_vPList[_pSlotIdx].hp < 0)
	{
		//_ccm->update();
	}
	//타겟 박스가 현재 가리키는 리스트에 값이 존재하면 플레이어 정보를 출ㄹ력하자
	else
	{
		//plm 에 아직 정보가 초기화 되지 않은 경우
		if (_plm[_pSlotIdx]->getHP() < 0)
		{
			//초기화하기
			_plm[_pSlotIdx]->init(_vPList[_pSlotIdx].name, _vPList[_pSlotIdx].characterkind, _vPList[_pSlotIdx].hp, _vPList[_pSlotIdx].maxHp, _vPList[_pSlotIdx].mana, _vPList[_pSlotIdx].money, _vPList[_pSlotIdx].suit, _vPList[_pSlotIdx].weapon);

		}
		else
		{
			//이 업데이트에서는 캐릭터 이미지의 프레임 업뎃이 있음 (삽기사 캐릭터의 갑옷이 반짝임)
			_plm[_pSlotIdx]->update();
			
		}
	}

	//K 버튼을 누르면 현재 인덱스에 캐릭터를 생성하기(기본값으로 생성한다.)
	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		//지금 선택한 슬롯에 정보가 없을 때만 캐릭터를 새로 생성한다.
		if (_vPList[_pSlotIdx].name[0] == '\0')
		{
			//새로운 기본캐릭터를 생성하고 ini 파일에 저장하는 함수를 호출
			createNewDefaultCharacter();
			_plm[_pSlotIdx]->init(_vPList[_pSlotIdx].name, _vPList[_pSlotIdx].characterkind, _vPList[_pSlotIdx].hp, _vPList[_pSlotIdx].maxHp, _vPList[_pSlotIdx].mana, _vPList[_pSlotIdx].money, _vPList[_pSlotIdx].suit, _vPList[_pSlotIdx].weapon);
		}
		else
		{
			SCENEMANAGER->changeScene(_GPS->getSceneName());
			_GPS->setPlayerIdx(&_pSlotIdx);
		}
	}
	//DIALOGUEMANAGER->update();
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
		//초기화 할 때는 지금 선택한 정보를 전달하여 초기화하기
		if (!(_plm[_pSlotIdx]->getHP() < 0))
		{
			_plm[_pSlotIdx]->render(getMemDC());
		}
		//DIALOGUEMANAGER->render(getMemDC(), 0, 0, 800, 96);
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
		wsprintf(subjectName, "player%d", i);
		wsprintf(titleBody, "%d", i);
		//플레이어 번호 저장하기
		INIDATA->addData(subjectName, "playerNumber", titleBody);
		INIDATA->iniSave(fileName);
	}
}

void gameMenuScene::loadPlayerListData()
{
	char* fileName = "playerList";
	char subjectName[256];
	//ini 파일이 존재하지 않으면 새로 만들기
	if (access("./playerList.ini", 0) == -1)
	{
		makePlayerListData();
	}

	//파일에 있는 플레이어를 벡터에 담기
	for (int i = 0; i < MAXPLAYERLIST; ++i)
	{
		playerList p;
		wsprintf(subjectName, "player%d", i);
	
		p.pNum = INIDATA->loadDataInterger(fileName, subjectName, "playerNumber");
		wsprintf(p.name, "%s", INIDATA->loadDataString(fileName, subjectName, "Name"));
		//p.name = INIDATA->loadDataString(fileName, subjectName, "Name");
		p.characterkind = INIDATA->loadDataInterger(fileName, subjectName, "CharacterKind");
		p.hp = INIDATA->loadDataInterger(fileName, subjectName, "HP");
		p.maxHp = INIDATA->loadDataInterger(fileName, subjectName, "MaxHP");
		p.money = INIDATA->loadDataInterger(fileName, subjectName, "Money");
		p.mana = INIDATA->loadDataInterger(fileName, subjectName, "Mana");
		p.suit = INIDATA->loadDataInterger(fileName, subjectName, "Suit");
		p.weapon = INIDATA->loadDataInterger(fileName, subjectName, "Weapon");

		_vPList.push_back(p);
	}

}

void gameMenuScene::createNewDefaultCharacter()
{
	
	//기본값을 세팅할 구조체를  선언하고
	playerList p;
	wsprintf(p.name, "palyerNumber%d", _pSlotIdx);
	p.characterkind = 0;
	p.hp = 8;
	p.maxHp = 8;
	p.mana = 30;
	p.money = 1000;
	p.suit = 0;
	p.weapon = 0;
	//벡터의 해당 인덱스에 이 구조체 데이터를 덮어쓴다
	_vPList[_pSlotIdx] = p;
	//그리고 INIDATA에 저장한다

	char* fileName = "playerList";
	char subjectName[256];
	wsprintf(subjectName, "player%d", _pSlotIdx);
	
	INIDATA->addData(subjectName, "Name", _vPList[_pSlotIdx].name);
	INIDATA->iniSave(fileName);
	addNsaveINTDataInINIFile(fileName, subjectName, "CharacterKind", _vPList[_pSlotIdx].characterkind);
	addNsaveINTDataInINIFile(fileName, subjectName, "HP", _vPList[_pSlotIdx].hp);
	addNsaveINTDataInINIFile(fileName, subjectName, "Mana", _vPList[_pSlotIdx].mana);
	addNsaveINTDataInINIFile(fileName, subjectName, "Money", _vPList[_pSlotIdx].money);
	addNsaveINTDataInINIFile(fileName, subjectName, "Suit", _vPList[_pSlotIdx].suit);
	addNsaveINTDataInINIFile(fileName, subjectName, "Weapon", _vPList[_pSlotIdx].weapon);
	
}
void gameMenuScene::addNsaveINTDataInINIFile(char* fileName, char subjectName[256], char title[256], int data)
{
	char str[128];
	wsprintf(str, "%d", data);
	INIDATA->addData(subjectName, title, str);
	INIDATA->iniSave(fileName);
}