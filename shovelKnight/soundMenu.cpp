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


	return S_OK;
}
void soundMenu::update() 
{

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
}