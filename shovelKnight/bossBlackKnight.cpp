#include "stdafx.h"
#include "bossBlackKnight.h"


bossBlackKnight::bossBlackKnight()
{
}
bossBlackKnight::~bossBlackKnight()
{
}

void bossBlackKnight::enemyInitSet()
{
	_enemyType = ENEMY_BLACKKNIGHT;

	_speed = BLACKKNIGHTSPEED;

	_img = IMAGEMANAGER->addFrameImage("darkKnight", ".//image//monster//darkKnight.bmp", _x, _y, 532, 602, 7, 14, true, RGB(255, 0, 255));

	_status = ENEMY_LEFT_IDLE;

	//========================================================================================= 에니메이션

	int rightIdle[] = { 18, 19 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightRightIdle", "darkKnight", rightIdle, 2, 3, true);

	int leftIdle[] = { 25, 26 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightLeftIdle", "darkKnight", leftIdle, 2, 3, true);

	int rightMove[] = { 0, 1, 2, 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightRightMove", "darkKnight", rightMove, 6, 7, true);

	int leftMove[] = { 7, 8, 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightLeftMove", "darkKnight", leftMove, 6, 7, true);

	int rightAttack[] = { 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightRightAttack", "darkKnight", rightAttack, 4, 5, false);

	int leftAttack[] = { 21, 22, 23, 24 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightLeftAttack", "darkKnight", leftAttack, 4, 5, false);

	int rightJumpAttack[] = { 28, 29, 30, 31, 32 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightRightJumpAttack", "darkKnight", rightJumpAttack, 5, 6, false);

	int leftJumpAttack[] = { 35, 36, 37, 38, 39 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightLeftJumpAttack", "darkKnight", leftJumpAttack, 5, 6, false);

	int rightBackMove[] = { 46 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightRightBackMove", "darkKnight", rightBackMove, 1, 10, false);

	int leftBackMove[] = { 53 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightLeftBackMove", "darkKnight", leftBackMove, 1, 10, false);

	int rightAttackFire[] = { 42, 43, 44, 45  };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightRightAttackFire", "darkKnight", rightAttackFire, 4, 5, false);

	int leftAttackFire[] = { 49, 50, 51, 52 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightLeftAttackFire", "darkKnight", leftAttackFire, 4, 5, false);

	int rightHit[] = { 70, 71, 72, 73, 74, 75, 76 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightRightHit", "darkKnight", rightHit, 7, 8, false);

	int leftHit[] = { 77, 78, 79, 80, 81, 82, 83 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightLeftHit", "darkKnight", leftHit, 7, 8, false);

	int rightDead[] = { 84, 85, 86, 87, 88 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightRightDead", "darkKnight", rightDead, 5, 6, false);

	int leftDead[] = { 91, 92, 93, 94, 95 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightLeftDead", "darkKnight", leftDead, 5, 6, false);

	//=========================================================================================

	_width = 18;
	_height = 35;
	_isDead = false;
	_isDeadVanish = false;
	_vanishTime = 1;
	_direction = false;
	_gravity = 0.0f;
	_directionCount = 1;
	_enemyHp = 12;
	_isHit = false;
	_isCountStop = false;
	_playerFind = false;
	_isAttack = false;

	_rc = RectMakeCenter(_x, _y, _width, _height);
	_anim = KEYANIMANAGER->findAnimation("darkKnightLeftIdle");

	_pixelC = new pixelCollision;
	_pixelC->init(_rc, _x, _y);

	_jump = new jump;
	_jump->init();
}


HRESULT bossBlackKnight::init(float x, float y)
{
	_x = x;
	_y = y;
	_patternTypeNum = ENEMY_BASIC;
	enemyInitSet();

	return S_OK;
}


HRESULT bossBlackKnight::init(float x, float y, int patternType)
{
	_x = x;
	_y = y;
	_patternTypeNum = patternType;

	enemyInitSet();

	return S_OK;
}


void bossBlackKnight::update()					 
{
	if (_status != ENEMY_LEFT_HIT && _status != ENEMY_RIGHT_HIT)
	{
		_previousStatus = _status; //직전 에너미 상태 저장
	}

	//상태값에 따른 에니메이션 및 움직임
	move();


	//플레이어가 일정거리 안으로 들어오면
	if (isPlayerFind(_x, 100)) _playerFind = true;


	//공격 움직임 패턴
	enemyPattern(_patternTypeNum);


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


	//데미지 설정
	if (_isHit && !_isHitDelayTime)
	{
		_enemyHp--;
		_isHitDelayTime = true;

		if (_direction)
		{
			_status = ENEMY_RIGHT_HIT;
		}
		else
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

void bossBlackKnight::draw()
{
	if (_direction)
	{
		CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left - 5, _rc.top - 9);
	}
	else
	{
		CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left - 19, _rc.top - 9);
	}

	//TTTextOut(CAMERAMANAGER->getX(_rc.left), CAMERAMANAGER->getY(_y - 30), "HP", _enemyHp);
}

void bossBlackKnight::move()
{
	//상태값에 따른 에니메이션 및 움직임
	switch (_status)
	{
		case ENEMY_LEFT_IDLE:

			_anim = KEYANIMANAGER->findAnimation("darkKnightLeftIdle");
			if (!_anim->isPlay()) _anim->start();


		break;
		case ENEMY_RIGHT_IDLE:

			_anim = KEYANIMANAGER->findAnimation("darkKnightRightIdle");
			if (!_anim->isPlay()) _anim->start();


		break;
		case ENEMY_LEFT_MOVE:
		_direction = false;

			_anim = KEYANIMANAGER->findAnimation("darkKnightLeftMove");
			if (!_anim->isPlay()) _anim->start();


			_speed = BLACKKNIGHTSPEED;
			_x -= _speed;
		break;
		case ENEMY_RIGHT_MOVE:
			_direction = true;

			_anim = KEYANIMANAGER->findAnimation("darkKnightRightMove");
			if (!_anim->isPlay()) _anim->start();


			_speed = BLACKKNIGHTSPEED;
			_x += _speed;
		break;
		case ENEMY_LEFT_BACK_MOVE:

			_anim = KEYANIMANAGER->findAnimation("darkKnightLeftBackMove");
			if (!_anim->isPlay()) _anim->start();


			_speed = BLACKKNIGHTSPEED;
			_x += _speed;
		break;
		case ENEMY_RIGHT_BACK_MOVE:
	
			_anim = KEYANIMANAGER->findAnimation("darkKnightRightBackMove");
			if (!_anim->isPlay()) _anim->start();
	
	
			_speed = BLACKKNIGHTSPEED;
			_x -= _speed;
		break;
		case ENEMY_LEFT_ATTACK:
			
			_anim = KEYANIMANAGER->findAnimation("darkKnightLeftAttack");
			if (!_anim->isPlay()) _anim->start();

		break;
		case ENEMY_RIGHT_ATTACK:

			_anim = KEYANIMANAGER->findAnimation("darkKnightRightAttack");
			if (!_anim->isPlay()) _anim->start();

		break;
		case ENEMY_LEFT_JUMP_ATTACK:

			_anim = KEYANIMANAGER->findAnimation("darkKnightLeftJumpAttack");
			if (!_anim->isPlay()) _anim->start();

		break;
		case ENEMY_RIGHT_JUMP_ATTACK:

			_anim = KEYANIMANAGER->findAnimation("darkKnightRightJumpAttack");
			if (!_anim->isPlay()) _anim->start();

		break;
		case ENEMY_LEFT_FIRE_ATTACK:

			_anim = KEYANIMANAGER->findAnimation("darkKnightLeftAttackFire");
			if (!_anim->isPlay()) _anim->start();

		break;
		case ENEMY_RIGHT_FIRE_ATTACK:

			_anim = KEYANIMANAGER->findAnimation("darkKnightRightAttackFire");
			if (!_anim->isPlay()) _anim->start();

		break;
		case ENEMY_RIGHT_HIT:
			_anim = KEYANIMANAGER->findAnimation("darkKnightRightHit");
			if (!_anim->isPlay())
			{
				_anim->start();
				_jump->jumping(&_x, &_y, 2.0f, 0.7f);
			}
	
			//움직임: 뒤로 점핑하면서 죽기
			if (_jump->getIsJumping())
			{
				_speed = BLACKKNIGHTSPEED * 3;
				_speed -= 0.4;
				_x -= _speed;
				_jump->update();
			}
			else
			{
				_status = _previousStatus;
			}

		break;
		case ENEMY_LEFT_HIT:
			_anim = KEYANIMANAGER->findAnimation("darkKnightLeftHit");
			if (!_anim->isPlay())
			{
				_anim->start();
				_jump->jumping(&_x, &_y, 2.0f, 0.7f);
			}

			//움직임: 뒤로 점핑하면서 죽기
			if (_jump->getIsJumping())
			{
				_speed = BLACKKNIGHTSPEED * 3;
				_speed -= 0.4;
				_x += _speed;
				_jump->update();
			}
			else
			{
				_status = _previousStatus;
			}


		break;
		case ENEMY_LEFT_DEAD:

			_anim = KEYANIMANAGER->findAnimation("darkKnightLeftDead");

			//에니메이션
			if (!_anim->isPlay() && !_isDead)
			{
				_anim->start();
				_isDead = true;
				_jump->jumping(&_x, &_y, 2.0f, 0.7f);
			}

			//움직임: 뒤로 점핑하면서 죽기
			if (_isDead && _jump->getIsJumping() == true)
			{
				_speed = BLACKKNIGHTSPEED * 3;
				_x += _speed;
				_jump->update();
			}
			//벡터에서 지울 불값 설정
			if (_isDead && _jump->getIsJumping() == false)
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

			_anim = KEYANIMANAGER->findAnimation("darkKnightRightDead");

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
				_speed = BLACKKNIGHTSPEED * 3;
				_x -= _speed;
				_jump->update();
			}

			//벡터에서 지울 불값 설정
			if (_isDead && _jump->getIsJumping() == false)
			{
				_vanishTime++;
				if (_vanishTime % DEADCOUNT == 0)
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

void bossBlackKnight::enemyPattern(int _patternTypeNum)
{
	switch (_patternTypeNum)
	{
		case ENEMY_BASIC:

		break;
		case ENEMY_PATROL:

		break;
		case ENEMY_LEFT_FOWARD:

		break;
		case ENEMY_RIGHT_FOWARD:

		break;
	}
}