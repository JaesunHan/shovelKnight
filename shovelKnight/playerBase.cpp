#include "stdafx.h"
#include "playerBase.h"
#include "stageManager.h"
#include "gameCollision.h"
#include "skillManager.h"
#include "gamePlayUI.h"
#include "frontObjectManager.h"

playerBase::playerBase()
{
}


playerBase::~playerBase()
{

}

HRESULT playerBase::init()
{
	return S_OK;
}
void playerBase::release()
{

}
void playerBase::update() 
{
	
}
void playerBase::render() 
{

}			

void playerBase::control()
{
	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		if (_isAttacking == false)
		{
			_isAttacking = true;
			_action = ATTACK;
			_counter = 0;
			_frameX = 0;
		}
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (_action != ATTACK) _direction = LEFT;
		_rtBlock = false;
		_ltMoving = true;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_ltMoving = false;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (_action != ATTACK) _direction = RIGHT;
		_ltBlock = false;
		_rtMoving = true;
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_rtMoving = false;
	}
	if (_ltMoving == false && _rtMoving == false && _state == ONLAND && _action != ATTACK)
	{
		_action = IDLE;
	}
	if (_state == ONLAND && 
		_action != MOVE && 
		_action != ATTACK &&
		(_ltMoving == true || _rtMoving == true))	//ÀÌµ¿ ÇÁ·¹ÀÓ ÃÊ±âÈ­
	{
		_frameX = 0;
		_counter = 0;
		_action = MOVE;
	}
	if (_ltBlock == false && _state != HANG)
	{
		if (_ltMoving == true)
		{
			if (!(_state == ONLAND && _action == ATTACK) && _playerRC.left > 0)
			{
				_x -= SPEED;
				_SM->setLayer2LoopX(-0.3f);
			}
		}
	}
	if (_rtBlock == false && _state != HANG)
	{
		if (_rtMoving == true)
		{
			if (!(_state == ONLAND && _action == ATTACK) && _playerRC.right < IMAGEMANAGER->findImage("bgMap")->getWidth())
			{
				_x += SPEED;
				_SM->setLayer2LoopX(0.3f);
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_GC->PlayerMeetNPC();
		hangPixelDetect();
		if (_state == HANG)
		{
			if (hangPixelDetectUp() == false) _y -= SPEED;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		_jumpKeyDown = true;
		if (_state == ONLAND)
		{
			_state = INAIR;
			_action = JUMP;
			_isAttacking = false;
			_jumpPower = JUMPPOWER;
		}
		if (_state == HANG)
		{
			_state = INAIR;
			_action = JUMP;
			_jumpPower = 0;
		}
	}
	if (_jumpKeyDown == true)
	{
		_jumpCounter++;
		if (_jumpCounter < 10)
		{
			_jumpPower += 0.3f;
		}
	}
	if (KEYMANAGER->isOnceKeyUp('K'))
	{
		if (_state == INAIR) _jumpCounter = 30;
		if (_state == ONLAND) _jumpCounter = 0;
	}
	
	if (KEYMANAGER->isOnceKeyDown('U'))
	{
		while (true)
		{
			_currentSkill--;
			if (_currentSkill < 0) _currentSkill == 3;
			if (_currentSkill == 1 && _fireBall == true) break;
			if (_currentSkill == 0) break;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		while (true)
		{
			_currentSkill++;
			if (_currentSkill > 3) _currentSkill == 0;
			if (_currentSkill == 1 && _fireBall == true) break;
			if (_currentSkill == 0) break;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		//switch (_currentSkill)
		//{
		//case(1):
		//	
		//	break;
		//}
	}

	if (_action == IDLE)
	{
		_shineCounter++;
		if (_shineCounter > 200) _shine = true;
		if (_shineCounter > 205)
		{
			_shineFrameX = 1;
		}
		if (_shineCounter > 210)
		{
			_shineFrameX = 2;
		}
		if (_shineCounter > 215)
		{
			_shine = false;
			_shineFrameX = 0;
			_shineCounter = 0;
		}
	}
	else
	{
		_shine = false;
		_shineFrameX = 0;
		_shineCounter = 0;
	}

	_playerRC = RectMake(_x - HIT_BOX_WIDTH / 2, _y - HIT_BOX_HEIGHT, HIT_BOX_WIDTH, HIT_BOX_HEIGHT);
}


void playerBase::pixelCollision()
{
	COLORREF color, color2, color3;
	int R, G, B, R2, G2, B2, R3, G3, B3;
	if (_state != HANG)
	{
		if (_jumpPower <= 0)	//ÇÏ°­ ÁßÀÏ ¶§ ¶¥¿¡ ´êÀ¸¸é ¸ØÃç¶ó
		{
			for (int i = 0; i < 10; ++i)
			{
				color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.right, _playerRC.bottom + i);
				R = GetRValue(color);
				G = GetGValue(color);
				B = GetBValue(color);
				if ((R == 0 && G == 255 && B == 0) || (R == 0 && G == 0 && B == 255))
				{
					_y = _playerRC.bottom + i;
					_jumpPower = 0;
					_jumpCounter = 0;
					_jumpKeyDown = false;
					_downwardThrust = false;
					_state = ONLAND;
					break;
				}
				color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.left, _playerRC.bottom + i);
				R = GetRValue(color);
				G = GetGValue(color);
				B = GetBValue(color);
				if ((R == 0 && G == 255 && B == 0) || (R == 0 && G == 0 && B == 255))
				{
					_y = _playerRC.bottom + i;
					_jumpPower = 0;
					_jumpCounter = 0;
					_jumpKeyDown = false;
					_downwardThrust = false;
					_state = ONLAND;
					break;
				}
				color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), (_playerRC.right + _playerRC.left) / 2, _playerRC.bottom + i);
				R = GetRValue(color);
				G = GetGValue(color);
				B = GetBValue(color);
				if ((R == 0 && G == 255 && B == 0) || (R == 0 && G == 0 && B == 255))
				{
					_y = _playerRC.bottom + i;
					_jumpPower = 0;
					_jumpCounter = 0;
					_jumpKeyDown = false;
					_downwardThrust = false;
					_state = ONLAND;
					break;
				}
			}
		}
		if (_jumpPower > 0)	//»ó½Â ÁßÀÏ ¶§ ¶¥¿¡ ´êÀ¸¸é ¸ØÃç¶ó
		{
			for (int i = 5; i > 0; --i)
			{
				color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.right, _playerRC.top + i);
				R = GetRValue(color);
				G = GetGValue(color);
				B = GetBValue(color);
				if (R == 0 && G == 255 && B == 0)
				{
					_y = _playerRC.bottom + i;
					_jumpPower = 0;
					break;
				}
				color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.left, _playerRC.top + i);
				R = GetRValue(color);
				G = GetGValue(color);
				B = GetBValue(color);
				if (R == 0 && G == 255 && B == 0)
				{
					_y = _playerRC.bottom + i;
					_jumpPower = 0;
					break;
				}
				color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), (_playerRC.right + _playerRC.left) / 2, _playerRC.top + i);
				R = GetRValue(color);
				G = GetGValue(color);
				B = GetBValue(color);
				if (R == 0 && G == 255 && B == 0)
				{
					_y = _playerRC.bottom + i;
					_jumpPower = 0;
					break;
				}
			}
		}
		if (_rtMoving == true)	//¿À¸¥ÂÊ ÀÌµ¿ Áß¿¡ º®¿¡ ºÎµúÈ÷¸é ¸ØÃç¶ó
		{
			_rtBlock = false;
			color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.right + 2, _playerRC.bottom - 1);
			R = GetRValue(color);
			G = GetGValue(color);
			B = GetBValue(color);
			if (R == 0 && G == 255 && B == 0)
			{
				_rtBlock = true;
			}
			color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.right + 2, _playerRC.top + 1);
			R = GetRValue(color);
			G = GetGValue(color);
			B = GetBValue(color);
			if (R == 0 && G == 255 && B == 0)
			{
				_rtBlock = true;
			}
			color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.right + 2, (_playerRC.top + _playerRC.bottom) / 2);
			R = GetRValue(color);
			G = GetGValue(color);
			B = GetBValue(color);
			if (R == 0 && G == 255 && B == 0)
			{
				_rtBlock = true;
			}
		}
		if (_ltMoving == true)	//¿ÞÂÊ ÀÌµ¿ Áß¿¡ º®¿¡ ºÎµúÈ÷¸é ¸ØÃç¶ó
		{
			_ltBlock = false;
			color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.left - 2, _playerRC.bottom - 1);
			R = GetRValue(color);
			G = GetGValue(color);
			B = GetBValue(color);
			if (R == 0 && G == 255 && B == 0)
			{
				_ltBlock = true;
			}
			color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.left - 2, _playerRC.top + 1);
			R = GetRValue(color);
			G = GetGValue(color);
			B = GetBValue(color);
			if (R == 0 && G == 255 && B == 0)
			{
				_ltBlock = true;
			}
			color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.left - 2, (_playerRC.top + _playerRC.bottom) / 2);
			R = GetRValue(color);
			G = GetGValue(color);
			B = GetBValue(color);
			if (R == 0 && G == 255 && B == 0)
			{
				_ltBlock = true;
			}
		}
		if (_isDamaged == true)	//µ¥¹ÌÁö ÀÔ¾úÀ»¶§ ÇÈ¼¿ÄÝ¸®Á¯
		{
			_rtBlock = false;
			_ltBlock = false;
			color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.right + 2, _playerRC.bottom - 1);
			R = GetRValue(color);
			G = GetGValue(color);
			B = GetBValue(color);
			if (R == 0 && G == 255 && B == 0)
			{
				_rtBlock = true;
			}
			color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.right + 2, _playerRC.top + 1);
			R = GetRValue(color);
			G = GetGValue(color);
			B = GetBValue(color);
			if (R == 0 && G == 255 && B == 0)
			{
				_rtBlock = true;
			}
			color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.right + 2, (_playerRC.top + _playerRC.bottom) / 2);
			R = GetRValue(color);
			G = GetGValue(color);
			B = GetBValue(color);
			if (R == 0 && G == 255 && B == 0)
			{
				_rtBlock = true;
			}
			color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.left - 2, _playerRC.bottom - 1);
			R = GetRValue(color);
			G = GetGValue(color);
			B = GetBValue(color);
			if (R == 0 && G == 255 && B == 0)
			{
				_ltBlock = true;
			}
			color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.left - 2, _playerRC.top + 1);
			R = GetRValue(color);
			G = GetGValue(color);
			B = GetBValue(color);
			if (R == 0 && G == 255 && B == 0)
			{
				_ltBlock = true;
			}
			color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.left - 2, (_playerRC.top + _playerRC.bottom) / 2);
			R = GetRValue(color);
			G = GetGValue(color);
			B = GetBValue(color);
			if (R == 0 && G == 255 && B == 0)
			{
				_ltBlock = true;
			}
			if (_x <= 6) _ltBlock = true;
			if (_x >= IMAGEMANAGER->findImage("bgMap")->getWidth() - 6) _rtBlock = true;
		}
		//¹Ù´Ú¿¡¼­ ¹þ¾î³ª¸é ¶³¾îÁ®¶ó
		color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.right + 1, _playerRC.bottom + 1);
		R = GetRValue(color);
		G = GetGValue(color);
		B = GetBValue(color);
		if (!(R == 0 && G == 255 && B == 0) && !(R == 0 && G == 0 && B == 255))
		{
			color2 = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.left - 1, _playerRC.bottom + 1);
			R2 = GetRValue(color2);
			G2 = GetGValue(color2);
			B2 = GetBValue(color2);
			if (!(R2 == 0 && G2 == 255 && B2 == 0) && !(R == 0 && G == 0 && B == 255))
			{
				color3 = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), (_playerRC.right + _playerRC.left) / 2, _playerRC.bottom + 1);
				R3 = GetRValue(color3);
				G3 = GetGValue(color3);
				B3 = GetBValue(color3);
				if (!(R2 == 0 && G2 == 255 && B2 == 0) && !(R == 0 && G == 0 && B == 255))
				{
					_state = INAIR;
					if (_action != ATTACK) _action = JUMP;
				}
			}
		}
	}
}

