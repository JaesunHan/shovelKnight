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

HRESULT playerListMenu::init(char* name, int characterKind, int hp, int mana, int money, int suit, int weapon)
{
	//백그라운드 이미지 초기화
	_imgKeyString = "playerListMenu";
	_imgFileName = "./image/title/profilePlayerList.bmp";
	menuBase::init(_imgKeyString, _imgFileName, 0, 0, WINSIZEX, WINSIZEY);
	//캐릭터를 둘러싼 타이틀
	_characterTitle = IMAGEMANAGER->addImage("characterTitle", "./image/title/profileCharacterBox.bmp", 160, 180, 100, 100, true, RGB(255, 0, 255));

	//매개변수로 받은 변수들을 전역에 저장
	_cName = name;
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

	_characterAnim = new animation;
	_characterAnim->init(_characterImg->getWidth(), _characterImg->getHeight(), _characterImg->getFrameWidth(), _characterImg->getFrameHeight());
	int arrIdleAnim[] = { 0,1, 2 };
	_characterAnim->setPlayFrame(arrIdleAnim, 3, true);
	_characterAnim->setFPS(1);
	_characterAnim->start();

	return S_OK;
}
void playerListMenu::update() 
{
	_characterAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
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
	if (_hp.hp != 0)
	{
		_characterImg->aniRender(hdc,
			_characterTitle->getCenterX() - _characterImg->getFrameWidth(),
			_characterTitle->getCenterY() - _characterImg->getFrameHeight(),
			_characterAnim, 2);
	}
}
