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
	_enemyType = ENEMY_DRAGON;

	_x = x;
	_y = y;
	_speed = 0.0f;

	_img = IMAGEMANAGER->addFrameImage("dragon", ".//image//monster//bubbleDragon.bmp", _x, _y, 1074, 356, 6, 4, true, RGB(255, 0, 255));

	//이미지 렉트
	_ImageRc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	//충돌용 렉트	
	_rc = RectMakeCenter(_x - DRAGONHEADRECTX, _y + DRAGONHEADRECTY, 40, 25);          //머리
	_trunkRc = RectMakeCenter(_x + DRAGONTRUNKRECTX, _y + DRAGONTRUNKRECTY, 85, 60);   //몸통


	_status = ENEMY_LEFT_IDLE;

	//========================================================================================= 에니메이션

	int leftStop[] = { 0, 1, 2, 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("dragonLeftStop", "dragon", leftStop, 6, 6, true);

	int leftForwardMove[] = { 6, 7, 8, 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("dragonLeftForwardMove", "dragon", leftForwardMove, 6, 6, false);

	int leftBackMove[] = { 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("dragonLeftBackMove", "dragon", leftBackMove, 6, 6, false);

	int leftHit[] = { 18, 19, 20 };
	KEYANIMANAGER->addArrayFrameAnimation("dragonLeftHit", "dragon", leftHit, 3, 20, false);

	int leftAttack[] = { 21, 22, 23 };
	KEYANIMANAGER->addArrayFrameAnimation("dragonLeftAttack", "dragon", leftAttack, 3, 10, false);

	//=========================================================================================

	_width = _img->getFrameWidth();
	_height = _img->getFrameHeight();
	_isDead = false;
	_isDeadVanish = false;
	_vanishTime = 1;
	_directionCount = 1;
	_direction = false;
	_movePatternCount = 1;
	_playerFind = false;
	_enemyHp = 7;
	_isHit = false;
	_previousStatus = _status;

	_anim = KEYANIMANAGER->findAnimation("dragonLeftStop");


	return S_OK;
}

void boss1::update()
{
	if (_status != ENEMY_LEFT_HIT && _status != ENEMY_RIGHT_HIT)
	{
		_previousStatus = _status; //직전 에너미 상태 저장
	}

	//상태값에 따른 에니메이션 및 움직임
	move();

	//플레이어가 일정거리 안으로 들어오면
	if (isPlayerFind(_x, 200)) _playerFind = true;
	_direction = false;  //예외처리: 방향 무조건 왼쪽으로

	//공격 움직임 패턴
	if (_playerFind) //플레이어를 발견하면
	{
		_directionCount++;

		switch (_directionCount)
		{
			case 100:
				_status = ENEMY_LEFT_MOVE;
			break;
			case 200:
				_status = ENEMY_LEFT_ATTACK;
			break;
			case 250:
				_status = ENEMY_LEFT_BACK_MOVE;
			break;
			case 350:
				_status = ENEMY_LEFT_ATTACK;
				_directionCount = 1;
			break;
		}

	}


	//데미지 설정
	if (_isHit)
	{
		_status = ENEMY_LEFT_HIT;
		_enemyHp--;
		_isHit = false;
	}

	//hp=0일경우 상태 변경
	if (_enemyHp <= 0)
	{
		_status = ENEMY_LEFT_DEAD;	
	}


}

void boss1::render()
{

	draw();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		//머리 렉트
		Rectangle(getMemDC(), CAMERAMANAGER->getX(_rc.left), CAMERAMANAGER->getY(_rc.top),
			CAMERAMANAGER->getX(_rc.right), CAMERAMANAGER->getY(_rc.bottom));
		//몸통 렉트
		Rectangle(getMemDC(), CAMERAMANAGER->getX(_trunkRc.left), CAMERAMANAGER->getY(_trunkRc.top),
			CAMERAMANAGER->getX(_trunkRc.right), CAMERAMANAGER->getY(_trunkRc.bottom));

	}
	
}

void boss1::draw()
{
	CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _ImageRc.left, _ImageRc.top);
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
		case ENEMY_LEFT_ATTACK:

			_anim = KEYANIMANAGER->findAnimation("dragonLeftAttack");
			if (!_anim->isPlay()) _anim->start();


		break;
		case ENEMY_LEFT_HIT:

			_anim = KEYANIMANAGER->findAnimation("dragonLeftHit");
			if (!_anim->isPlay())
			{
				_anim->start();
				_x += _speed;
			}
			else
			{
				_jumpCount++;  //에니메이션 플레이 여유타임
				if (_jumpCount % 10 == 0)
				{
					_status = _previousStatus;
					_jumpCount = 1;
				}
			}


		break;
		case ENEMY_LEFT_DEAD:

			_anim = KEYANIMANAGER->findAnimation("dragonLeftHit");

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
				if (_vanishTime % 50 == 0)
				{
					_isDeadVanish = true;
					_vanishTime = 1;
				}
			}

		break;
	}


	//렉트위치 update
	_ImageRc = RectMakeCenter(_x, _y, _width, _height);
	_rc = RectMakeCenter(_x - DRAGONHEADRECTX, _y + DRAGONHEADRECTY, 40, 25);
	_trunkRc = RectMakeCenter(_x + DRAGONTRUNKRECTX, _y + DRAGONTRUNKRECTY, 85, 60);
}
