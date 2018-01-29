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
	_enemyType = ENEMY_BEETO;

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
	_gravity = 0.0f;
	_isJump = false;
	_jumpCount = 1;
	_enemyHp = 1;
	_isHit = false;
	_previousStatus = _status;

	_anim = KEYANIMANAGER->findAnimation("beetoLeftMove");

	_jump = new jump;
	_jump->init();

	_pixelC = new pixelCollision;
	_pixelC->init(_rc, _x, _y);

	return S_OK;
}

void minion1::update()
{
	//============================================================ 피격 테스트
	//if (KEYMANAGER->isOnceKeyDown('P'))
	//{
	//	_isHit = true;
	//}
	//============================================================


	if (_status != ENEMY_LEFT_HIT && _status != ENEMY_RIGHT_HIT)
	{
		_previousStatus = _status; //직전 에너미 상태 저장
	}

	//상태값에 따른 에니메이션 및 움직임
	move();


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
			_status = ENEMY_RIGHT_MOVE;
		}
		else            //현상태가 왼쪽이면
		{
			_status = ENEMY_LEFT_MOVE;
		}

		_pixelC->setDirectionChange(false);  //초기화
	}
	//=============================================================


	//데미지 설정
	if (_isHit)
	{
		if (_direction)  //현상태가 오른쪽이면
		{
			_status = ENEMY_RIGHT_HIT;
		}
		else            //현상태가 왼쪽이면
		{
			_status = ENEMY_LEFT_HIT;
		}

		_enemyHp--;
		_isHit = false;
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


void minion1::move()
{
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
		case ENEMY_LEFT_JUMP_DEAD: ENEMY_RIGHT_JUMP_DEAD:
			if (_direction)
			{
				_anim = KEYANIMANAGER->findAnimation("beetoRightDead");
			}
			else
			{
				_anim = KEYANIMANAGER->findAnimation("beetoLeftDead");
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


