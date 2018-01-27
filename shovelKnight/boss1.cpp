#include "stdafx.h"
#include "boss1.h"


boss1::boss1()
{
}


boss1::~boss1()
{
}

HRESULT boss1::init(float x, float y)
{
	_x = x;
	_y = y;
	_speed = 0.0f;

	_img = IMAGEMANAGER->addFrameImage("dragon", ".//image//monster//bubbleDragon.bmp", _x, _y, 1074, 623, 6, 7, true, RGB(255, 0, 255));

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_status = ENEMY_LEFT_IDLE;

	//========================================================================================= 에니메이션

	int leftStop[] = { 0, 1, 2, 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("dragonLeftStop", "dragon", leftStop, 6, 6, true);

	int leftForwardMove[] = { 6, 7, 8, 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("dragonLeftForwardMove", "dragon", leftForwardMove, 6, 6, false);

	int leftBackMove[] = { 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("dragonLeftBackMove", "dragon", leftBackMove, 6, 6, false);

	int leftHit[] = { 18, 19, 20 };
	KEYANIMANAGER->addArrayFrameAnimation("dragonLeftHit", "dragon", leftHit, 3, 4, false);

	int leftAttack[] = { 21, 22, 23 };
	KEYANIMANAGER->addArrayFrameAnimation("dragonLeftAttack", "dragon", leftAttack, 3, 4, false);

	//=========================================================================================

	_width = _img->getFrameWidth();
	_height = _img->getFrameHeight();
	_isDead = false;
	_isDeadVanish = false;
	_vanishTime = 1;
	_gravity = 0.0f;
	_directionCount = 1;
	_direction = false;


	_anim = KEYANIMANAGER->findAnimation("dragonLeftStop");


	return S_OK;
}

void boss1::update()
{
	//공격 움직임 패턴
	_directionCount++;

	if (_directionCount % 100 == 0)
	{
		if (_status == ENEMY_LEFT_MOVE)
		{
			_status = ENEMY_LEFT_BACK_MOVE;
		}
		else if (_status == ENEMY_LEFT_BACK_MOVE)
		{
			_status = ENEMY_LEFT_MOVE;
		}
	}
	if (_directionCount % 150 == 0)
	{
		_status = ENMEY_LEFT_ATTACK;

		_directionCount = 1;
	}



	//상태값에 따른 에니메이션 및 움직임
	move();
}


void boss1::move()
{
	//상태값에 따른 에니메이션 및 움직임
	switch (_status)
	{
		case ENEMY_LEFT_IDLE:
			

			_anim = KEYANIMANAGER->findAnimation("dragonLeftStop");
			if (!_anim->isPlay()) _anim->start();


		break;
		case ENEMY_LEFT_MOVE:
			_direction = false;  //앞으로 움직이는 상태

			_anim = KEYANIMANAGER->findAnimation("dragonLeftForwardMove");
			if (!_anim->isPlay()) _anim->start();


			_speed = DRAGONSPEED;
			_x -= _speed;
		break;
		case ENEMY_LEFT_BACK_MOVE:
			_direction = true;  //뒤로 움직이는 상태

			_anim = KEYANIMANAGER->findAnimation("dragonLeftBackMove");
			if (!_anim->isPlay()) _anim->start();


			_speed = DRAGONSPEED;
			_x += _speed;
		break;
		case ENMEY_LEFT_ATTACK:

			_anim = KEYANIMANAGER->findAnimation("dragonLeftAttack");
			if (!_anim->isPlay()) _anim->start();


		break;
		case ENEMY_LEFT_HIT:

			_anim = KEYANIMANAGER->findAnimation("dragonLeftHit");
			if (!_anim->isPlay()) _anim->start();


		break;
		case ENEMY_LEFT_DEAD:

			//_anim = KEYANIMANAGER->findAnimation("");

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
