#include "stdafx.h"
#include "selectScene.h"


selectScene::selectScene()
{
}


selectScene::~selectScene()
{

}

HRESULT selectScene::init()
{
	IMAGEMANAGER->addImage("profileBackGround", "backGround(profileScene).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("campaignBackGround", "backGround(campaignScene).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("titleBackGround", "backGround(titleScene).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("삽기사선택", "characterSelect(shovel).bmp", 550, 550, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("삽기사선택안함", "characterSelect(shovel)black.bmp", 550, 550, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("역병기사선택", "characterSelect(plague).bmp", 550, 550, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("역병기사선택안함", "characterSelect(plague)black.bmp", 550, 550, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("악령기사선택", "characterSelect(specter).bmp", 550, 550, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("악령기사선택안함", "characterSelect(specter)black.bmp", 550, 550, true, RGB(255, 0, 255));
	characterSelect[0].image = IMAGEMANAGER->findImage("삽기사선택안함");
	characterSelect[1].image = IMAGEMANAGER->findImage("역병기사선택안함");
	characterSelect[2].image = IMAGEMANAGER->findImage("악령기사선택안함");
	for (int i = 0; i < 3; i++)
	{
		characterSelect[i].isSelect = false;
		characterSelect[i].x = WINSIZEX / 2 - 825 + 550 * i;
		characterSelect[i].y = WINSIZEY / 2 - 290;
	}
	_selectX = WINSIZEX / 2 - 275;
	_selectY = WINSIZEY / 2 - 290;

	_selectMoveLeft = false;
	_selectMoveRight = false;

	return S_OK;
}

void selectScene::release()
{

}

void selectScene::update()
{
	for (int i = 0; i < 3; i++)
	{
		if (characterSelect[i].x == _selectX)
		{
			characterSelect[i].isSelect = true;
		}
		else
		{
			characterSelect[i].isSelect = false;
		}
	}

	if (characterSelect[0].isSelect) characterSelect[0].image = IMAGEMANAGER->findImage("삽기사선택");
	else characterSelect[0].image = IMAGEMANAGER->findImage("삽기사선택안함");
	if (characterSelect[1].isSelect) characterSelect[1].image = IMAGEMANAGER->findImage("역병기사선택");
	else characterSelect[1].image = IMAGEMANAGER->findImage("역병기사선택안함");
	if (characterSelect[2].isSelect) characterSelect[2].image = IMAGEMANAGER->findImage("악령기사선택");
	else characterSelect[2].image = IMAGEMANAGER->findImage("악령기사선택안함");

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (_selectMoveRight) _selectMoveRight = false;
		_selectMoveLeft = true;
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (_selectMoveLeft) _selectMoveLeft = false;
		_selectMoveRight = true;
	}

	if (_selectMoveLeft)
	{
		for (int i = 0; i < 3; i++)
		{
			characterSelect[i].x -= 5;
			if (characterSelect[i].x == _selectX) _selectMoveLeft = false;
		}
	}
	if (_selectMoveRight)
	{
		for (int i = 0; i < 3; i++)
		{
			characterSelect[i].x += 5;
			if (characterSelect[i].x == _selectX) _selectMoveRight = false;
		}
	}

	if (_selectMoveRight)
	{
		if (characterSelect[0].x> WINSIZEX) characterSelect[0].x = characterSelect[1].x - 550;
		if (characterSelect[1].x> WINSIZEX) characterSelect[1].x = characterSelect[2].x - 550;
		if (characterSelect[2].x> WINSIZEX) characterSelect[2].x = characterSelect[0].x - 550;
	}
	if (_selectMoveLeft)
	{
		if (characterSelect[0].x + IMAGEWIDTH < 0) characterSelect[0].x = characterSelect[2].x + 550;
		if (characterSelect[1].x + IMAGEWIDTH < 0) characterSelect[1].x = characterSelect[0].x + 550;
		if (characterSelect[2].x + IMAGEWIDTH < 0) characterSelect[2].x = characterSelect[1].x + 550;
	}
	for (int i = 0; i < 3; i++)
	{
		if (characterSelect[i].isSelect)
		{
			if (KEYMANAGER->isOnceKeyDown('K'))
			{
				cbSceneChange();
			}
		}
	}

}

void selectScene::render()
{
	IMAGEMANAGER->findImage("campaignBackGround")->render(getMemDC(), 0, 0);
	for (int i = 0; i < 3; i++)
	{
		characterSelect[i].image->render(getMemDC(), characterSelect[i].x, characterSelect[i].y);
	}
}

void selectScene::cbSceneChange()
{
	SCENEMANAGER->changeScene("profile");
}