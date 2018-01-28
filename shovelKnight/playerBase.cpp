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
	_jumpPower = 0;
	_gravity = GRAVITY;
	_moveSpeed = 0;
	_rtBlock = false;
	_ltBlock = false;
	_isDamaged = false;
	_skillUsed = false;
	_isDead = false;
	_isJumping = true;
	_maxAti = false;
	_delay = 0;
	_jumpCount = 0;
	return S_OK;
}
void playerBase::release()
{

}
void playerBase::update() 
{
	move();
	hitReAction();
	collision();
	CAMERAMANAGER->setSingleFocus(_x, _y, 800);
	imageSetting();
	if (_direction == PLAYERDIRECTION_RIGHT) _currentFrameY = 0;
	else _currentFrameY = 1;

	_time += TIMEMANAGER->getElapsedTime();
	
	if (_delay > 0)
	{
		_delay -= TIMEMANAGER->getElapsedTime();
	}
	while (_time > TIMECOUNT)
	{
		_time -= TIMECOUNT;
		if (_action == PLAYERACTION_DIE || _action == PLAYERACTION_MOVE || _action == PLAYERACTION_ATTACK||
			_action == PLAYERACTION_IDLE||_action == PLAYERACTION_DAMAGED)
		{

			if (_image->getMaxFrameX()>1) _currentFrameX++;
			if (_currentFrameX > _image->getMaxFrameX())
			{
				_currentFrameX = 0;
				if (_action == PLAYERACTION_ATTACK) _action = PLAYERACTION_IDLE;
			}
		}
		
	}
	if (_action == PLAYERACTION_JUMP && _jumpPower <= 0) _currentFrameX = 1;
	if (_action == PLAYERACTION_JUMP && _jumpPower > 0) _currentFrameX = 0;
	if (_action == PLAYERACTION_IDLE && _state == PLAYERSTATE_INAIR) _action == PLAYERACTION_JUMP;
}
void playerBase::render() 
{
	HDC hdc = getMemDC();
	TTTextOut(300, 10, "top", _rc.top);
	TTTextOut(300, 25, "bottom", _rc.bottom);
	TTTextOut(300, 40, "left", _rc.left);
	TTTextOut(300, 55, "right", _rc.right);
	TTTextOut(300, 70, "state", _state);
	TTTextOut(400, 10, "action", _action);
	//TTTextOut(400, 25, "speed", _moveSpeed);
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
			_image = IMAGEMANAGER->findImage("shovelMove");
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
		case PLAYERACTION_DOWNATTACK :
			_image = IMAGEMANAGER->findImage("shovelDownAttack");
	}


}

void playerBase::collision()
{
	probeY = _y;
	HDC hdc = IMAGEMANAGER->findImage("bgMap")->getMemDC();
	
	COLORREF color = GetPixel(hdc, _x, probeY);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

	//땅과 충돌했을떄
	if ((r == 0 && g == 255 && b == 0))
	{
		while (!(r == 0 && g == 255 && b == 0))
		{
			probeY++;
		}
		if (_action == PLAYERACTION_JUMP||_action ==PLAYERACTION_DOWNATTACK)
		{
			_action = PLAYERACTION_IDLE;
			_currentFrameX = 0;
		}
		_jumpPower = 0;
		_isJumping = false;
		_maxAti = false;
		_jumpCount = 0;
		_y = probeY+1;
		_state = PLAYERSTATE_ONLAND;
		
	}

	//공중에 있을때
	if ((r == 255 && g == 0 && b == 255))
	{
		_state = PLAYERSTATE_INAIR;
	}

}


