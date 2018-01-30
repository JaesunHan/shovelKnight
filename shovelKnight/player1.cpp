#include "stdafx.h"
#include "player1.h"


player1::player1()
{
}


player1::~player1()
{

}

HRESULT player1::init()
{
	_x = 100;
	_y = 100;
	_isDead = false;
	_isDamaged = false;
	_currentHP = _maxHP = 8;
	_currentMP = _maxMP = 30;
	_skillUsed = false;
	_action = JUMP;
	_state = INAIR;
	_direction = RIGHT;
	_skill = NULL;
	_moveSpeed = SPEED;
	_gravity = GRAVITY;
	_jumpPower = 0;
	_ltBlock = false;
	_rtBlock = false;

	_playerRC = RectMake(_x - HIT_BOX_WIDTH / 2, _y - HIT_BOX_HEIGHT, HIT_BOX_WIDTH, HIT_BOX_HEIGHT);
	IMAGEMANAGER->addFrameImage("Idle", ".\\image\\shovelKnight\\shovelKnightIdle.bmp", 34, 62, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("Move", ".\\image\\shovelKnight\\shovelKnightRunning.bmp", 276, 66, 6, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("Jump", ".\\image\\shovelKnight\\shovelKnightJump.bmp", 68, 68, 2, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("Attack", ".\\image\\shovelKnight\\shovelKnightAttack.bmp", 264, 70, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("DownwardThrust", ".\\image\\shovelKnight\\shovelKnightDownAttack.bmp", 24, 70, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("Shine", ".\\image\\shovelKnight\\shovelKnightShine.bmp", 102, 62, 3, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("Dead", ".\\image\\shovelKnight\\shovelKnightDead.bmp", 126, 68, 3, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("Damaged", ".\\image\\shovelKnight\\shovelKnightDamaged.bmp", 40, 76, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("Hanging", ".\\image\\shovelKnight\\shovelKnightClimb.bmp", 48, 76, 2, 2, true, RGB(255, 0, 255), true);


	return S_OK;
}

void player1::release()
{

}

void player1::update() 
{
	if (_pause == false)
	{
		if (_isDamaged == false) control();
		physics();
		pixelCollision();
		control2();
		attack();
		invincibilityCount();
		CAMERAMANAGER->setSingleFocus(_x, _y, WINSIZEX);
	}
	if (_currentHP <= 0 && _isDead == false)
	{
		_frameX = 0;
		_isDead = true;
	}
	if (_downwardThrust == true) _playerRC = RectMake(_x - HIT_BOX_WIDTH / 2, _y - HIT_BOX_HEIGHT, HIT_BOX_WIDTH, HIT_BOX_HEIGHT - 5);
	else _playerRC = RectMake(_x - HIT_BOX_WIDTH / 2, _y - HIT_BOX_HEIGHT, HIT_BOX_WIDTH, HIT_BOX_HEIGHT);
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		if (_isDead == true) SCENEMANAGER->changeScene("GameTitleScene");
	}
}

void player1::render() 
{
	if (_isDead == true)
	{
		_counter++;
		_pause = true;
		CAMERAMANAGER->frameRenderObject(getMemDC(), IMAGEMANAGER->findImage("Dead"), _x - 21, _y - 26, _frameX, _direction);
		if (_counter > 30 && _frameX < 2)
		{
			_frameX++;
			_counter = 0;
		}
	}
	else if(_isDamaged == true)
	{
		_counter++;
		if (_counter % 2 == 0) CAMERAMANAGER->frameRenderObject(getMemDC(), IMAGEMANAGER->findImage("Damaged"), _x - 20, _y - 38, 0, _direction);
		if (_counter > 35)
		{
			_isDamaged = false;
		}
	}
	else
	{
		if (_action == IDLE)
		{
			if (_shine == true) CAMERAMANAGER->frameRenderObject(getMemDC(), IMAGEMANAGER->findImage("Shine"), _x - 17, _y - 31, _shineFrameX, _direction);
			else CAMERAMANAGER->frameRenderObject(getMemDC(), IMAGEMANAGER->findImage("Idle"), _x - 17, _y - 31, 0, _direction);
		}
		if (_action == MOVE)
		{
			CAMERAMANAGER->frameRenderObject(getMemDC(), IMAGEMANAGER->findImage("Move"), _x - 23, _y - 33, _frameX, _direction);
			frameCounter(6, 5);
		}
		if (_action == JUMP)
		{
			if (_downwardThrust == true)
			{
				CAMERAMANAGER->frameRenderObject(getMemDC(), IMAGEMANAGER->findImage("DownwardThrust"), _x - 12, _y - 31, 0, _direction);
			}
			else if (_jumpPower >= 0) CAMERAMANAGER->frameRenderObject(getMemDC(), IMAGEMANAGER->findImage("Jump"), _x - 17, _y - 34, 0, _direction);
			else if (_jumpPower < 0) CAMERAMANAGER->frameRenderObject(getMemDC(), IMAGEMANAGER->findImage("Jump"), _x - 17, _y - 34, 1, _direction);
		}
		if (_action == ATTACK)
		{
			CAMERAMANAGER->frameRenderObject(getMemDC(), IMAGEMANAGER->findImage("Attack"), _x - 33, _y - 35, _frameX, _direction);
			_counter++;
			if (_counter > 4)
			{
				_frameX++;
				if (_frameX >= 4)
				{
					_action = IDLE;
					_frameX = 0;
					_counter = 0;
					_isAttacking = false;
				}
				_counter = 0;
			}
		}
		if (_action == HANGING)
		{
			CAMERAMANAGER->frameRenderObject(getMemDC(), IMAGEMANAGER->findImage("Hanging"), _x - 12, _y - 38, 0, _frameX);
			frameCounter(2, 10);
		}
	}

	//char testX[128];
	//int testx = _x;
	//wsprintf(testX, "playerX : %d", testx);
	//TextOut(getMemDC(), 200, 100, testX, strlen(testX));
	//char testY[128];
	//int testy = _y;
	//wsprintf(testY, "playerY : %d", testy);
	//TextOut(getMemDC(), 200, 120, testY, strlen(testY));

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(),
			CAMERAMANAGER->getX(_playerRC.left),
			CAMERAMANAGER->getY(_playerRC.top),
			CAMERAMANAGER->getX(_playerRC.right),
			CAMERAMANAGER->getY(_playerRC.bottom));
		Rectangle(getMemDC(),
			CAMERAMANAGER->getX(_attackRC.left),
			CAMERAMANAGER->getY(_attackRC.top),
			CAMERAMANAGER->getX(_attackRC.right),
			CAMERAMANAGER->getY(_attackRC.bottom));
	}
	//TTTextOut(300, 0, "playerX", _x);
	//TTTextOut(300, 20, "playerY", _y);
}

void player1::control2()
{
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_state == INAIR) _downwardThrust = true;
		hangPixelDetect();
		if (_state == HANG)
		{
			_y += SPEED;
			hangPixelDetectDown();
		}
	}
	if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		_jumpPower = 3;
		_state = INAIR;
		_isDamaged = true;
		_currentHP--;
		_counter = 0;
		//_isDead = true;
	}
	if (_rtBlock == false && _ltBlock == false && _isDamaged == true)
	{
		_x += (_direction * 2 - 1) * 0.5f;
	}
}

void player1::attack()
{
	if (_isDamaged == false && _isDead == false)
	{
		if (_action == JUMP && _downwardThrust == true)
		{
			_attackRC = RectMakeCenter(_x + (_direction * 2 - 1), _y, 8, 9);
		}
		else if (_action == ATTACK)
		{
			switch (_frameX)
			{
			case(0):
				_attackRC = RectMakeCenter(_x + (-9) * (_direction * 2 - 1), _y - 4, 10, 8);
				break;
			case(1):
				_attackRC = RectMakeCenter(_x + (-27) * (_direction * 2 - 1), _y - 11, 10, 8);
				break;
			case(2):
				_attackRC = RectMakeCenter(_x + (-16) * (_direction * 2 - 1), _y - 22, 10, 8);
				break;
			case(3):
				_attackRC = RectMakeCenter(_x + (13) * (_direction * 2 - 1), _y - 24, 10, 8);
				break;
			}
		}
		else
		{
			_attackRC = RectMake(0, 0, 0, 0);
		}
	}
	else
	{
		_attackRC = RectMake(0, 0, 0, 0);
	}
}
