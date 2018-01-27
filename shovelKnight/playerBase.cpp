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
/*
	_image = IMAGEMANAGER->findImage("shovelIdle");
	_x = startX;
	_y = startY;
	_isDead = false;
	_isDamaged = false;
	_currentFrameX = _currentFrameY = 0;
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
	_rc = RectMake(_x - HIT_BOX_WIDTH / 2, _y - HIT_BOX_HEIGHT, HIT_BOX_WIDTH, HIT_BOX_HEIGHT);*/
	_image			= IMAGEMANAGER->findImage("shovelIdle");
	_direction		= PLAYERDIRECTION_RIGHT;
	_state			= PLAYERSTATE_INAIR;
	_action			= PLAYERACTION_IDLE;
	_time = 0;
	_x = startX;
	_y = startY;
	_rc				= RectMake(_x - HIT_BOX_WIDTH / 2, _y - HIT_BOX_HEIGHT, HIT_BOX_WIDTH, HIT_BOX_HEIGHT);
	_frameCount		= 0;
	_currentFrameX	= 0;
	_currentFrameY	= 0;
	_currentSkill	= 0;
	_skillUnlockLv = 0;
	_currentHP = _maxHP = 8;
	_currentMP = _maxMP = 30;
	_money = 0;
	_skill = 0;
	_alpha = 255;
	_jumpPower = JUMPPOWER;
	_gravity = GRAVITY;
	_moveSpeed = SPEED;
	_rtBlock = false;
	_ltBlock = false;
	_isDamaged = false;
	_skillUsed = false;
	_isDead = false;

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
	imageSetting();
	_frameCount++;
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
	CAMERAMANAGER->frameRenderObject(hdc, _image, _x-_image->getFrameWidth()/2, _y-_image->getFrameHeight(), _currentFrameX, _currentFrameY);

}
//충돌에 따른 물리값 수정 
void playerBase::attack(float fireX, float fireY, bool skillUsed)
{

}

void playerBase::imageSetting()
{
	switch (_action)
	{
		case PLAYERACTION_IDLE:
			_image = IMAGEMANAGER->findImage("shovelIdle");
		break;
		case PLAYERACTION_MOVE:
			if (_state == PLAYERSTATE_ONLAND)_image = IMAGEMANAGER->findImage("shovelMove");
			if (_state == PLAYERSTATE_HANG) _image = IMAGEMANAGER->findImage("shovelClimb");
			if (_state == PLAYERSTATE_INAIR) _image = IMAGEMANAGER->findImage("shovelJump");
		break;
		case PLAYERACTION_ATTACK:
			_image = IMAGEMANAGER->findImage("shovelAttack");
		break;
		case PLAYERACTION_JUMP:
			_image = IMAGEMANAGER->findImage("shovelJump");
		break;
		case PLAYERACTION_ROOTING:
			_image = IMAGEMANAGER->findImage("shovelRooting");
		break;
		case PLAYERACTION_DAMAGED:
			_image = IMAGEMANAGER->findImage("shovelDamaged");
		break;
		case PLAYERACTION_DIE:
			_image = IMAGEMANAGER->findImage("shovelDead");
		break;
	}
	if (_direction == PLAYERDIRECTION_RIGHT) _currentFrameY = 0;
	else _currentFrameY = 1;

	_time += TIMEMANAGER->getElapsedTime();
	while (_time > TIMECOUNT)
	{
		_frameCount++;
		_time -= TIMECOUNT;
		if (_frameCount >= _image->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
	}
	if (_frameCount == 1)
	{
		_currentFrameX++;
	}
	
}