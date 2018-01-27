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
		if (_action != PLAYERACTION_MOVE || _direction != PLAYERDIRECTION_LEFT) _currentFrameX = 0;
		_direction = PLAYERDIRECTION_LEFT;
		if (_state = PLAYERSTATE_ONLAND)_action = PLAYERACTION_MOVE;
		if(_speed<MAXSPEED)_speed += ACCELERATION;
		if (_speed > MAXSPEED)_speed = MAXSPEED;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		if (_action == PLAYERACTION_MOVE)_action = PLAYERACTION_IDLE;
		if (_speed > 0)_speed -= ACCELERATION;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (_state == PLAYERSTATE_ONLAND)
		{
			if (_action != PLAYERACTION_MOVE || _direction != PLAYERDIRECTION_RIGHT) _currentFrameX = 0;
			if (_state = PLAYERSTATE_ONLAND)_action = PLAYERACTION_MOVE;
		}
		_direction = PLAYERDIRECTION_RIGHT;
		if (_speed<MAXSPEED)_speed += ACCELERATION;
		if (_speed > MAXSPEED)_speed = MAXSPEED;
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		if(_action==PLAYERACTION_MOVE)_action = PLAYERACTION_IDLE;
		if (_speed > 0)_speed -= ACCELERATION;
	}

	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		_action = PLAYERACTION_ATTACK;
	}
	if (KEYMANAGER->isStayKeyDown('K'))
	{
		_isJump = true;
		_action = PLAYERACTION_JUMP;
		_jumpPower = JUMPPOWER;
	}
	if (_action == PLAYERACTION_JUMP&&_isJump)
	{
		_y -= _jumpPower;
		_jumpPower -= _gravity;
	}

	_x += _moveSpeed * _direction;

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
		if (_action == PLAYERACTION_JUMP && _jumpPower < 0) _currentFrameX = 1;
		if (_action == PLAYERACTION_JUMP && _jumpPower > 0) _currentFrameX = 0;
	}
	break;
	}

	_rc = RectMake(_x - HIT_BOX_WIDTH / 2, _y - HIT_BOX_HEIGHT, HIT_BOX_WIDTH, HIT_BOX_HEIGHT);
}
