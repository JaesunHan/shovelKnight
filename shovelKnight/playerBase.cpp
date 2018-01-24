#include "stdafx.h"
#include "playerBase.h"


playerBase::playerBase()
{
}


playerBase::~playerBase()
{

}

HRESULT playerBase::init(float startX, float startY, string imageName)
{
	_image = IMAGEMANAGER->findImage(imageName);
	_x = startX;
	_y = startY;
	_isDead = false;
	_isDamaged = false;
	_currentHP = _maxHP = 8;
	_currentMP = _maxMP = 30;
	_skill = NULL;
	_skillUsed = false;
	_direction = RIGHT;
	_rc = RectMake(_x - HIT_BOX_WIDTH / 2, _y - HIT_BOX_HEIGHT, HIT_BOX_WIDTH, HIT_BOX_HEIGHT);



	return S_OK;
}
void playerBase::release()
{

}
void playerBase::update() 
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_direction == PLAYER_LEFT_HANG || _direction == PLAYER_RIGHT_HANG) _y -= 3;


	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_direction == PLAYER_RIGHT_STOP) _direction = PLAYER_RIGHT_SIT;
		if (_direction == PLAYER_LEFT_STOP) _direction = PLAYER_LEFT_SIT;
		if (_direction == PLAYER_LEFT_HANG || _direction == PLAYER_RIGHT_HANG) _y += 3;
		if (_direction == PLAYER_LEFT_JUMP)
		{
			_direction = PLAYER_LEFT_JUMP_DOWNATTACK;
			_fireX = _x;
			_fireY = _y + HIT_BOX_HEIGHT / 2;
			attack(_fireX, _fireY, false);
		}
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{

	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{

	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{

	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{

	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{

	}
}
void playerBase::render() 
{

}

void playerBase::hitReAction(int num)
{
	switch (num)
	{
		case HIT_OBJ_AIR:
		break;
		case HIT_ENEMY_GROUND:
		break;
		case HIT_ENEMY_AIR:
		break;
	}
}

void playerBase::attack(float fireX, float fireY, bool skillUsed)
{
	if (skillUsed == false)
	{
		RECT damageRC;
		if (_direction == PLAYER_LEFT_ATTACK || _direction == PLAYER_RIGHT_ATTACK
			|| _direction == PLAYER_LEFT_HANG_ATTACK|| _direction == PLAYER_RIGHT_HANG_ATTACK)
		{
			if (_image->getMaxFrameX() == _currentFrameX)
			{
				switch (_direction)
				{
					case PLAYER_LEFT_ATTACK: 
						_direction = PLAYER_LEFT_STOP;
						_currentFrameX = 0;
					break;
					case PLAYER_RIGHT_ATTACK:
						_direction = PLAYER_RIGHT_STOP;
						_currentFrameX = 0;
					break;
					case PLAYER_LEFT_HANG_ATTACK:
						_direction = PLAYER_LEFT_HANG;
						_currentFrameX = 0;
					break;
					case PLAYER_RIGHT_HANG_ATTACK:
						_direction = PLAYER_RIGHT_HANG;
						_currentFrameX = 0;
					break;
				}
			}
			damageRC = RectMakeCenter(fireX, fireY, ATTACK_DAMAGE_BOX_WIDTH, ATTACK_DAMAGE_BOX_HEIGHT);
		}
		else if (_direction == PLAYER_LEFT_JUMP_DOWNATTACK || _direction == PLAYER_RIGHT_JUMP_DOWNATTACK)
		{
			damageRC = RectMakeCenter(fireX, fireY, DOWNATTACK_DAMAGE_BOX_WIDTH, DOWNATTACK_DAMAGE_BOX_HEIGHT);
		}
	}
	else
	{ }
}