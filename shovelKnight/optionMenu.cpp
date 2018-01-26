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
	menuBase::init(_imgKeyString, _imgFileName, 0, 0, WINSIZEX, WINSIZEY);
	
	return S_OK;
}
void optionMenu::update() 
{

}
void optionMenu::release()
{

}
void optionMenu::render() 
{

}
void optionMenu::draw(HDC hdc)
{

}