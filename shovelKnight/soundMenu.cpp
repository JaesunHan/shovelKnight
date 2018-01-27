#include "stdafx.h"
#include "soundMenu.h"


soundMenu::soundMenu()
{
}


soundMenu::~soundMenu()
{

}

HRESULT soundMenu::init()
{
	_imgKeyString = "option_Sound";
	_imgFileName = "./image/title/option_Sound.bmp";
	menuBase::init(_imgKeyString, _imgFileName, WINSIZEX / 2 - 534 / 2, WINSIZEY / 2 - 320 / 2, 534, 320);

	//글자 2개박스
	_soundLetter2Box = IMAGEMANAGER->addFrameImage("사운드2글자박스", "./image/title/2letterSelectBox.bmp", 120, 36, 2, 1, true, RGB(255, 0, 255), false);			
	//글자 3개박스
	_soundLetter4Box = IMAGEMANAGER->addFrameImage("사운드4글자박스", "./image/title/4letterSelectBox.bmp", 185, 39, 2, 1, true, RGB(255, 0, 255), false);
	//글자 5개박스
	_soundLetter5Box = IMAGEMANAGER->addFrameImage("사운드5글자박스", "./image/title/5letterSelectBox.bmp", 267, 39, 2, 1, true, RGB(255, 0, 255), false);
	//글자 10개박스
	_soundLetter10Box = IMAGEMANAGER->addFrameImage("사운드10글자박스", "./image/title/10letterSelectBox.bmp", 500, 42, 2, 1, true, RGB(255, 0, 255), false);
	
	
	
	//232, 250 시작( right, top)
	_rcSound[0] = RectMake(144, 130 , 48, 28);
	_rcSound[1] = RectMake(144, 164,  48, 28);
	_rcSound[2] = RectMake(144, 198, 48, 28);
	_rcSound[3] = RectMake(144, 232, 48, 28);

	_soundLetterBoxEm = IMAGEMANAGER->findImage("사운드2글자박스");
	_soundLetterBoxEm2 = IMAGEMANAGER->findImage("사운드4글자박스");
	_soundLetterBoxEm3 = IMAGEMANAGER->findImage("사운드5글자박스");
	_soundLetterBoxEm4 = IMAGEMANAGER->findImage("사운드10글자박스");
	
	_indexSoundRc = 0;
	
	int soundLetter2Move[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("사운드2글자박스깜빡이", "사운드2글자박스", soundLetter2Move, 2, 3, true);
	int soundLetter4Move[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("사운드4글자박스깜빡이", "사운드4글자박스", soundLetter4Move, 2, 3, true);
	int soundLetter5Move[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("사운드5글자박스깜빡이", "사운드5글자박스", soundLetter5Move, 2, 3, true);
	int soundLetter10Move[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("사운드10글자박스깜빡이", "사운드10글자박스", soundLetter10Move, 2, 3, true);

	//레터박스 애니 2글자짜리
	_soundLetterBoxAni = KEYANIMANAGER->findAnimation("사운드2글자박스깜빡이");
	KEYANIMANAGER->start("사운드2글자박스깜빡이");
	//레터박스 애니 3글자짜리
	_soundLetterBoxAni2 = KEYANIMANAGER->findAnimation("사운드4글자박스깜빡이");
	KEYANIMANAGER->start("사운드4글자박스깜빡이");
	//레터박스 애니 5글자짜리
	_soundLetterBoxAni3 = KEYANIMANAGER->findAnimation("사운드5글자박스깜빡이");
	KEYANIMANAGER->start("사운드5글자박스깜빡이");
	//레터박스 애니 10글자짜리
	_soundLetterBoxAni4 = KEYANIMANAGER->findAnimation("사운드10글자박스깜빡이");
	KEYANIMANAGER->start("사운드10글자박스깜빡이");




	return S_OK;
}
void soundMenu::update() 
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_indexSoundRc == 4) _indexSoundRc = 0;
		else _indexSoundRc++;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_indexSoundRc == 0) _indexSoundRc = 4;
		else _indexSoundRc--;
	}

}
void soundMenu::release()
{

}
void soundMenu::render(HDC hdc)
{
	draw(hdc);
}
void soundMenu::draw(HDC hdc)
{
	_menuImg->render(hdc, WINSIZEX / 2 - 534 / 2, WINSIZEY / 2 - 320 / 2);
	
	if (KEYMANAGER->isStayKeyDown('G'))
	{
		// 테스트용 : 설정메뉴 렉트 출력
		for (int i = 0; i < selectRect; ++i)
		{
			Rectangle(hdc, _rcSound[i].left, _rcSound[i].top, _rcSound[i].right, _rcSound[i].bottom);
		}
	}
	
	TTTextOut(300, 10, "_indexSoundRc", _indexSoundRc);
	
	if (_indexSoundRc == 0 )
	{
		_soundLetterBoxEm->aniRender(hdc, _rcSound[0].left - 5, _rcSound[0].top + _indexSoundRc * 32, _soundLetterBoxAni);
	}
	if (_indexSoundRc == 1)
	{
		_soundLetterBoxEm2->aniRender(hdc, _rcSound[0].left - 5, _rcSound[0].top + _indexSoundRc * 32, _soundLetterBoxAni2);
	}
	if (_indexSoundRc == 2)
	{
		_soundLetterBoxEm3->aniRender(hdc, _rcSound[0].left - 5, _rcSound[0].top + _indexSoundRc * 32, _soundLetterBoxAni3);
	}
	if (_indexSoundRc == 3)
	{
		_soundLetterBoxEm4->aniRender(hdc, _rcSound[0].left - 5, _rcSound[0].top + _indexSoundRc * 32, _soundLetterBoxAni4);
	}
}