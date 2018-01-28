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
		if (_action == PLAYERACTION_JUMP)
		{
			_currentFrameX = 0;
			_action = PLAYERACTION_DOWNATTACK;
		}
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_direction = PLAYERDIRECTION_LEFT;
		//if (_action != PLAYERACTION_MOVE) _currentFrameX = 0;
		if (_action != PLAYERACTION_ATTACK)
		{
			if (_state == PLAYERSTATE_ONLAND)_action = PLAYERACTION_MOVE;
			if (_moveSpeed < MAXSPEED)_moveSpeed += ACCELERATION;
			if (_moveSpeed > MAXSPEED)_moveSpeed = MAXSPEED;
		}
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_currentFrameX = 0;
		if (_action == PLAYERACTION_MOVE)_action = PLAYERACTION_IDLE;
		if (_moveSpeed > 0)_moveSpeed = 0;

	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_direction = PLAYERDIRECTION_RIGHT;
		if (_action != PLAYERACTION_ATTACK)
		{

			if (_state == PLAYERSTATE_ONLAND)
			{
				//if (_action != PLAYERACTION_MOVE) _currentFrameX = 0;
				if (_state == PLAYERSTATE_ONLAND)_action = PLAYERACTION_MOVE;
			}
			if (_moveSpeed < MAXSPEED)_moveSpeed += ACCELERATION;
			if (_moveSpeed > MAXSPEED)_moveSpeed = MAXSPEED;
		}
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_currentFrameX = 0;
		if(_action==PLAYERACTION_MOVE)_action = PLAYERACTION_IDLE;
		if (_moveSpeed > 0)_moveSpeed = 0;
	}

	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		
		if (_action != PLAYERACTION_ATTACK && _delay <= 0)
		{
			_action = PLAYERACTION_ATTACK;
			_currentFrameX = 0;
			_time = 0;
			if (_state == PLAYERSTATE_ONLAND)_moveSpeed = 0;
			_jumpPower -= 1;
		}
		
	}
	if (KEYMANAGER->isStayKeyDown('K'))
	{
		if (_action != PLAYERACTION_ATTACK && _action != PLAYERACTION_DOWNATTACK && _jumpCount == 0)
		{
			if (!_maxAti)
			{
				if (!_isJumping) _startY = _y;
				_isJumping = true;
				_jumpPower = JUMPPOWER;
			}
			_action = PLAYERACTION_JUMP;

			if (_startY - _y >= MAXATTITUDE)
			{
				_maxAti = true;

			}
		}
			/*if (_maxAti)_jumpPower = 0;*/
	}
	if (KEYMANAGER->isOnceKeyUp('K'))
	{
		_jumpCount = 1;
	}

	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		_currentFrameX = 0;
		_action = PLAYERACTION_DAMAGED;
	}

	_x += _moveSpeed * _direction;

	if (_action == PLAYERACTION_JUMP||_action == PLAYERACTION_DOWNATTACK)
	{
			_y -= _jumpPower;
			_jumpPower -= _gravity;	
	}
	if (_action == PLAYERACTION_ATTACK)
	{
		_y -= _jumpPower;
		_jumpPower -= _gravity;
		if (_currentFrameX == _image->getMaxFrameX())
		{
			_delay = DELAYTIME;
			if (_state == PLAYERSTATE_INAIR) _action = PLAYERACTION_JUMP;
			//if (_state == PLAYERSTATE_ONLAND) _action = PLAYERACTION_IDLE;
		}
	}
	

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
		if(_action!=PLAYERACTION_ATTACK&& _action != PLAYERACTION_DAMAGED
			&& _action != PLAYERACTION_DIE && _action!=PLAYERACTION_DOWNATTACK)_action = PLAYERACTION_JUMP;
	}
	break;
	}

	_rc = RectMake(_x - HIT_BOX_WIDTH / 2, _y - HIT_BOX_HEIGHT, HIT_BOX_WIDTH, HIT_BOX_HEIGHT);
}
