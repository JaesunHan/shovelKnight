#include "stdafx.h"
#include "gamePlayUI.h"


gamePlayUI::gamePlayUI()
{
}


gamePlayUI::~gamePlayUI()
{

}

HRESULT gamePlayUI::init()
{

	return S_OK;
}
void gamePlayUI::update() 
{

}
void gamePlayUI::release()
{

}
//void gamePlayUI::render() 
//{
//
//}
void gamePlayUI::draw(HDC hdc)	  
{
	_uiBackImg->render(hdc, 0, 0);
}