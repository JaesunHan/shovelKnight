#include "stdafx.h"
#include "gameTitleScene.h"
#include "gameMenuScene.h"


gameTitleScene::gameTitleScene()
{
	_sceneName = "GameTitleScene";
}


gameTitleScene::~gameTitleScene()
{

}

HRESULT gameTitleScene::init()
{
	//_sceneName = "GameTitleScene";
	//사운드 추가 -괴도 JH
	SOUNDMANAGER->addSound("MainTheme", "./sound/ost/Shovel Knight Soundtrack - 01 - Main Theme.mp3", true, true);
	SOUNDMANAGER->addSound("MainSelect", "./sound/EFFECTSOUND/selectSound.mp3", false, false);

	_titleBGImgKeyStr = "titleBackgroundImg";
	_titleBGImgFileName = "./image/title/titleMain.bmp";
	_backgroundImg = IMAGEMANAGER->addImage(_titleBGImgKeyStr, _titleBGImgFileName, 0,0,WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	_shovelImgKeyStr = "shovelFlag";
	_shovelImgFileName = "./image/title/shovel.bmp";
	_shovelImg = IMAGEMANAGER->addImage(_shovelImgKeyStr, _shovelImgFileName, 96, 20, true, RGB(255, 0, 255));
	_shovelW = _shovelImg->getWidth();		//96
	_shovelH = _shovelImg->getHeight();		//20
	
	//렉트의세로 크기 : 22
	//각 게임 메뉴의 위치에 놓을 렉트 초기화 (게임 스타트, 공적, 옵션, 게임 종료)
	for (int i = 0; i < MAXBTN; ++i)
	{
		//232, 250 시작( right, top)
		_rcBtn[i] = RectMake(232, 250 + i * 22, 96, 22);
	}

	//처음에는 게임스타트 버튼 옆에 삽을 출력
	
	_shovelIdx = 0;

	//적 스크립트 세팅
	setScript();

	_isOption = false;		//옵션 선택됐니? = 기본 false by JH^_^
	_isTitleScene = true;	//타이틀씬일때만 노래나오게 제어
	_op = new optionMenu;
	_op->init();
	
	_sM = new soundMenu;
	_sM->init();


	_effectSoundVolume = 0.3f;
	_bgmSoundVolume = 0.3f;

	return S_OK;
}
void gameTitleScene::update() 
{
	//옵션이 선택되었으면 업데이트를 합시당
	if (_isOption)
	{
		_op->update();
	}
	else
	{
		//타이틀 사운드 재생을 위한 함수 
		soundPlay();
		//삽 이미지가 아래로 이동
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			++_shovelIdx;
			if (_shovelIdx >= MAXBTN - 1)	_shovelIdx = MAXBTN - 1;
		}
		//위로 이동
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			--_shovelIdx;
			if (_shovelIdx <= 0)	_shovelIdx = 0;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			//게임 스타트 버튼 누름
			if (_shovelIdx == 0)
			{
				//선택시 메인테마곡은 끝나고 다음씬에서 다음 노래 재생.
				_isTitleScene = false;
				SOUNDMANAGER->stop("MainTheme");
				//선택시 선택사운드 추가
				if (!SOUNDMANAGER->isPlaySound("MainSelect"))
				{
					SOUNDMANAGER->play("MainSelect", _effectSoundVolume);
				}
				
				SCENEMANAGER->changeScene(_gms->getSceneName());
			}
			//안쓸거임
			else if (_shovelIdx == 1)
			{
			}
			//옵션 버튼 누름
			else if (_shovelIdx == 2)
			{
				_isOption = true; // 옵션 눌렀구나! 
			}
			//안쓸거임
			else if (_shovelIdx == 3)
			{
			}

		}
	}



}
void gameTitleScene::release()
{
	
}
void gameTitleScene::render() 
{

	draw();
}
void gameTitleScene::draw()	  
{
	//백그라운드 이미지 출력
	_backgroundImg->render(getMemDC(), 0, 0);
	//삽 이미지가 출력될 수 있는ㄴ 위치 렉트 출력하기
	if (KEYMANAGER->isStayKeyDown('G'))
	{
		// 테스트용 : 삽이미지가 들어갈 렉트 영역을 출력
		for (int i = 0; i < MAXBTN; ++i)
		{
			Rectangle(getMemDC(), _rcBtn[i].left, _rcBtn[i].top, _rcBtn[i].right, _rcBtn[i].bottom);
		}
	}
	//삽 출력
	_shovelImg->render(getMemDC(), _rcBtn[_shovelIdx].left, _rcBtn[_shovelIdx].top);
	
	
	//옵션이 선택되었으면 랜더를 합시당
	if (_isOption)
	{
		_op->render(getMemDC());
	}

}

void gameTitleScene::setScript()
{
	//블랙나이트 
	//black knight: I knew you'd show your face sooner or later. The cerulean coward!
	char* enemyName = "BlackKnight";
	char* iniFileName = "enemyScript";
	int tmp = INIDATA->loadDataInterger(iniFileName, enemyName, "enemyNum");
	//이미 데이터가 있으므로 ini 파일을 만들지 않는다.
	if (tmp != NULL)
	{
		return;
	}
	//데이터가 없으므로 ini 파일을 만들자
	INIDATA->addData(enemyName, "enemyNum", "0");
	INIDATA->iniSave(iniFileName);
	INIDATA->addData(enemyName, "script", "black knight: I knew you'd show your face sooner or later. The cerulean coward!");
	INIDATA->iniSave(iniFileName);
	
}

void gameTitleScene::soundPlay()
{
	if(_isTitleScene)
	{
		if (!SOUNDMANAGER->isPlaySound("MainTheme"))
		{
			SOUNDMANAGER->play("MainTheme", _bgmSoundVolume, true);
		}
	}

}
