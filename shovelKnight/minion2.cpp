#include "stdafx.h"
#include "minion2.h"


minion2::minion2()
{
}
minion2::~minion2()
{
}


HRESULT minion2::init(float x, float y)
{
	_enemyType = ENEMY_BLORB;

	_x = x;
	_y = y;
	_speed = 0.0f;

	_img = IMAGEMANAGER->addFrameImage("blorb", ".//image//monster//Blorb.bmp", _x, _y, 80, 162, 4, 6, true, RGB(255, 0, 255));


	_status = ENEMY_LEFT_MOVE;

	//========================================================================================= 에니메이션

	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("blorbRightStop", "blorb", rightStop, 1, 10, false);

	int leftStop[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("blorbLeftStop", "blorb", leftStop, 1, 10, false);

	int rightMove[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("blorbRightMove", "blorb", rightMove, 4, 4, true);

	int leftMove[] = { 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("blorbLeftMove", "blorb", leftMove, 4, 4, true);

	int rightHit[] = { 16, 17, 18, 19 };
	KEYANIMANAGER->addArrayFrameAnimation("blorbRightHit", "blorb", rightHit, 4, 4, false);

	int leftHit[] = { 20, 21, 22, 23 };
	KEYANIMANAGER->addArrayFrameAnimation("blorbLeftHit", "blorb", leftHit, 4, 4, false);

	int rightDead[] = { 8, 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("blorbRightDead", "blorb", rightDead, 4, 4, false);

	int leftDead[] = { 12, 13, 14, 15 };
	KEYANIMANAGER->addArrayFrameAnimation("blorbLeftDead", "blorb", leftDead, 4, 4, false);

	//=========================================================================================

	_width = _img->getFrameWidth();
	_height = 10;
	_isDead = false;
	_isDeadVanish = false;
	_vanishTime = 1;
	_direction = false;
	_gravity = 0.0f;
	_jumpTime = 1;
	_isJump = false;
	_jumpCount = 1;

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _height);

	_anim = KEYANIMANAGER->findAnimation("blorbLeftMove");

	_jump = new jump;
	_jump->init();

	_pixelC = new pixelCollision;
	_pixelC->init(_rc, _x, _y);

	return S_OK;
}

void minion2::update()
{
	//============================================================= 픽셀충돌: 바닥충돌	
	_pixelC->pixelCollisonY(_rc);  //바닥상태 검출

	if (_pixelC->getIsGround())     //상태값에 따른 에네미 상태적용
	{
		_gravity = 0.0f;
		_y = _pixelC->getProbeY();
	}
	else
	{
		if (!_isJump && !_isDead) _gravity += 0.1f;	
		else _gravity = 0.0f;
	}
	//중력적용
	_y += _gravity;
	//============================================================= 픽셀충돌: 벽
	_pixelC->pixelCollisonX(_rc, _direction);  //벽 검출

	if (_pixelC->getDirectionChange())  //벽에 부딪치면
	{
		if (_direction)  //현상태가 오른쪽이면
		{
			_status = ENEMY_LEFT_MOVE;
		}
		else            //현상태가 왼쪽이면
		{
			_status = ENEMY_RIGHT_MOVE;
		}

		_pixelC->setDirectionChange(false);  //초기화
	}
	//=============================================================




	//상태값에 따른 에니메이션 및 움직임
	move();



}


void minion2::draw()
{
	CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left, _rc.top - 18);

	//TTTextOut(CAMERAMANAGER->getX(_rc.left), CAMERAMANAGER->getY(_rc.top - 20), "상태", _status, true);
}


void minion2::move()
{

	//상태값에 따른 에니메이션 및 움직임
	switch (_status)
	{
	case ENEMY_LEFT_MOVE:
		_direction = false;

		_anim = KEYANIMANAGER->findAnimation("blorbLeftMove");
		if (!_anim->isPlay()) _anim->start();

		//----------------------------------- 점프
		_jumpCount++;

		if (_jumpCount % 100 == 0)
		{
			_jump->jumping(&_x, &_y, 5.0f, 0.7f);
			_jumpCount = 1;
			_isJump = true;
		}

		_jump->update();
		//-----------------------------------

		_speed = BLORBSPEED;
		_x -= _speed;
	break;
	case ENEMY_RIGHT_MOVE:
		_direction = true;
		_jumpCount++;

		_anim = KEYANIMANAGER->findAnimation("blorbRightMove");
		if (!_anim->isPlay()) _anim->start();

		//----------------------------------- 점프
		_jumpCount++;

		if (_jumpCount % 100 == 0)
		{
			_jump->jumping(&_x, &_y, 5.0f, 0.7f);
			_jumpCount = 1;
			_isJump = true;
		}

		_jump->update();
		//-----------------------------------

		_speed = BLORBSPEED;
		_x += _speed;
	break;
	case ENEMY_RIGHT_HIT:

		_anim = KEYANIMANAGER->findAnimation("blorbRightHit");
		if (!_anim->isPlay()) _anim->start();


	break;
	case ENEMY_LEFT_HIT:

		_anim = KEYANIMANAGER->findAnimation("blorbLeftHit");
		if (!_anim->isPlay()) _anim->start();


	break;
	case ENEMY_LEFT_DEAD:
		_anim = KEYANIMANAGER->findAnimation("blorbLeftDead");

		//에니메이션
		if (!_anim->isPlay() && !_isDead)
		{
			_anim->start();
			_isDead = true;
			_jump->jumping(&_x, &_y, 7.0f, 0.7f);
		}

		//움직임: 뒤로 점핑하면서 죽기
		if (_isDead && _jump->getIsJumping() == true)
		{
			_speed = BLORBSPEED;
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
		_anim = KEYANIMANAGER->findAnimation("blorbRightDead");


		//에니메이션
		if (!_anim->isPlay() && !_isDead)
		{
			_anim->start();
			_isDead = true;
			_jump->jumping(&_x, &_y, 7.0f, 0.7f);
		}

		//움직임: 뒤로 점핑하면서 죽기
		if (_isDead && _jump->getIsJumping() == true)
		{
			_speed = BLORBSPEED;
			_x -= _speed;
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
	}

	//점프상태 초기화
	if (!_jump->getIsJumping()) _isJump = false;

	//렉트위치 update
	_rc = RectMakeCenter(_x, _y, _width, _height);
}
