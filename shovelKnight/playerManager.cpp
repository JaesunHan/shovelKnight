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
	IMAGEMANAGER->addFrameImage("shovelAttack", ".//image//shovelKnigt//shovelKnightAttack.bmp", 264, 70, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelClimb", ".//image//shovelKnigt//shovelKnightClimb.bmp", 48, 76, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelDamaged", ".//image//shovelKnigt//shovelKnightDamaged.bmp", 40, 76, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelDead", ".//image//shovelKnigt//shovelKnightDead.bmp", 126, 68, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelDownAttack", ".//image//shovelKnigt//shovelKnightDownAttack.bmp", 24, 70, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelIdle", ".//image//shovelKnigt//shovelKnightIdle.bmp", 34, 62, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelJump", ".//image//shovelKnigt//shovelKnightJump.bmp", 68, 68, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelMove", ".//image//shovelKnigt//shovelKnightRunning.bmp", 276, 66, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelShine", ".//image//shovelKnigt//shovelKnightShine.bmp", 102, 62, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovelRooting", ".//image//shovelKnigt//shovelKnightTreasureGet.bmp", 114, 64, 3, 2, true, RGB(255, 0, 255));



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
