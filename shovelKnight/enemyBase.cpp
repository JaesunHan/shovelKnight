#include "stdafx.h"
#include "enemyBase.h"


enemyBase::enemyBase()
{
}


enemyBase::~enemyBase()
{

}

HRESULT enemyBase::init(float x, float y)
{
	_jump = new jump;
	_jump->init();

	return S_OK;
}

HRESULT enemyBase::init(string imgKeyString, char* imgFileName, float x, float y, int totalWidth, int totalHeight, int frameX, int frameY)
{
	_imgKeyString = imgKeyString;
	_imgFileName = imgFileName;
	_x = x;
	_y = y;

	_speed = 3.0f;
	_playerDistance = 0.0f;
	_isDead = false;
	_isDeadVanish = false;
	_vanishTime = 1;
	_direction = false;

	_img = IMAGEMANAGER->addFrameImage(_imgKeyString, _imgFileName, _x, _y, totalWidth, totalHeight, frameX, frameY, true, RGB(255, 0, 255));

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_status = ENEMY_LEFT_STOP;

	_width = _img->getFrameWidth();
	_height = _img->getFrameHeight();


	return S_OK;
}

void enemyBase::release()
{

}

void enemyBase::update()
{
	//이동
	move();

	//RECT update
	_rc = RectMakeCenter(_x, _y, _width, _height);



	KEYANIMANAGER->update();
}

void enemyBase::render()
{
	//자식클래스에 있는 draw() 이던지, 아니면 부모클래스에 있는 draw() 던지 하나는 출력된다.
	//필요하다면 자식클래스의 draw() 함수에서 부모클래스의 draw()를 호출하도록 하자
	draw();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{		
		Rectangle(getMemDC(), CAMERAMANAGER->getX(_rc.left), CAMERAMANAGER->getY(_rc.top), 
			CAMERAMANAGER->getX(_rc.right), CAMERAMANAGER->getY(_rc.bottom));
	}

}

void enemyBase::draw()
{
	CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left, _rc.top);
}

void enemyBase::move()
{

}

bool enemyBase::isPlayerFind(float playerX, float playerY, int distance)
{
	_playerDistance = getDistance(playerX, playerY, _x, _y);

	if (_playerDistance <= distance)
	{
		return true;
	}

	return false;
}

