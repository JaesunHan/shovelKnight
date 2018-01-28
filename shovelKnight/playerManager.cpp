#include "stdafx.h"
#include "playerManager.h"


playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}

HRESULT playerManager::init()
{
	IMAGEMANAGER->addFrameImage("shovelAttack", ".//image//shovelKnight//shovelKnightAttack.bmp", 264, 70, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelClimb", ".//image//shovelKnight//shovelKnightClimb.bmp", 48, 76, 2, 2, true, RGB(255, 0, 255));
	/*IMAGEMANAGER->addFrameImage("shovelDamaged", ".//image//shovelKnight//shovelKnightDamaged.bmp", 40, 76, 1, 2, true, RGB(255, 0, 255));*/
	IMAGEMANAGER->addFrameImage("shovelDamaged", ".//image//shovelKnight//shovelKnightDamaged2.bmp", 80, 76, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelDead", ".//image//shovelKnight//shovelKnightDead.bmp", 126, 68, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelDownAttack", ".//image//shovelKnight//shovelKnightDownAttack.bmp", 24, 70, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelIdle", ".//image//shovelKnight//shovelKnightIdle.bmp", 34, 62, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelJump", ".//image//shovelKnight//shovelKnightJump.bmp", 68, 68, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelMove", ".//image//shovelKnight//shovelKnightRunning.bmp", 276, 66, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelShine", ".//image//shovelKnight//shovelKnightShine.bmp", 102, 62, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelRooting", ".//image//shovelKnight//shovelKnightTreasureGet.bmp", 114, 64, 3, 2, true, RGB(255, 0, 255));



	_p1 = new player1;
	_p1->init(200 , 150);

	return S_OK;
}

void playerManager::release()
{
}

void playerManager::update()
{
	_p1->update();
}

void playerManager::render()
{
	_p1->render();
}
