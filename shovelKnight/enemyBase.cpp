#include "stdafx.h"
#include "enemyBase.h"


enemyBase::enemyBase()
{
}


enemyBase::~enemyBase()
{

}


HRESULT enemyBase::init(string imgKeyString, char* imgFileName, float x, float y, int totalWidth, int totalHeight, int frameX, int frameY)
{



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

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{		
		Rectangle(getMemDC(), CAMERAMANAGER->getX(_rc.left), CAMERAMANAGER->getY(_rc.top), 
			CAMERAMANAGER->getX(_rc.right), CAMERAMANAGER->getY(_rc.bottom));

		CAMERAMANAGER->renderMap(getMemDC(), IMAGEMANAGER->findImage("bgMap"));

		Rectangle(getMemDC(), CAMERAMANAGER->getX(_attackRc.left), CAMERAMANAGER->getY(_attackRc.top),
			CAMERAMANAGER->getX(_attackRc.right), CAMERAMANAGER->getY(_attackRc.bottom));
	}

	//자식클래스에 있는 draw() 이던지, 아니면 부모클래스에 있는 draw() 던지 하나는 출력된다.
	//필요하다면 자식클래스의 draw() 함수에서 부모클래스의 draw()를 호출하도록 하자
	draw();

	//TTTextOut(CAMERAMANAGER->getX(_rc.left), CAMERAMANAGER->getY(_y - 10), "힛트", _isHit);
	//TTTextOut(CAMERAMANAGER->getX(_rc.left), CAMERAMANAGER->getY(_y - 20), "상태", _status);
	//TTTextOut(CAMERAMANAGER->getX(_rc.left), CAMERAMANAGER->getY(_rc.bottom + 5), "좌표", _rc.bottom);
}

void enemyBase::draw()
{
	CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left, _rc.top);
}

void enemyBase::move()
{

}

//                           에너미X좌표   반응거리    
bool enemyBase::isPlayerFind(float enemyX, int distance)
{
	//거리계산
	float playerDistance = enemyX - _getPlayerX;

	//에너미 방향설정
	if (playerDistance >= 0) _direction = false;
	else _direction = true;

	playerDistance = fabs(playerDistance);  //절대값

	if (playerDistance <= distance)
	{
		return true;
	}

	return false;
}

void enemyBase::attackCollisionRect()
{

}