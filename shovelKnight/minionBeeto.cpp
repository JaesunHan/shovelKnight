#include "stdafx.h"
#include "minionBeeto.h"


minionBeeto::minionBeeto()
{
}


minionBeeto::~minionBeeto()
{
}


HRESULT minionBeeto::init(string imgKeyString, char* imgFileName, float x, float y, int totalWidth, int totalHeight, int frameX, int frameY)
{
	_imgKeyString = imgKeyString;
	_imgFileName = imgFileName;
	_x = x;
	_y = y;

	_img = IMAGEMANAGER->addFrameImage(_imgKeyString, _imgFileName, _x, _y, totalWidth, totalHeight, frameX, frameY, true, RGB(255, 0, 255));

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_status = ENEMY_LEFT_STOP;

	//========================================================================================= 에니메이션

	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("beetoRightStop", "beeto", rightStop, 1, 10, false);

	int leftStop[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("beetoLeftStop", "beeto", rightStop, 1, 10, false);

	int rightMove[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("beetoRightMove", "beeto", rightStop, 4, 8, true);

	int leftMove[] = { 5, 6, 7, 8 };
	KEYANIMANAGER->addArrayFrameAnimation("beetoRightMove", "beeto", rightStop, 4, 8, true);

	int rightDead[] = { 9, 10 };
	KEYANIMANAGER->addArrayFrameAnimation("beetoRightMove", "beeto", rightStop, 2, 4, true);

	int leftDead[] = { 13, 14 };
	KEYANIMANAGER->addArrayFrameAnimation("beetoRightMove", "beeto", rightStop, 2, 4, true);

	//=========================================================================================

	_width = _img->getFrameWidth();
	_height = _img->getFrameHeight();

	_anim = KEYANIMANAGER->findAnimation("beetoLeftStop");

	return S_OK;
}

void minionBeeto::move()
{

}

