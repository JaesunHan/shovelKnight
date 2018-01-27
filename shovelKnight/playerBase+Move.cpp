#include "stdafx.h"
#include "playerBase.h"

void playerBase::move()
{

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_state == PLAYERSTATE_HANG) _y -= 1;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_state == PLAYERSTATE_HANG) _y += 1;
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_direction = PLAYERDIRECTION_LEFT;
		if (_action != PLAYERACTION_MOVE) _currentFrameX = 0;
		if (_state == PLAYERSTATE_ONLAND)_action = PLAYERACTION_MOVE;
		if(_moveSpeed<MAXSPEED)_moveSpeed += ACCELERATION;
		if (_moveSpeed > MAXSPEED)_moveSpeed = MAXSPEED;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		if (_action == PLAYERACTION_MOVE)_action = PLAYERACTION_IDLE;
		if (_moveSpeed > 0)_moveSpeed = 0;

	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_direction = PLAYERDIRECTION_RIGHT;
		if (_state == PLAYERSTATE_ONLAND)
		{
			if (_action != PLAYERACTION_MOVE) _currentFrameX = 0;
			if (_state == PLAYERSTATE_ONLAND)_action = PLAYERACTION_MOVE;
		}
		if (_moveSpeed < MAXSPEED)_moveSpeed += ACCELERATION;
		if (_moveSpeed > MAXSPEED)_moveSpeed = MAXSPEED;
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		if(_action==PLAYERACTION_MOVE)_action = PLAYERACTION_IDLE;
		if (_moveSpeed > 0)_moveSpeed = 0;
	}

	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		_action = PLAYERACTION_ATTACK;
	}
	if (KEYMANAGER->isStayKeyDown('K'))
	{
		if (!_maxAti)
		{
			if (!_isJumping) _startY = _y;
			_isJumping = true;

			_action = PLAYERACTION_JUMP;
			if (_y - _startY >= MAXATTITUDE)  _maxAti = true;
			_jumpPower = JUMPPOWER;
		}
		/*if (_maxAti)_jumpPower = 0;*/
	}
	if (_action == PLAYERACTION_JUMP)
	{
		_y -= _jumpPower;
		_jumpPower -= _gravity;
	}

	_x += _moveSpeed * _direction;

	if (_action != PLAYERACTION_MOVE)
	{
		//if (_moveSpeed > 0)_moveSpeed -= friction;
		if (_moveSpeed <= 0)_moveSpeed = 0;
	}
	switch (_state)
	{
	case PLAYERSTATE_ONLAND:
	{
	}
		break;
	case PLAYERSTATE_INAIR:
	{
		if(_action!=PLAYERACTION_ATTACK|| _action != PLAYERACTION_DAMAGED
			|| _action != PLAYERACTION_DIE||_action!=PLAYERACTION_DOWNATTACK)_action = PLAYERACTION_JUMP;
	}
	break;
	}

	_rc = RectMake(_x - HIT_BOX_WIDTH / 2, _y - HIT_BOX_HEIGHT, HIT_BOX_WIDTH, HIT_BOX_HEIGHT);
}
