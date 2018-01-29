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

	_status = ENEMY_LEFT_MOVE;

	//========================================================================================= 에니메이션

	int rightMove[] = { 0, 1, 2};
	KEYANIMANAGER->addArrayFrameAnimation("drakeRightMove", "drake", rightMove, 3, 4, true);

	int leftMove[] = { 3, 4, 5};
	KEYANIMANAGER->addArrayFrameAnimation("drakeLeftMove", "drake", leftMove, 3, 4, true);

	int rightHit[] = { 12, 13, 14 };
	KEYANIMANAGER->addArrayFrameAnimation("drakeRightHit", "drake", rightHit, 3, 10, false);

	int leftHit[] = { 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("drakeLeftHit", "drake", leftHit, 3, 10, false);

	//=========================================================================================

	_width = 24;
	_height = 15;
	_isDead = false;
	_isDeadVanish = false;
	_vanishTime = 1;
	_direction = false;
	_gravity = 0.0f;
	_directionCount = 1;
	_angle = 0.0f;
	_jumpCount = 1;
	_enemyHp = 2;
	_isHit = false;
	_previousStatus = _status;
	_playerStatus = 0;
	_isHitPlay = false; //타격 에니메이션 플레이 여부
	_isHitDelayTime = false;
	_delayCount = 1;

	_rc = RectMakeCenter(_x, _y, _width, _height);

	_anim = KEYANIMANAGER->findAnimation("drakeLeftMove");


	return S_OK;
}

void minion3::update()
{
	if (_status != ENEMY_LEFT_HIT && _status != ENEMY_RIGHT_HIT)
	{
		_previousStatus = _status; //직전 에너미 상태 저장
	}

	//상태값에 따른 에니메이션 및 움직임
	move();


	//좌우 움직임 패턴: 방향전환
	if (_status != ENEMY_LEFT_HIT && _status != ENEMY_RIGHT_HIT)
	{
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
	}


	//데미지 설정
	if (_isHit && !_isHitDelayTime)
	{
		_enemyHp--;
		_isHitDelayTime = true;

		if (_direction)  //현상태가 오른쪽이면
		{
			_status = ENEMY_RIGHT_HIT;
		}
		else            //현상태가 왼쪽이면
		{
			_status = ENEMY_LEFT_HIT;
		}
	}


	if (_isHitDelayTime)
	{
		_delayCount++;

		if (_delayCount % DELAYTIME == 0)
		{
			_isHitDelayTime = false;
			_isHit = false;
		}
	}


	//hp=0일경우 상태 변경
	if (_enemyHp <= 0)
	{
		if (_playerStatus == 3) //플레이어가 점프상태일 경우
		{
			if (_direction)
			{
				_status = ENEMY_RIGHT_JUMP_DEAD;
			}
			else
			{
				_status = ENEMY_LEFT_JUMP_DEAD;
			}
		}
		else //플레이어가 바닥에서 공격할 경우
		{
			if (_direction)
			{
				_status = ENEMY_RIGHT_DEAD;
			}
			else
			{
				_status = ENEMY_LEFT_DEAD;
			}
		}

	}


}


void minion3::draw()
{

	CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left - 9, _rc.top - 9);

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
		case ENEMY_RIGHT_HIT:

			_anim = KEYANIMANAGER->findAnimation("drakeLeftHit");
			if (!_anim->isPlay())
			{
				_anim->start();
				_speed = DRAKESPEED * 5;
				_speed -= 0.4;
				_x -= _speed;
				_isHitPlay = true;
			}

			if (!_anim->isPlay() && _isHitPlay)
			{
				_jumpCount++;  //에니메이션 플레이 여유타임
				if (_jumpCount % HITCOUNT == 0)
				{
					_status = _previousStatus;
					_jumpCount = 1;
				}
			}


		break;
		case ENEMY_LEFT_HIT:

			_anim = KEYANIMANAGER->findAnimation("drakeRightHit");
			if (!_anim->isPlay())
			{
				_anim->start();
				_speed = DRAKESPEED * 5;
				_speed -= 0.4;
				_x += _speed;
				_isHitPlay = true;
			}
			else
			{
				_jumpCount++;  //에니메이션 플레이 여유타임
				if (_jumpCount % HITCOUNT == 0)
				{
					_status = _previousStatus;
					_jumpCount = 1;
				}
			}

		break;
		case ENEMY_LEFT_DEAD:
			_anim = KEYANIMANAGER->findAnimation("drakeLeftHit");

			//에니메이션
			if (!_anim->isPlay() && !_isDead)
			{
				_anim->start();
				_speed = DRAKESPEED * 10;
				_speed -= 0.4;
				_x += _speed;
				_isDead = true;
			}

			//벡터에서 지울 불값 설정
			if (_isDead)
			{
				_vanishTime++;
				if (_vanishTime % DEADCOUNT == 0)
				{
					_isDeadVanish = true;
					_vanishTime = 1;
				}
			}
		break;
		case ENEMY_RIGHT_DEAD:
			_anim = KEYANIMANAGER->findAnimation("drakeRightHit");


			//에니메이션
			if (!_anim->isPlay() && !_isDead)
			{
				_anim->start();
				_speed = DRAKESPEED * 10;
				_speed -= 0.4;
				_x -= _speed;
				_isDead = true;
			}

			//벡터에서 지울 불값 설정
			if (_isDead)
			{
				_vanishTime++;
				if (_vanishTime % DEADCOUNT == 0)
				{
					_isDeadVanish = true;
					_vanishTime = 1;
				}
			}
		break;
		case ENEMY_LEFT_JUMP_DEAD: ENEMY_RIGHT_JUMP_DEAD:
			if (_direction)
			{
				_anim = KEYANIMANAGER->findAnimation("drakeRightHit");
			}
			else
			{
				_anim = KEYANIMANAGER->findAnimation("drakeLeftHit");
			}


			//에니메이션
			if (!_anim->isPlay() && !_isDead)
			{
				_anim->start();
				_isDead = true;
			}

			//벡터에서 지울 불값 설정
			if (_isDead)
			{
				_vanishTime++;
				if (_vanishTime % 10 == 0)
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

