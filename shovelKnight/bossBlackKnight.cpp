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

	int rightIdle[] = { 89, 90 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightRightIdle", "darkKnight", rightIdle, 2, 3, true);

	int leftIdle[] = { 96, 97 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightLeftIdle", "darkKnight", leftIdle, 2, 3, true);

	int rightSmile[] = { 18, 19 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightRightSmile", "darkKnight", rightSmile, 2, 3, false);

	int leftSmile[] = { 25, 26 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightLeftSmile", "darkKnight", leftSmile, 2, 3, false);

	int rightMove[] = { 0, 1, 2, 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightRightMove", "darkKnight", rightMove, 6, 7, true);

	int leftMove[] = { 7, 8, 9, 10, 11, 12 };
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
	_frameCount = 1;
	_isDialogueEnd = false;
	_isAniPlayEnd = false;
	_patternTrun = 0;
	_jumpCount = 4;
	_patternCount = 0;
	_isFight = false;
	_previousStatus = _status;

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


	//PATTERN TEST
	if (KEYMANAGER->isOnceKeyDown('O'))	_isDialogueEnd = true;

	//다이얼로그가 끝나면
	if (_isDialogueEnd && !_isFight)
	{
		_status = ENEMY_LEFT_SMILE;
		_isFight = true;
	}


	//공격 움직임 패턴
	if (_isDialogueEnd && _isFight)	enemyPattern(_patternTypeNum);



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
			_patternTrun = 0;
		}
	}



	//hp=0일경우 상태 변경
	if (_enemyHp <= 0)
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

void bossBlackKnight::draw()
{

	CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left - 29, _rc.top - 6);

	//TTTextOut(CAMERAMANAGER->getX(_rc.left), CAMERAMANAGER->getY(_y - 30), "패턴", _patternTrun);
}

void bossBlackKnight::move()
{
	//상태값에 따른 에니메이션 및 움직임
	switch (_status)
	{
		case ENEMY_LEFT_IDLE:
			_direction = false;

			_frameCount++;
			_anim = KEYANIMANAGER->findAnimation("darkKnightLeftIdle");
			if (!_anim->isPlay()) _anim->start();

			if (_frameCount % 30 == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_RIGHT_IDLE:
			_direction = true;

			_frameCount++;
			_anim = KEYANIMANAGER->findAnimation("darkKnightRightIdle");
			if (!_anim->isPlay()) _anim->start();

			if (_frameCount % 30 == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_LEFT_SMILE:
			_direction = false;

			_frameCount++;
			_anim = KEYANIMANAGER->findAnimation("darkKnightLeftSmile");
			if (!_anim->isPlay()) _anim->start();

			if (_frameCount % 90 == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_RIGHT_SMILE:
			_direction = true;

			_frameCount++;
			_anim = KEYANIMANAGER->findAnimation("darkKnightRightSmile");
			if (!_anim->isPlay()) _anim->start();

			if (_frameCount % 90 == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_LEFT_MOVE:
			_direction = false;

			_frameCount++;
			_anim = KEYANIMANAGER->findAnimation("darkKnightLeftMove");
			if (!_anim->isPlay()) _anim->start();


			if (_rc.left > 5)
			{
				_speed = BLACKKNIGHTSPEED;
				_x -= _speed;
			}

			if (_frameCount % 10 == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_RIGHT_MOVE:
			_direction = true;

			_frameCount++;
			_anim = KEYANIMANAGER->findAnimation("darkKnightRightMove");
			if (!_anim->isPlay()) _anim->start();

			if (_rc.right < WINSIZEX - 5)
			{
				_speed = BLACKKNIGHTSPEED;
				_x += _speed;
			}

			if (_frameCount % 10 == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_LEFT_BACK_MOVE:
			_frameCount++;
			_anim = KEYANIMANAGER->findAnimation("darkKnightLeftBackMove");
			if (!_anim->isPlay())
			{
				_anim->start();
				_jump->jumping(&_x, &_y, 3.0f, 0.7f);
			}

			//움직임: 뒤로 점핑
			if (_jump->getIsJumping())
			{
				if (_rc.left > 5)
				{
					_speed = BLACKKNIGHTSPEED * 3;
					_speed -= 0.4;
					_x += _speed;
				}
				_jump->update();
			}

			if (_frameCount % 30 == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_RIGHT_BACK_MOVE:
			_frameCount++;
			_anim = KEYANIMANAGER->findAnimation("darkKnightRightBackMove");
			if (!_anim->isPlay())
			{
				_anim->start();
				_jump->jumping(&_x, &_y, 3.0f, 0.7f);
			}

			//움직임: 뒤로 점핑
			if (_jump->getIsJumping())
			{
				if (_rc.right < WINSIZEX - 5)
				{
					_speed = BLACKKNIGHTSPEED * 3;
					_speed -= 0.4;
					_x -= _speed;
				}
				_jump->update();
			}

			if (_frameCount % 30 == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_LEFT_ATTACK:
			_frameCount++;
			_anim = KEYANIMANAGER->findAnimation("darkKnightLeftAttack");
			if (!_anim->isPlay()) _anim->start();

			if (_frameCount % 30 == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_RIGHT_ATTACK:
			_frameCount++;
			_anim = KEYANIMANAGER->findAnimation("darkKnightRightAttack");
			if (!_anim->isPlay()) _anim->start();

			if (_frameCount % 30 == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_LEFT_JUMP_ATTACK:

			_anim = KEYANIMANAGER->findAnimation("darkKnightLeftJumpAttack");
			if (!_anim->isPlay())
			{
				_anim->start();
				_jump->jumping(&_x, &_y, 10.0f, 0.7f);
			}

			//움직임: 뒤로 점핑
			if (_jump->getIsJumping())
			{
				_jump->update();
			}

			//움직임: 전진
			if (_frameCount <= 5)
			{
				if (_rc.left < 10)
				{
					_speed = BLACKKNIGHTSPEED * 10;
					_speed -= 0.4;
					_x -= _speed;
				}
			}

			if (_frameCount % 60 == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_RIGHT_JUMP_ATTACK:
			_frameCount++;
			_anim = KEYANIMANAGER->findAnimation("darkKnightRightJumpAttack");
			if (!_anim->isPlay())
			{
				_anim->start();
				_jump->jumping(&_x, &_y, 10.0f, 0.7f);
			}

			//움직임: 뒤로 점핑
			if (_jump->getIsJumping())
			{
				_jump->update();
			}

			//움직임: 전진
			if (_frameCount <= 5)
			{
				if (_rc.right < WINSIZEX - 10)
				{
					_speed = BLACKKNIGHTSPEED * 10;
					_speed -= 0.4;
					_x += _speed;
				}
			}

			if (_frameCount % 60 == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_LEFT_FIRE_ATTACK:
			_frameCount++;
			_anim = KEYANIMANAGER->findAnimation("darkKnightLeftAttackFire");
			if (!_anim->isPlay()) _anim->start();

			if (_frameCount % 30 == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_RIGHT_FIRE_ATTACK:
			_frameCount++;
			_anim = KEYANIMANAGER->findAnimation("darkKnightRightAttackFire");
			if (!_anim->isPlay()) _anim->start();

			if (_frameCount % 30 == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_RIGHT_HIT:
			_frameCount++;
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

			
			if (_frameCount % HITCOUNT == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_LEFT_HIT:
			_frameCount++;
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


			if (_frameCount % HITCOUNT == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_LEFT_DEAD:
			_frameCount++;
			_anim = KEYANIMANAGER->findAnimation("darkKnightLeftDead");

			//에니메이션
			if (!_anim->isPlay() && !_isDead)
			{
				_anim->start();
				_isDead = true;
				_jump->jumping(&_x, &_y, 4.0f, 0.7f);
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
			
			if (_frameCount % DEADCOUNT == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
			}
		break;
		case ENEMY_RIGHT_DEAD:
			_frameCount++;
			_anim = KEYANIMANAGER->findAnimation("darkKnightRightDead");

			//에니메이션
			if (!_anim->isPlay() && !_isDead)
			{
				_anim->start();
				_isDead = true;
				_jump->jumping(&_x, &_y, 4.0f, 0.7f);
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

			if (_frameCount % DEADCOUNT == 0)
			{
				_isAniPlayEnd = true;
				_frameCount = 1;
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
			if (_isAniPlayEnd)  //동작이 끝나면
			{
				if(isPlayerFind(_x, 100)); //플레이어와의 거리 및 방향 탐색
			
				switch (_patternTrun)  //현재 패턴 순서로
				{
					case 0:
						if (_direction)
						{
							_status = ENEMY_RIGHT_MOVE;
						}
						else
						{
							_status = ENEMY_LEFT_MOVE;
						}

						if (isPlayerFind(_x, 70))
						{
							_patternTrun = 2;
						}
						else
						{
							if (isPlayerFind(_x, 100))
							{
								_patternTrun = 1;
							}
						}

					break;
					case 1:
						if (isPlayerFind(_x, 50))
						{
							if (_direction)
							{
								_status = ENEMY_RIGHT_ATTACK;
							}
							else
							{
								_status = ENEMY_LEFT_ATTACK;
							}
						}
						else
						{
							if (_direction)
							{
								_status = ENEMY_RIGHT_MOVE;
							}
							else
							{
								_status = ENEMY_LEFT_MOVE;
							}
						}

						_patternTrun = 0;

						if (_patternCount > 7)
						{
							_patternTrun = 3;
							_patternCount = 0;
						}
					break;
					case 2:
						if (isPlayerFind(_x, 50))
						{
							if (_direction)
							{
								_status = ENEMY_RIGHT_BACK_MOVE;
							}
							else
							{
								_status = ENEMY_LEFT_BACK_MOVE;
							}
						}

						if (_isHitDelayTime)
						{
							_patternTrun = 2;
						}
						else
						{
							_patternTrun = 3;
						}
			
						if (_patternCount > 7)
						{
							_patternTrun = 6;
							_patternCount = 0;
						}
					break;
					case 3:
						if (_direction)
						{
							_status = ENEMY_RIGHT_SMILE;
						}
						else
						{
							_status = ENEMY_LEFT_SMILE;
						}

						_patternTrun = 0;
					break;
					case 4:
						if (_isHitDelayTime || _jumpCount < 0)
						{
							_patternTrun = 5;

							_jumpCount = 4;
						}
						else
						{
							if (_direction)
							{
								_status = ENEMY_RIGHT_JUMP_ATTACK;
							}
							else
							{
								_status = ENEMY_LEFT_JUMP_ATTACK;
							}

							_jumpCount--;
						}
					break;
					case 5:
						if (_direction)  //플레이어가 오른쪽에 있고
						{
							if (_x < 30)  //화면 좌측 끝에 오면
							{
								_status = ENEMY_RIGHT_SMILE;

								_patternTrun = 0;
							}
							else if (_x <= WINSIZEX / 2)  //화면 좌측에 있다면
							{
								_status = ENEMY_LEFT_MOVE;
							}
						}
						else  //플레이어가 왼쪽에 있고
						{
							if (_x > WINSIZEX - 30)  //화면 우측 끝에 오면
							{
								_status = ENEMY_LEFT_SMILE;

								_patternTrun = 0;
							}
							else if (_x > WINSIZEX / 2)  //화면 우측에 있다면
							{
								_status = ENEMY_RIGHT_MOVE;
							}
						}

					break;
					case 6:
						if (_direction)
						{
							_status = ENEMY_RIGHT_FIRE_ATTACK;
						}
						else
						{
							_status = ENEMY_LEFT_FIRE_ATTACK;
						}

						_patternTrun = 0;
					break;
				}

				_isAniPlayEnd = false;
				_patternCount++;
			}
		break;
		case ENEMY_PATROL:

		break;
		case ENEMY_LEFT_FOWARD:

		break;
		case ENEMY_RIGHT_FOWARD:

		break;
	}
}