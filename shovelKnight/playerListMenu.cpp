#include "stdafx.h"
#include "playerListMenu.h"


playerListMenu::playerListMenu()
{
}


playerListMenu::~playerListMenu()
{

}

HRESULT playerListMenu::init()
{
	_imgKeyString = "playerListMenu";
	_imgFileName = "./image/title/profilePlayerList.bmp";
	menuBase::init(_imgKeyString, _imgFileName, 0, 0, WINSIZEX, WINSIZEY);
	//캐릭터를 둘러싼 타이틀
	_characterTitle = IMAGEMANAGER->addImage("characterTitle", "./image/title/profileCharacterBox.bmp", 160, 180, 100, 100, true, RGB(255, 0, 255));

	return S_OK;
}

HRESULT playerListMenu::init(char name[128], int characterKind, int hp, int mana, int money, int suit, int weapon)
{
	//백그라운드 이미지 초기화
	_imgKeyString = "playerListMenu";
	_imgFileName = "./image/title/profilePlayerList.bmp";
	menuBase::init(_imgKeyString, _imgFileName, 0, 0, WINSIZEX, WINSIZEY);
	//캐릭터를 둘러싼 타이틀
	_characterTitle = IMAGEMANAGER->addImage("characterTitle", "./image/title/profileCharacterBox.bmp", 160, 180, 100, 100, true, RGB(255, 0, 255));

	//매개변수로 받은 변수들을 전역에 저장
	wsprintf(_cName, "%s", name);
	_characterKind = characterKind;
	_hp.hp = hp;
	_mana.mana = mana;
	_money.money = money;
	
	//캐릭터 이미지 초기화 할 정보들을 미리 저장
	_imgKeyNFile[0].imageKeyStr = "ShovelKnightShine";
	_imgKeyNFile[0].imageFileName = "./image/shovelKnight/shovelKnightShine.bmp";
	_imgKeyNFile[0].totalWidth = 102;
	_imgKeyNFile[0].totalHeight = 62;
	_imgKeyNFile[0].frameX = 3;
	_imgKeyNFile[0].frameY = 2;
	//캐릭터 이미지를 이미지 매니저에 등록
	_characterImg = IMAGEMANAGER->addFrameImage(
		_imgKeyNFile[characterKind].imageKeyStr,
		_imgKeyNFile[characterKind].imageFileName,
		_imgKeyNFile[characterKind].totalWidth,
		_imgKeyNFile[characterKind].totalHeight,
		_imgKeyNFile[characterKind].frameX,
		_imgKeyNFile[characterKind].frameY,
		true, RGB(255, 0, 255));

	//삽기사 아이들 애니메이션 만들기
	_characterAnim = new animation;
	_characterAnim->init(_characterImg->getWidth(), _characterImg->getHeight(), _characterImg->getFrameWidth(), _characterImg->getFrameHeight());
	_characterAnim->setPlayFrame(0, 3, false, true);
	_characterAnim->setFPS(1);
	_characterAnim->start();

	//HP 출력에 사용될 이미지 3개 : 풀 HP, 하프 HP, 엠티 HP
	_emptyHP = IMAGEMANAGER->addImage("emptyHPBlock", "./image/UI/Hud_empty.bmp", 16, 16, true, RGB(255, 0, 255));
	_fullHP = IMAGEMANAGER->addImage("fullHPBlock", "./image/UI/Hud_hpFull.bmp", 16, 16, true, RGB(255, 0, 255));
	_halfHP = IMAGEMANAGER->addImage("halfHPBlock", "./image/UI/Hud_hpHalf.bmp", 16, 16, true, RGB(255, 0, 255));




	return S_OK;
}
void playerListMenu::update() 
{
	_characterAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 8);
}
void playerListMenu::release()
{

}
void playerListMenu::render(HDC hdc) 
{
	draw(hdc);
}
void playerListMenu::draw(HDC hdc)	  
{
	_menuImg->render(hdc, 0, 0);
	_characterTitle->render(hdc, _characterTitle->getX(), _characterTitle->getY());
	//캐릭터 정보가 있으면 그 정보를 출력
	if (_hp.hp != 0)
	{
		//캐릭터 이미지를 애니렌더로 그리기
		_characterImg->aniRender(hdc,
			_characterTitle->getCenterX() - _characterImg->getFrameWidth(),
			_characterTitle->getCenterY() - _characterImg->getFrameHeight(),
			_characterAnim, 2);
		//======================== Start 캐릭터의 이름을 텍스트로 출력======================================
		TextOut(hdc, _menuImg->getWidth() / 3 * 1+20, _menuImg->getHeight() / 3 * 1+10, _cName, strlen(_cName));
		//======================== End 캐릭터의 이름을 텍스트로 출력======================================

		//======================== Start hp 출력하기 ===================================================
		//기본으로 빈거 4개 깔기
		for (int i = 0; i < MAXHPIMAGE; ++i)
		{
			_emptyHP->render(hdc, _menuImg->getWidth() / 3 * 1 + 20 + 16 * i, _menuImg->getHeight() / 3 * 1 + 30);
		}
		for (int i = 0; i < _hp.hp / 2; ++i)
		{
			_fullHP->render(hdc, _menuImg->getWidth() / 3 * 1 + 20 + 16 * i, _menuImg->getHeight() / 3 * 1 + 30);
		}
		if (_hp.hp % 2 == 1)
		{
			_halfHP->render(hdc, _menuImg->getWidth() / 3 * 1 + 20 + 16 * (_hp.hp / 2), _menuImg->getHeight() / 3 * 1 + 30);
		}
		//======================== End hp 출력하기 ===================================================
	}
}
