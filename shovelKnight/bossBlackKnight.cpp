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
	_enemyType = ENEMY_SKELETON;

	_speed = 0.0f;

	_img = IMAGEMANAGER->addFrameImage("darkKnight", ".//image//monster//darkKnight.bmp", _x, _y, 608, 516, 8, 12, true, RGB(255, 0, 255));

	_status = ENEMY_LEFT_IDLE;

	//========================================================================================= 에니메이션

	int rightIdle[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightRightIdle", "darkKnight", rightIdle, 2, 3, true);

	int leftIdle[] = { 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightLeftIdle", "darkKnight", leftIdle, 2, 3, true);

	int rightMove[] = { 5, 6, 7, 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightRightMove", "darkKnight", rightMove, 5, 6, true);

	int leftMove[] = { 10, 11, 12, 13, 14 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightLeftMove", "darkKnight", leftMove, 5, 6, true);

	int rightBackMove[] = { 9, 8, 7, 6, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightRightBackMove", "darkKnight", rightBackMove, 5, 6, true);

	int leftBackMove[] = { 14, 13, 12, 11, 10 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightLeftBackMove", "darkKnight", leftBackMove, 5, 6, true);

	int rightAttack[] = { 15, 16 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightRightAttack", "darkKnight", rightAttack, 2, 3, false);

	int leftAttack[] = { 17, 18 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightLeftAttack", "darkKnight", leftAttack, 2, 3, false);

	int rightHit[] = { 20, 21 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightRightHit", "darkKnight", rightHit, 2, 3, false);

	int leftHit[] = { 22, 23 };
	KEYANIMANAGER->addArrayFrameAnimation("darkKnightLeftHit", "darkKnight", leftHit, 2, 3, false);

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

}

void bossBlackKnight::move()					 
{

}

void bossBlackKnight::draw()					 
{

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