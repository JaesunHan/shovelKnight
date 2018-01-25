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
	_gravity = GRAVITY;
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
	HDC hdc = getMemDC();
	Rectangle(hdc,
		CAMERAMANAGER->getX(_rc.left),
		CAMERAMANAGER->getY(_rc.top),
		CAMERAMANAGER->getX(_rc.right),
		CAMERAMANAGER->getY(_rc.bottom));
	TTTextOut(hdc, 300, 10, "top", _rc.top);
	TTTextOut(hdc, 300, 25, "bottom", _rc.bottom);
	TTTextOut(hdc, 300, 40, "left", _rc.left);
	TTTextOut(hdc, 300, 55, "right", _rc.right);

}

void playerBase::hitReAction(int num)
{
	switch (_cp)
	{
	case CP_NULL:
		break;
	case CP_GROUND:
		break;
	case CP_OBJECT:
		break;
	case CP_OBJECT_SHOVEL_TOP:
		break;
	case CP_ENEMY_RIGHT:
		break;
	case CP_ENEMY_LEFT:
		break;
	case CP_SHOVEL_ENEMY_RIGHT:
		break;
	case CP_SHOVEL_ENEMY_LEFT:
		break;
	}
}

void playerBase::attack(float fireX, float fireY, bool skillUsed)
{

}
void playerBase::move()
{

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_state == HANG) _action = PR_MOVE;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_state == HANG) _action = PR_MOVE;
		if (_state == INAIR) _action = PR_ATTACK;
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		if (_state == INAIR) _action = PR_ATTACK;
		if (_state == HANG)_action = PR_IDLE;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_direction = LEFT;
		_action = PR_MOVE;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_action = PR_IDLE;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_direction = RIGHT;
		_action = PR_MOVE;
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_action = PR_IDLE;
	}	

	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		_action = PR_ATTACK;
	}
	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		_action = PR_JUMP;
		_jumpPower = JUMPPOWER;
	}

	if (_action == PR_MOVE)
	{
		_x += _moveSpeed*_direction;
	}
	if (_action == PR_JUMP || _state == INAIR)
	{
		_y -= _jumpPower;
		_jumpPower -= _gravity;
	}
	//if (_state == ONLAND)
	//{
	//	_jumpPower = JUMPPOWER;j
	//}

	_rc = RectMake(_x - HIT_BOX_WIDTH / 2, _y - HIT_BOX_HEIGHT, HIT_BOX_WIDTH, HIT_BOX_HEIGHT);
}