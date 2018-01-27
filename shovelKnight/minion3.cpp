#include "stdafx.h"
#include "minion3.h"


minion3::minion3()
{
}


minion3::~minion3()
{
}

HRESULT minion3::init(float x, float y)
{
	_enemyType = ELEMY_DRAKE;

	_x = x;
	_y = y;
	_speed = 0.0f;

	_img = IMAGEMANAGER->addFrameImage("drake", ".//image//monster//Divedrake.bmp", _x, _y, 111, 256, 3, 8, true, RGB(255, 0, 255));

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_status = ENEMY_LEFT_MOVE;

	//========================================================================================= 에니메이션

	int rightMove[] = { 0, 1, 2};
	KEYANIMANAGER->addArrayFrameAnimation("drakeRightMove", "drake", rightMove, 3, 4, true);

	int leftMove[] = { 3, 4, 5};
	KEYANIMANAGER->addArrayFrameAnimation("drakeLeftMove", "drake", leftMove, 3, 4, true);

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


	_anim = KEYANIMANAGER->findAnimation("drakeLeftMove");


	return S_OK;
}

void minion3::update()
{

	//좌우 움직임 패턴: 방향전환
	_directionCount++;
	if (_directionCount % 50 == 0)
	{
		if (_status == ENEMY_LEFT_MOVE)
		{
			_status = ENEMY_LEFT_IDLE;
		}
		else if (_status == ENEMY_RIGHT_MOVE)
		{
			_status = ENEMY_RIGHT_IDLE;
		}
	}
	if (_directionCount % 120 == 0)
	{
		if (_status == ENEMY_LEFT_IDLE)
		{
			_status = ENEMY_RIGHT_MOVE;
		}
		else if (_status == ENEMY_RIGHT_IDLE)
		{
			_status = ENEMY_LEFT_MOVE;
		}

		_directionCount = 1;
	}


	//상태값에 따른 에니메이션 및 움직임
	move();
}

void minion3::move()
{
	//상태값에 따른 에니메이션 및 움직임
	switch (_status)
	{
		case ENEMY_LEFT_IDLE:
			_direction = false;

			_anim = KEYANIMANAGER->findAnimation("drakeLeftMove");


		break;
		case ENEMY_RIGHT_IDLE:
			_direction = true;

			_anim = KEYANIMANAGER->findAnimation("drakeRightMove");

		break;
		case ENEMY_LEFT_MOVE:
			_direction = false;

			_anim = KEYANIMANAGER->findAnimation("drakeLeftMove");
			if (!_anim->isPlay()) _anim->start();

			//_angle = PI * 1.25;
			_angle -= 0.1f;
			_speed = DRAKESPEED;
			_speed -= 0.3f;
			_x -= _speed;
			_y += -sinf(_angle) * _speed;
		break;
		case ENEMY_RIGHT_MOVE:
			_direction = true;

			_anim = KEYANIMANAGER->findAnimation("drakeRightMove");
			if (!_anim->isPlay()) _anim->start();

			//_angle = PI / 4;
			_angle += 0.15f;
			_speed = DRAKESPEED;
			_speed -= 0.3f;
			_x += _speed;
			_y += -sinf(_angle) * _speed;
		break;
		case ENEMY_LEFT_DEAD:
			_anim = KEYANIMANAGER->findAnimation("drakeLeftMove");

			//에니메이션
			if (!_anim->isPlay() && !_isDead)
			{
				_anim->start();
				_isDead = true;
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
			_anim = KEYANIMANAGER->findAnimation("drakeRightMove");


			//에니메이션
			if (!_anim->isPlay() && !_isDead)
			{
				_anim->start();
				_isDead = true;
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


	//렉트위치 update
	_rc = RectMakeCenter(_x, _y, _width, _height);
}

