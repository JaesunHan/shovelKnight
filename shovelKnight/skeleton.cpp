#include "stdafx.h"
#include "skeleton.h"


skeleton::skeleton()
{
}
skeleton::~skeleton()
{
}

HRESULT skeleton::init(float x, float y)
{
	_enemyType = ENEMY_SKELETON;

	_x = x;
	_y = y;
	_speed = 0.0f;

	_img = IMAGEMANAGER->addFrameImage("skeleton", ".//image//monster//skeleton.bmp", _x, _y, 240, 185, 5, 5, true, RGB(255, 0, 255));

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_status = ENEMY_LEFT_IDLE;

	//========================================================================================= 에니메이션

	int rightIdle[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("skeletonRightIdle", "skeleton", rightIdle, 2, 3, true);

	int leftIdle[] = { 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("skeletonLeftIdle", "skeleton", leftIdle, 2, 3, true);

	int rightMove[] = { 5, 6, 7, 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("skeletonRightMove", "skeleton", rightMove, 5, 6, true);

	int leftMove[] = { 10, 11, 12, 13, 14 };
	KEYANIMANAGER->addArrayFrameAnimation("skeletonLeftMove", "skeleton", leftMove, 5, 6, true);

	int rightAttack[] = { 15, 16 };
	KEYANIMANAGER->addArrayFrameAnimation("skeletonRightAttack", "skeleton", rightAttack, 2, 3, false);

	int leftAttack[] = { 17, 18 };
	KEYANIMANAGER->addArrayFrameAnimation("skeletonLeftAttack", "skeleton", leftAttack, 2, 3, false);

	int rightHit[] = { 20, 21 };
	KEYANIMANAGER->addArrayFrameAnimation("skeletonRightHit", "skeleton", rightHit, 2, 3, false);

	int leftHit[] = { 22, 23 };
	KEYANIMANAGER->addArrayFrameAnimation("skeletonLeftHit", "skeleton", leftHit, 2, 3, false);

	//=========================================================================================

	_width = _img->getFrameWidth();
	_height = _img->getFrameHeight();
	_isDead = false;
	_isDeadVanish = false;
	_vanishTime = 1;
	_direction = false;
	_gravity = 0.0f;
	_directionCount = 1;
	_angle = 0.0f;
	_isHit = false;


	_anim = KEYANIMANAGER->findAnimation("skeletonLeftIdle");

	_jump = new jump;
	_jump->init();

	_pixelC = new pixelCollision;
	_pixelC->init(_rc, _x, _y);


	return S_OK;
}

void skeleton::update()
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

void skeleton::move()
{

	//상태값에 따른 에니메이션 및 움직임
	switch (_status)
	{
		case ENEMY_LEFT_IDLE:

			_anim = KEYANIMANAGER->findAnimation("skeletonLeftIdle");
			if (!_anim->isPlay()) _anim->start();


		break;
		case ENEMY_RIGHT_IDLE:

			_anim = KEYANIMANAGER->findAnimation("skeletonRightIdle");
			if (!_anim->isPlay()) _anim->start();


		break;
		case ENEMY_LEFT_MOVE:
			_direction = false;

			_anim = KEYANIMANAGER->findAnimation("skeletonLeftMove");
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

			_speed = SKELETONSPEED;
			_x -= _speed;
		break;
		case ENEMY_RIGHT_MOVE:
			_direction = true;

			_anim = KEYANIMANAGER->findAnimation("skeletonRightMove");
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

			_speed = SKELETONSPEED;
			_x += _speed;
		break;
		case ENEMY_LEFT_ATTACK:

			_direction = false;

			_anim = KEYANIMANAGER->findAnimation("skeletonLeftAttack");
			if (!_anim->isPlay()) _anim->start();

		break;
		case ENEMY_RIGHT_ATTACK:

			_direction = false;

			_anim = KEYANIMANAGER->findAnimation("skeletonRightAttack");
			if (!_anim->isPlay()) _anim->start();

		break;
		case ENEMY_RIGHT_HIT:

			_anim = KEYANIMANAGER->findAnimation("skeletonRightHit");
			if (!_anim->isPlay())
			{
				_anim->start();
				_isHit = true;
				_jump->jumping(&_x, &_y, 5.0f, 0.7f);
			}

			//움직임: 뒤로 점핑하면서 죽기
			if (_isHit && _jump->getIsJumping() == true)
			{
				_speed = SKELETONSPEED * 2;
				_x -= _speed;
				_jump->update();
			}

			//----------------------------------- hit action후 상태변경
			if (!_anim->isPlay() && _isHit)
			{
				if (_direction)
				{
					_status = ENEMY_RIGHT_MOVE;
					_isHit = false;
				}
				else
				{
					_status = ENEMY_LEFT_MOVE;
					_isHit = false;
				}
			}

		break;
		case ENEMY_LEFT_HIT:

			_anim = KEYANIMANAGER->findAnimation("skeletonLeftHit");
			if (!_anim->isPlay())
			{
				_anim->start();
				_isHit = true;
				_jump->jumping(&_x, &_y, 5.0f, 0.7f);
			}

			//움직임: 뒤로 점핑하면서 죽기
			if (_isHit && _jump->getIsJumping() == true)
			{
				_speed = SKELETONSPEED * 2;
				_x += _speed;
				_jump->update();
			}

			//----------------------------------- hit action후 상태변경
			if (!_anim->isPlay() && _isHit)
			{
				if (_direction)
				{
					_status = ENEMY_RIGHT_MOVE;
					_isHit = false;
				}
				else
				{
					_status = ENEMY_LEFT_MOVE;
					_isHit = false;
				}
			}

		break;
		case ENEMY_LEFT_DEAD:

			_anim = KEYANIMANAGER->findAnimation("skeletonLeftHit");

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
				_speed = SKELETONSPEED;
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

			_anim = KEYANIMANAGER->findAnimation("skeletonRightHit");

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
				_speed = SKELETONSPEED;
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
