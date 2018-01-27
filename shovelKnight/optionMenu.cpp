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
	//이미지 초기화 
	_imgKeyString = "option_main";
	_imgFileName = "./image/title/option_main.bmp";
	menuBase::init(_imgKeyString, _imgFileName, WINSIZEX/2 - 534/2, WINSIZEY/2 - 320/2, 534, 320);
	
	//글자를 감싸는 선택박스 세팅
	_letter2Box = IMAGEMANAGER->addFrameImage("2글자박스", "./image/title/2letterSelectBox.bmp", 120, 36, 2, 1, true, RGB(255, 0, 255), false);
	_letter3Box = IMAGEMANAGER->addFrameImage("3글자박스", "./image/title/3letterSelectBox.bmp", 286, 67, 2, 1, true, RGB(255, 0, 255), false);
	_letter5Box = IMAGEMANAGER->addFrameImage("5글자박스", "./image/title/5letterSelectBox.bmp", 464, 67, 2, 1, true, RGB(255, 0, 255), false);

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
	_indexRc = 0;

	//애니메이션 세팅 
	int letter2Move[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("2글자박스깜빡이", "2글자박스", letter2Move, 2, 3, true);

	_letterBoxAni = KEYANIMANAGER->findAnimation("2글자박스깜빡이");

	return S_OK;
}
void optionMenu::update() 
{
	


}
void optionMenu::release()
{

}
void optionMenu::render(HDC hdc)
{
	draw(hdc);
	
	_letterBox->aniRender(hdc, _rcOption[0].left-5, _rcOption[0].top, _letterBoxAni);
	
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
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		
	}
}

void optionMenu::showLetterBox()
{
	switch (_letterBoxEnum)
	{
	default: _letterBox = IMAGEMANAGER->findImage("2글자박스");
		break;

	}
}

