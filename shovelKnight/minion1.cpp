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
	KEYANIMANAGER->addArrayFrameAnimation("beetoRightDead", "beeto", rightDead, 2, 3, false);

	int leftDead[] = { 12, 13 };
	KEYANIMANAGER->addArrayFrameAnimation("beetoLeftDead", "beeto", leftDead, 2, 3, false);

	//=========================================================================================

	_width = _img->getFrameWidth();
	_height = _img->getFrameHeight();
	_isDead = false;
	_isDeadVanish = false;
	_vanishTime = 1;
	_direction = false;

	_anim = KEYANIMANAGER->findAnimation("beetoLeftMove");

	_jump = new jump;
	_jump->init();

	_pixelC = new pixelCollision;
	_pixelC->init("bgMap", _rc, _x, _y, _speed);

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
	//enemyX좌표 픽셀충돌시 방향전환
	if (_pixelC->pixelDirection()) _status = ENEMY_RIGHT_MOVE;
	else _status = ENEMY_LEFT_MOVE;


	//상태값에 따른 에니메이션 및 움직임
	switch (_status)
	{
		case ENEMY_LEFT_MOVE:
			_direction = false;

			_anim = KEYANIMANAGER->findAnimation("beetoLeftMove");
			if (!_anim->isPlay()) _anim->start();

			_speed = BEETOSPEED;
			_x -= _speed;
		break;
		case ENEMY_RIGHT_MOVE:
			_direction = true;

			_anim = KEYANIMANAGER->findAnimation("beetoRightMove");
			if (!_anim->isPlay()) _anim->start();

			_speed = BEETOSPEED;
			_x += _speed;
		break;
		case ENEMY_LEFT_DEAD:
			_anim = KEYANIMANAGER->findAnimation("beetoLeftDead");

			//에니메이션
			if (!_anim->isPlay() && !_isDead)
			{
				_anim->start();
				_isDead = true;
				_jump->jumping(&_x, &_y, 8.0f, 0.9f);
			}

			//움직임: 뒤로 점핑하면서 죽기
			if (_isDead && _jump->getIsJumping() == true)
			{
				_speed = BEETOSPEED;
				_x += _speed;
				_jump->update();
			}
			//벡터에서 지울 불값 설정
			if (_isDead && _jump->getIsJumping() == false)
			{
				_vanishTime++;
				if (_vanishTime % 20 == 0)
				{
					_isDeadVanish = true;
					_vanishTime = 1;
				}
			}
		break;
		case ENEMY_RIGHT_DEAD:
			_anim = KEYANIMANAGER->findAnimation("beetoRighttDead");

			//에니메이션
			if (!_anim->isPlay() && !_isDead)
			{
				_anim->start();
				_isDead = true;
				_jump->jumping(&_x, &_y, 15.0f, 0.4f);
			}

			//움직임: 뒤로 점핑하면서 죽기
			if (_isDead && _jump->getIsJumping() == true)
			{
				_speed = BEETOSPEED;
				_x -= _speed;
				_jump->update();
			}
		break;
	}


	_rc = RectMakeCenter(_pixelC->pixelCollisonX(_direction), _pixelC->pixelCollisonY(), _width, _height);
}


