#include "stdafx.h"
#include "createCharacterMenu.h"


createCharacterMenu::createCharacterMenu()
{
}


createCharacterMenu::~createCharacterMenu()
{

}

HRESULT createCharacterMenu::init()
{
	_imgKeyString = "createCharacterMenu";
	_imgFileName = "./image/title/profileCreateCharacter.bmp";
	menuBase::init(_imgKeyString, _imgFileName, 0, 0, WINSIZEX, WINSIZEY);

	return S_OK;
}
void createCharacterMenu::update() 
{

}
void createCharacterMenu::release()
{

}
void createCharacterMenu::render(HDC hdc)
{
	draw(hdc);
}
void createCharacterMenu::draw(HDC hdc)	 
{
	_menuImg->render(hdc, 0, 0);
}