void playerBase::physics()
{
	if (_state == INAIR)
	{
		_y -= _jumpPower;
		_jumpPower -= _gravity;
	}
}

void playerBase::frameCounter(float frameMax, float counterMax)
{
	_counter++;
	if (_counter > counterMax)
	{
		_frameX++;
		if (_frameX >= frameMax) _frameX = 0;
		_counter = 0;
	}
}

void playerBase::hangPixelDetect()
{
	COLORREF color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _x, _y - 1);
	int R = GetRValue(color);
	int G = GetGValue(color);
	int B = GetBValue(color);
	if (R == 255 && G == 0 && B == 0)
	{
		_state = HANG;
		_action = HANGING;
	}
	else 
	{
		if (_action == HANGING)
		{
			_state = ONLAND;
			_action = IDLE;
		}
	}
}

bool playerBase::hangPixelDetectUp()
{
	COLORREF color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _x + 6, _y - 26);
	int R = GetRValue(color);
	int G = GetGValue(color);
	int B = GetBValue(color);
	if (R == 0 && G == 255 && B == 0)
	{
		return true;
	}
	else return false;
}

void playerBase::hangPixelDetectDown()
{
	for (int i = 0; i < 3; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _playerRC.right, _playerRC.bottom + i);
		int R = GetRValue(color);
		int G = GetGValue(color);
		int B = GetBValue(color);
		if (R == 0 && G == 255 && B == 0)
		{
			_y = _playerRC.bottom + i;
			_jumpPower = 0;
			_jumpCounter = 0;
			_jumpKeyDown = false;
			_downwardThrust = false;
			_state = ONLAND;
			break;
		}
	}
	//COLORREF color = GetPixel(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _x + 6, _y + 3);
	//int R = GetRValue(color);
	//int G = GetGValue(color);
	//int B = GetBValue(color);
	//if (R == 0 && G == 255 && B == 0)
	//{
	//	_y += 3;
	//	_jumpPower = 0;
	//	_jumpCounter = 0;
	//	_jumpKeyDown = false;
	//	_downwardThrust = false;
	//	_state = ONLAND;
	//	_action = IDLE;
	//}
}

void playerBase::invincibilityCount()
{
	if (_invincibility == true)
	{
		_invincibilityCounter++;
		if (_invincibilityCounter > 60)
		{
			_invincibility = false;
			_invincibilityCounter = 0;
		}
	}
}

void playerBase::attackReaction()
{
	if (_action == ATTACK || _downwardThrust == true)
	{
		_FOM->objectInteraction();
	}
}

void playerBase::setDamagePlayer()
{
	if (_invincibility == false)
	{
		_jumpPower = 3;
		_state = INAIR;
		_counter = 0;
		_currentHP--;
		_GPU->setLife(_currentHP);
		_isDamaged = true;
		_invincibilityCounter = 0;
		_invincibility = true;
	}
}