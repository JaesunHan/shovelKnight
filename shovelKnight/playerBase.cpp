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
	collisionPlayerMap();
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
	TTTextOut(hdc, 300, 10, "top", _rc.top);
	TTTextOut(hdc, 300, 25, "bottom", _rc.bottom);
	TTTextOut(hdc, 300, 40, "left", _rc.left);
	TTTextOut(hdc, 300, 55, "right", _rc.right);



}

void playerBase::hitReAction()
{
	switch (collisionPlayerMap())
	{
	case CT_NULL:
		_cPlayerTarget = CP_NULL;
		break;
	case CT_TOP:
		_cPlayerTarget = CP_GROUND;
		_cLR = LR_NULL;
		_cTB = TB_TOP;
		break;
	case CT_BOTTOM:
		_cPlayerTarget = CP_GROUND;
		_cLR = LR_NULL;
		_cTB = TB_BOTTOM;
		break;
	case CT_LEFT:
		_cPlayerTarget = CP_GROUND;
		_cLR = LR_LEFT;
		_cTB = TB_NULL;
		break;
	case CT_RIGHT:
		_cPlayerTarget = CP_GROUND;
		_cLR = LR_RIGHT;
		_cTB = TB_NULL;
		break;
	case CT_LEFT_BOTTOM:
		_cPlayerTarget = CP_GROUND;
		_cLR = LR_LEFT;
		_cTB = TB_BOTTOM;
		break;
	case CT_RIGHT_BOTTOM:
		_cPlayerTarget = CP_GROUND;
		_cLR = LR_RIGHT;
		_cTB = TB_BOTTOM;
		break;
	}

	switch (_cPlayerTarget)
	{
		case CP_NULL:
		break;
		case CP_OBJECT:
		{
			switch (_cLR)
			{
				case LR_NULL:
				_rtBlock = false;
				_ltBlock = false;
				break;
				case LR_LEFT:
				_rtBlock = true;
				break;
				case LR_RIGHT:
				_ltBlock = true;
				break;
			}
			switch (_cTB)
			{
				case TB_NULL:
				break;
				case TB_TOP:
				_jumpPower = JUMPPOWER;
				break;
				case TB_BOTTOM:
				_jumpPower = 0;
				break;
			}
		}
		break;
		case CP_ENEMY:
		
		break;
		case CP_GROUND:
		{
			switch (_cLR)
			{
				case LR_NULL:
				_rtBlock = false;
				_ltBlock = false;
				break;
				case LR_LEFT:
				_rtBlock = true;
				break;
				case LR_RIGHT:
				_ltBlock = true;
				break;
			}
			switch (_cTB)
			{
				case TB_NULL:
				break;
				case TB_TOP:
				_jumpPower = JUMPPOWER;
				break;
				case TB_BOTTOM:
				_jumpPower = 0;
				break;
			}
		}
		case CP_SHOVEL_OBJ:
		{
			switch (_cTB)
			{
			case TB_NULL:
				break;
			case TB_TOP:
				_jumpPower = JUMPPOWER/2;
				break;
			case TB_BOTTOM:
				break;
			}
		}
			break;
		case CP_SHOVEL_ENEMY:
		{
			switch (_cTB)
			{
			case TB_NULL:
				break;
			case TB_TOP:
				_jumpPower = JUMPPOWER / 2;
				break;
			case TB_BOTTOM:
				break;
			}
			switch (_cLR)
			{
			case LR_NULL:
				break;
			case LR_LEFT:
				break;
			case LR_RIGHT:
				break;
			}
		}
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
		_direction = PD_LEFT;
		_action = PR_MOVE;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_action = PR_IDLE;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_direction = PD_RIGHT;
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
	if (KEYMANAGER->isStayKeyDown('J'))
	{
		_action = PR_JUMP;
		_jumpPower = JUMPPOWER;
	}

	//좌우 이동부분
	if (_action == PR_MOVE)
	{
		_x += _moveSpeed*_direction;
	}
	//상하 이동부분
	if (_action == PR_JUMP || _state == INAIR)
	{
		_y -= _jumpPower;
		_jumpPower -= _gravity;
		
		if (_jumpPower < 0) _currentFrameX = 1;
		else _currentFrameX = 0;
	}
	


	_rc = RectMake(_x - HIT_BOX_WIDTH / 2, _y - HIT_BOX_HEIGHT, HIT_BOX_WIDTH, HIT_BOX_HEIGHT);
}


int playerBase::collisionPlayerMap()
{
	HDC hdc = IMAGEMANAGER->findImage("bgMap")->getMemDC();

	RECT rc = _rc;

	int probeX, probeY, probeY2;
	bool ltBlock, rtBlock;

	ltBlock = false;
	rtBlock = false;

	probeY = rc.bottom;
	probeY2 = rc.bottom;
	

	for (probeX = rc.left; probeX != rc.right; ++probeX)
	{
		if (probeX == rc.left)
		{
			while (ThisPixelIsMazen(hdc, probeX, probeY2))
			{
				--probeY2;
			}
			while (!ThisPixelIsMazen(hdc, probeX, probeY))
			{
				--probeY;
			}

			if (probeY == probeY2 + 1) ltBlock = false;
			else ltBlock = true;
		}
		if (probeX != rc.left&&probeX != rc.right)
		{
			while (!ThisPixelIsMazen(hdc, probeX, probeY))
			{
				--probeY;
			}
		}
		if (probeX == rc.right)
		{
			while (ThisPixelIsMazen(hdc, probeX, probeY2))
			{
				--probeY2;
			}
			while (!ThisPixelIsMazen(hdc, probeX, probeY))
			{
				--probeY;
			}
			if (probeY == probeY2 + 1) rtBlock = false;
			else rtBlock = true;
		}
	}
	
	if (probeY == rc.bottom&& !ltBlock&& !rtBlock) return CT_BOTTOM;
	else if (probeY == rc.bottom && ltBlock && !rtBlock) return CT_LEFT_BOTTOM;
	else if (probeY == rc.bottom && !ltBlock && rtBlock) return CT_RIGHT_BOTTOM;
	else if (probeY < rc.top && !ltBlock && !rtBlock) return CT_NULL;
	else if (probeY < rc.top && ltBlock && !rtBlock) return CT_LEFT;
	else if (probeY < rc.top && !ltBlock && rtBlock) return CT_RIGHT;
	else return CT_TOP;
}
