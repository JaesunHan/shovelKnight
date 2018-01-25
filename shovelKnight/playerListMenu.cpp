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
	_imgFileName = "./image/title/profileCreateCharacter.bmp";
	menuBase::init(_imgKeyString, _imgFileName, 0, 0, WINSIZEX, WINSIZEY);

	return S_OK;
}
void playerListMenu::update() 
{

}
void playerListMenu::release()
{

}
void playerListMenu::render() 
{

}
void playerListMenu::draw()	  
{

}
