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

	int rightBackMove[] = { 9, 8, 7, 6, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("skeletonRightBackMove", "skeleton", rightBackMove, 5, 6, true);

	int leftBackMove[] = { 14, 13, 12, 11, 10 };
	KEYANIMANAGER->addArrayFrameAnimation("skeletonLeftBackMove", "skeleton", leftBackMove, 5, 6, true);

	int rightAttack[] = { 15, 16 };
	KEYANIMANAGER->addArrayFrameAnimation("skeletonRightAttack", "skeleton", rightAttack, 2, 3, false);

	int leftAttack[] = { 17, 18 };
	KEYANIMANAGER->addArrayFrameAnimation("skeletonLeftAttack", "skeleton", leftAttack, 2, 3, false);

	int rightHit[] = { 20, 21 };
	KEYANIMANAGER->addArrayFrameAnimation("skeletonRightHit", "skeleton", rightHit, 2, 3, false);

	int leftHit[] = { 22, 23 };
	KEYANIMANAGER->addArrayFrameAnimation("skeletonLeftHit", "skeleton", leftHit, 2, 3, false);

	//=========================================================================================

	_width = 20;
	_height = 29;
	_isDead = false;
	_isDeadVanish = false;
	_vanishTime = 1;
	_direction = false;
	_gravity = 0.0f;
	_directionCount = 1;
	_angle = 0.0f;
	_enemyHp = 3;
	_isHit = false;
	_isCountStop = false;
	_playerFind = false;
	_isAttack = false;

	_rc = RectMakeCenter(_x, _y, _width, _height);
	_anim = KEYANIMANAGER->findAnimation("skeletonLeftIdle");

	_pixelC = new pixelCollision;
	_pixelC->init(_rc, _x, _y);

	_jump = new jump;
	_jump->init();

	return S_OK;
}

void skeleton::update()
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
	if (_status != ENEMY_LEFT_HIT && _status != ENEMY_RIGHT_HIT)
	{
		if (_playerFind) //플레이어를 발견하면
		{
			if (!_isCountStop) _directionCount++;

			if (_direction)
			{
				switch (_directionCount)
				{
				case 50:
					_status = ENEMY_RIGHT_MOVE;
					_isCountStop = true;
					_isAttack = false;
					break;
				case 100:
					_status = ENEMY_RIGHT_BACK_MOVE;
					_directionCount = 1;
					break;
				}

				//플레이어와의 거리가 가까울 경우 공격
				if (isPlayerFind(_x, 30) && !_isAttack)
				{
					_status = ENEMY_RIGHT_ATTACK;
					_isCountStop = false;
					_isAttack = true;
				}
			}
			else
			{
				switch (_directionCount)
				{
				case 50:
					_status = ENEMY_LEFT_MOVE;
					_isCountStop = true;
					_isAttack = false;
					break;
				case 100:
					_status = ENEMY_LEFT_BACK_MOVE;
					_directionCount = 1;
					break;
				}

				//플레이어와의 거리가 가까울 경우 공격
				if (isPlayerFind(_x, 30) && !_isAttack)
				{
					_status = ENEMY_LEFT_ATTACK;
					_isCountStop = false;
					_isAttack = true;
				}
			}
		}
	}


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
	if (_isHit)
	{
		_enemyHp--;
		_isHit = false;

		if (_direction)
		{
			_status = ENEMY_RIGHT_HIT;
		}
		else
		{
			_status = ENEMY_LEFT_HIT;
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

void skeleton::draw()
{
	CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left - 19, _rc.top - 9);
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


			_speed = SKELETONSPEED;
			_x -= _speed;
		break;
		case ENEMY_RIGHT_MOVE:
			_direction = true;

			_anim = KEYANIMANAGER->findAnimation("skeletonRightMove");
			if (!_anim->isPlay()) _anim->start();


			_speed = SKELETONSPEED;
			_x += _speed;
		break;
		case ENEMY_LEFT_BACK_MOVE:

			_anim = KEYANIMANAGER->findAnimation("skeletonLeftBackMove");
			if (!_anim->isPlay()) _anim->start();


			_speed = SKELETONSPEED;
			_x += _speed;
		break;
		case ENEMY_RIGHT_BACK_MOVE:

			_anim = KEYANIMANAGER->findAnimation("skeletonRightBackMove");
			if (!_anim->isPlay()) _anim->start();


			_speed = SKELETONSPEED;
			_x -= _speed;
		break;
		case ENEMY_LEFT_ATTACK:

			_anim = KEYANIMANAGER->findAnimation("skeletonLeftAttack");
			if (!_anim->isPlay()) _anim->start();

		break;
		case ENEMY_RIGHT_ATTACK:

			_anim = KEYANIMANAGER->findAnimation("skeletonRightAttack");
			if (!_anim->isPlay()) _anim->start();

		break;
		case ENEMY_RIGHT_HIT:

			_anim = KEYANIMANAGER->findAnimation("skeletonRightHit");
			if (!_anim->isPlay())
			{
				_anim->start();
				_jump->jumping(&_x, &_y, 2.0f, 0.7f);
			}

			//움직임: 뒤로 점핑하면서 죽기
			if (_jump->getIsJumping())
			{
				_speed = SKELETONSPEED * 3;
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

			_anim = KEYANIMANAGER->findAnimation("skeletonLeftHit");
			if (!_anim->isPlay())
			{
				_anim->start();
				_jump->jumping(&_x, &_y, 2.0f, 0.7f);
			}

			//움직임: 뒤로 점핑하면서 죽기
			if (_jump->getIsJumping())
			{
				_speed = SKELETONSPEED * 3;
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

			_anim = KEYANIMANAGER->findAnimation("skeletonLeftHit");

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
				_speed = SKELETONSPEED * 3;
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
				_speed = SKELETONSPEED * 3;
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
				_anim = KEYANIMANAGER->findAnimation("skeletonRightHit");
			}
			else
			{
				_anim = KEYANIMANAGER->findAnimation("skeletonLeftHit");
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

	//점프상태 초기화
	if (!_jump->getIsJumping()) _isJump = false;

	//렉트위치 update
	_rc = RectMakeCenter(_x, _y, _width, _height);
}
