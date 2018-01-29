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
	char* filename = "playerList";
	_uiBackImg = IMAGEMANAGER->addImage("GamePlayUI", "./image/UI/UI.bmp", 0, 0, 800, 35, true, RGB(255, 0, 255));
	char subjectName[256];
	wsprintf(subjectName, "player%d", _playerIdx);

	_life = INIDATA->loadDataInterger(filename, subjectName, "HP");
	_mana = INIDATA->loadDataInterger(filename, subjectName, "Mana");
	_gold = INIDATA->loadDataInterger(filename, subjectName, "Money");

	return S_OK;
}
void gamePlayUI::update()
{

}
void gamePlayUI::release(HDC hdc)
{
	draw(hdc);
}
//void gamePlayUI::render() 
//{
//
//}
void gamePlayUI::draw(HDC hdc)
{
	_uiBackImg->render(hdc, 0, 0);
}