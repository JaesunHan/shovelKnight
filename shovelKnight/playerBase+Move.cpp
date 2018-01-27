#include "stdafx.h"
#include "playerBase.h"

void playerBase::move()
{

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_state == PLAYERSTATE_HANG) _action = PLAYERACTION_MOVE;
		_directionTB = PLAYERDIRECTION_TOP;
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		if (_state == PLAYERSTATE_HANG)_action = PLAYERACTION_IDLE;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_state == PLAYERSTATE_HANG) _action = PLAYERACTION_MOVE;
		_directionTB = PLAYERDIRECTION_BOTTOM;
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		if (_state == PLAYERSTATE_HANG)_action = PLAYERACTION_IDLE;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_direction = PLAYERDIRECTION_LEFT;
		_action = PLAYERACTION_MOVE;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_action = PLAYERACTION_IDLE;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_direction = PLAYERDIRECTION_RIGHT;
		_action = PLAYERACTION_MOVE;
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_action = PLAYERACTION_IDLE;
	}

	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		_action = PLAYERACTION_ATTACK;
	}
	if (KEYMANAGER->isStayKeyDown('J'))
	{
		_action = PLAYERACTION_JUMP;
		_jumpPower = JUMPPOWER;
	}



	switch (_state)
	{
	case PLAYERSTATE_ONLAND:
	{
		if (_action == PLAYERACTION_MOVE)_x += _moveSpeed * _direction;
	}
		break;
	case PLAYERSTATE_INAIR:
	{
		_y -= _jumpPower;
		_jumpPower -= _gravity;
		if (_action == PLAYERACTION_MOVE)_x += _moveSpeed * _direction;
		if (_jumpPower < 0) _currentFrameX = 1;
		else _currentFrameX = 0;
	}
	break;
	case PLAYERSTATE_HANG:
		if (_action == PLAYERACTION_MOVE)_y += _moveSpeed * _directionTB;
		break;
	}

	_rc = RectMake(_x - HIT_BOX_WIDTH / 2, _y - HIT_BOX_HEIGHT, HIT_BOX_WIDTH, HIT_BOX_HEIGHT);
}
