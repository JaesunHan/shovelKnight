#include "stdafx.h"
#include "minion1.h"


minion1::minion1()
{
}


minion1::~minion1()
{
}


HRESULT minion1::init(float x, float y)
{
	_x = x;
	_y = y;
	_speed = 0.0f;

	_img = IMAGEMANAGER->addFrameImage("beeto", ".//image//monster//Beeto.bmp", _x, _y, 104, 64, 4, 4, true, RGB(255, 0, 255));

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_status = ENEMY_LEFT_MOVE;

	//========================================================================================= 에니메이션

	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("beetoRightStop", "beeto", rightStop, 1, 10, false);

	int leftStop[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("beetoLeftStop", "beeto", leftStop, 1, 10, false);

	int rightMove[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("beetoRightMove", "beeto", rightMove, 4, 4, true);

	int leftMove[] = { 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("beetoLeftMove", "beeto", leftMove, 4, 4, true);

	int rightDead[] = { 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("beetoRightMove", "beeto", rightDead, 2, 4, true);

	int leftDead[] = { 12, 13 };
	KEYANIMANAGER->addArrayFrameAnimation("beetoLeftMove", "beeto", leftDead, 2, 4, true);

	//=========================================================================================

	_width = _img->getFrameWidth();
	_height = _img->getFrameHeight();

	_anim = KEYANIMANAGER->findAnimation("beetoLeftMove");

	return S_OK;
}

void minion1::update()
{
	//상태값에 따른 에니메이션 및 움직임
	move();

	

	
	KEYANIMANAGER->update();
}

void minion1::move()
{
	//상태값에 따른 에니메이션 및 움직임
	switch (_status)
	{
		case ENEMY_LEFT_STOP:
			_speed = 0.0f;
		break;
		case ENEMY_RIGHT_STOP:
			_speed = 0.0f;
		break;
		case ENEMY_LEFT_MOVE:
			_anim = KEYANIMANAGER->findAnimation("beetoLeftMove");
			if (!_anim->isPlay()) _anim->start();

			_speed = BEETOSPEED;
			_x -= _speed;
			_rc = RectMakeCenter(_x, _y, _width, _height);
		break;
		case ENEMY_RIGHT_MOVE:
			_anim = KEYANIMANAGER->findAnimation("beetoRightMove");
			if (!_anim->isPlay()) _anim->start();

			_speed = BEETOSPEED;
			_x += _speed;
			_rc = RectMakeCenter(_x, _y, _width, _height);
		break;
	}
}


