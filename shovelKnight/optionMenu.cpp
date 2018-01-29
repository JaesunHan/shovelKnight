#include "stdafx.h"
#include "optionMenu.h"



optionMenu::optionMenu()
{
}


optionMenu::~optionMenu()
{

}


HRESULT optionMenu::init()
{
	_isOptionRender = false;// 초기화로 false해야 꺼진다.
	//이미지 초기화 
	_imgKeyString = "option_main";
	_imgFileName = "./image/title/option_main.bmp";
	menuBase::init(_imgKeyString, _imgFileName, WINSIZEX/2 - 534/2, WINSIZEY/2 - 320/2, 534, 320);
	
	//글자를 감싸는 선택박스 세팅
	_letter2Box = IMAGEMANAGER->addFrameImage("2글자박스", "./image/title/2letterSelectBox.bmp", 120, 36, 2, 1, true, RGB(255, 0, 255), false);
	_letter3Box = IMAGEMANAGER->addFrameImage("3글자박스", "./image/title/3letterSelectBox.bmp", 165, 39, 2, 1, true, RGB(255, 0, 255), false);
	_letter5Box = IMAGEMANAGER->addFrameImage("5글자박스", "./image/title/5letterSelectBox.bmp", 267, 39, 2, 1, true, RGB(255, 0, 255), false);

	//옵션 선택위한 렉트 깝시다
	//뒤로, 게임, 조작 ->두글자여서 0,1,2 렉트는 48,28 사이즈로
	for (int i = 0; i < 3; ++i)
	{
		//232, 250 시작( right, top)
		_rcOption[i] = RectMake(144, 130 + i * 34, 48, 28);
	}

	//사운드, 그래픽 -> 세글자여서 렉튼 63, 28 사이즈로
	for (int i = 3; i < 5; ++i)
	{
		_rcOption[i] = RectMake(144, 232 + (i - 3) * 34, 63, 28);
	}

	//데이터 삭제(5글자) 렉트 
	_rcOption[5] = RectMake(144, 297, 115, 28);

	_letterBoxEnum = LETTERBACK;


	_letterBox = IMAGEMANAGER->findImage("2글자박스");
	_letterBoxEm = IMAGEMANAGER->findImage("3글자박스");
	_letterBoxEm2 = IMAGEMANAGER->findImage("5글자박스");

	_indexRc = 0;

	//애니메이션 세팅 
	int letter2Move[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("2글자박스깜빡이", "2글자박스", letter2Move, 2, 3, true);

	int letter3Move[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("3글자박스깜빡이", "3글자박스", letter3Move, 2, 3, true);

	int letter5Move[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("5글자박스깜빡이", "5글자박스", letter5Move, 2, 3, true);


	_letterBoxAni = KEYANIMANAGER->findAnimation("2글자박스깜빡이");
	//_letterBoxAni2 = KEYANIMANAGER->findAnimation
	KEYANIMANAGER->start("2글자박스깜빡이");

	_letterBoxAni2 = KEYANIMANAGER->findAnimation("3글자박스깜빡이");
	KEYANIMANAGER->start("3글자박스깜빡이");
	_letterBoxAni3 = KEYANIMANAGER->findAnimation("5글자박스깜빡이");
	KEYANIMANAGER->start("5글자박스깜빡이");

	_sm = new soundMenu;
	_sm->init();
	_isSoundMenu = false;

	//_isOptionRender = true;
	return S_OK;
}

void optionMenu::update() 
{	//옵션이 선택되었으면 업데이트를 합니다.
	if (_sm->getIsOptionRender())
	{
		_sm->update();
	}
	else
	{
		_sm->setIsOptionRender(false);
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_indexRc == 5) _indexRc = 0;
			else _indexRc++;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (_indexRc == 0) _indexRc = 5;
			else _indexRc--;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			if (_indexRc == 0)
			{
				_isOptionRender = false;
			}
			if (_indexRc == 3)
			{
				_isSoundMenu = true;
				_sm->setIsOptionRender(true);
			}
		}
	}
	switch (_indexRc)
	{
	case 0: case 1: case 2:
		//letterBox = ;
		break;
	case 3: case 4:
		//_letterBox = ;
		break;
	case 5:
		//_letterBox = ;
		break;
	}


}
void optionMenu::release()
{

}
void optionMenu::render(HDC hdc)
{

		draw(hdc);
	
	

	
}
void optionMenu::draw(HDC hdc)
{
	_menuImg->render(hdc, WINSIZEX / 2 - 534 / 2, WINSIZEY / 2 - 320 / 2);
	
	if (KEYMANAGER->isStayKeyDown('G'))
	{
		// 테스트용 : 설정메뉴 렉트 출력
		for (int i = 0; i < selectRect; ++i)
		{
			Rectangle(hdc, _rcOption[i].left, _rcOption[i].top, _rcOption[i].right, _rcOption[i].bottom);
		}
	}
	
	//TTTextOut(300, 10, "_indexRC", _indexRc);
	if (_indexRc >= 0 && _indexRc <= 2)
	{
		_letterBox->aniRender(hdc, _rcOption[0].left - 5, _rcOption[0].top + _indexRc * 32, _letterBoxAni);
	}
	if (_indexRc >= 3 && _indexRc <= 4)
	{
		_letterBoxEm->aniRender(hdc, _rcOption[0].left - 5, _rcOption[0].top + _indexRc * 32, _letterBoxAni2);
	}
	if (_indexRc == 5)
	{
		_letterBoxEm2->aniRender(hdc, _rcOption[0].left - 5, _rcOption[0].top + _indexRc * 32, _letterBoxAni3);
	}

	if (_sm->getIsOptionRender())
	{
		_sm->render(hdc);
	}
	
	//if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	//{
	//	_letterBox->aniRender(hdc, _rcOption[1].left - 5, _rcOption[1].top, _letterBoxAni);
	//}
}

void optionMenu::showLetterBox()
{
	switch (_letterBoxEnum)
	{
		default: _letterBox = IMAGEMANAGER->findImage("2글자박스");
		break;

	}
}

