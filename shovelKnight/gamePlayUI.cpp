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
	_uiBackImg = IMAGEMANAGER->addImage("GamePlayUI", "./image/UI/UI.bmp", 0, 0, 800, 35, true, RGB(255, 0, 255));
	
	//HP 출력에 사용될 이미지 3개 : 풀 HP, 하프 HP, 엠티 HP
	_emptyHP = IMAGEMANAGER->addImage("emptyHPBlock", "./image/UI/Hud_empty.bmp", 16, 16, true, RGB(255, 0, 255));
	_fullHP = IMAGEMANAGER->addImage("fullHPBlock", "./image/UI/Hud_hpFull.bmp", 16, 16, true, RGB(255, 0, 255));
	_halfHP = IMAGEMANAGER->addImage("halfHPBlock", "./image/UI/Hud_hpHalf.bmp", 16, 16, true, RGB(255, 0, 255));

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
	SetTextColor(hdc, RGB(255, 255, 255));
	TCHAR goldText[128];
	wsprintf(goldText, "%d", _gold);
	TextOut(hdc, 30, 15, goldText, strlen(goldText));
	TCHAR manaText[128];
	wsprintf(manaText, "%d", _mana);
	TextOut(hdc, 190, 15, manaText, strlen(manaText));
	//라이프 출력
	//기본으로 빈거 N개 깔기
	for (int i = 0; i < _maxLife / 2; ++i)
	{
		_emptyHP->render(hdc, 330 + 16 * i, 15);
	}
	for (int i = 0; i < _life / 2; ++i)
	{
		_fullHP->render(hdc, 330 + 16 * i, 15);
	}
	if (_life % 2 == 1)
	{
		_halfHP->render(hdc, 330 + 16 * (_life / 2), 15);
	}
}
void gamePlayUI::setPlayerInfo(int* idx)
{
	_playerIdx = *idx;
	char* filename = "playerList";
	char subjectName[256];
	wsprintf(subjectName, "player%d", _playerIdx);

	_life = INIDATA->loadDataInterger(filename, subjectName, "HP");
	_maxLife = INIDATA->loadDataInterger(filename, subjectName, "MaxHP");
	_mana = INIDATA->loadDataInterger(filename, subjectName, "Mana");
	_gold = INIDATA->loadDataInterger(filename, subjectName, "Money");
}