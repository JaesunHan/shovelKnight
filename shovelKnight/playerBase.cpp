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
	_direction = RIGHT;
	_moveSpeed = SPEED;
	_jumpPower = JUMPPOWER;
	_rc = RectMake(_x - HIT_BOX_WIDTH / 2, _y - HIT_BOX_HEIGHT, HIT_BOX_WIDTH, HIT_BOX_HEIGHT);

	return S_OK;
}
void playerBase::release()
{

}
void playerBase::update() 
{
	move();
	CAMERAMANAGER->setSingleFocus(_x, _y, 800);
}
void playerBase::render() 
{
	Rectangle(getMemDC(), CAMERAMANAGER->getX(_rc.left), CAMERAMANAGER->getY(_rc.top), CAMERAMANAGER->getX(_rc.right), CAMERAMANAGER->getY(_rc.bottom));
}

void playerBase::hitReAction(int num)
{
	/*switch (num)
	{
		case CP_OBJECT:
		break;
		case CP_ENEMY_SIDE:
		break;
		case CP_ENEMY_TOP:
		break;
	}*/
}

void playerBase::attack(float fireX, float fireY, bool skillUsed)
{

}
void playerBase::move()
{

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_state == HANG) _action = MOVE;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_state == HANG) _action = MOVE;
		if (_state == INAIR) _action = ATTACK;
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		if (_state == INAIR) _action = ATTACK;
		if (_state == HANG)_action = IDLE;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_direction = LEFT;
		_action = MOVE;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_action = IDLE;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_direction = RIGHT;
		_action = MOVE;
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_action = IDLE;
	}	

	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		_action = ATTACK;
	}
	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		_action = JUMP;
	}

	if (_action == MOVE)
	{
		_x += _moveSpeed*_direction;
	}
	if (_action == JUMP || _state == INAIR)
	{
		_y -= _jumpPower;
		_jumpPower -= _gravity;
	}
	if (_state == ONLAND)
	{
		_jumpPower = JUMPPOWER;
	}

	_rc = RectMake(_x - HIT_BOX_WIDTH / 2, _y - HIT_BOX_HEIGHT, HIT_BOX_WIDTH, HIT_BOX_HEIGHT);
}