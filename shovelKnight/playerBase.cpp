#include "stdafx.h"
#include "playerBase.h"


playerBase::playerBase()
{
}


playerBase::~playerBase()
{

}

HRESULT playerBase::init(float startX, float startY)
{

	//_image = IMAGEMANAGER->findImage(imageName);
	_x = startX;
	_y = startY;
	_isDead = false;
	_isDamaged = false;
	_currentHP = _maxHP = 8;
	_currentMP = _maxMP = 30;
	_skill = NULL;
	_skillUsed = false;
	_action = PR_IDLE;
	_state = INAIR;
	_direction = PD_RIGHT;
	_moveSpeed = SPEED;
	_gravity = GRAVITY;
	_jumpPower = JUMPPOWER;
	_jumpCount = 0;
	_rc = RectMake(_x - HIT_BOX_WIDTH / 2, _y - HIT_BOX_HEIGHT, HIT_BOX_WIDTH, HIT_BOX_HEIGHT);

	return S_OK;
}
void playerBase::release()
{

}
void playerBase::update() 
{
	move();
	hitReAction();
	CAMERAMANAGER->setSingleFocus(_x, _y, 800);
}
void playerBase::render() 
{
	HDC hdc = getMemDC();
	Rectangle(hdc,
		CAMERAMANAGER->getX(_rc.left),
		CAMERAMANAGER->getY(_rc.top),
		CAMERAMANAGER->getX(_rc.right),
		CAMERAMANAGER->getY(_rc.bottom));
	TTTextOut(300, 10, "top", _rc.top);
	TTTextOut(300, 25, "bottom", _rc.bottom);
	TTTextOut(300, 40, "left", _rc.left);
	TTTextOut(300, 55, "right", _rc.right);
	TTTextOut(300, 70, "state", _state);
	TTTextOut(400, 10, "action", _action);

}
//충돌에 따른 물리값 수정 
void playerBase::attack(float fireX, float fireY, bool skillUsed)
{

}

void playerBase::imageSetting()
{
	switch (_action)
	{
		case PR_IDLE:
			_image = IMAGEMANAGER->findImage("shovelIdle");
		break;
		case PR_MOVE:
			if (_state == ONLAND)_image = IMAGEMANAGER->findImage("shovelMove");
			if (_state == HANG) _image = IMAGEMANAGER->findImage("shovelClimb");
			if (_state == INAIR) _image = IMAGEMANAGER->findImage("shovelJump");
		break;
		case PR_ATTACK:
			_image = IMAGEMANAGER->findImage("shovelAttack");
		break;
		case PR_JUMP:
			_image = IMAGEMANAGER->findImage("shovelJump");
		break;
		case PR_ROOTING:
			_image = IMAGEMANAGER->findImage("shovelRooting");
		break;
		case PR_DAMAGED:
			_image = IMAGEMANAGER->findImage("shovelDamaged");
		break;
		case PR_DIE:
			_image = IMAGEMANAGER->findImage("shovelDead");
		break;
	}
}