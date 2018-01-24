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
	
}
void playerBase::render() 
{

}

void playerBase::hitReAction(int num)
{
	
}

void playerBase::attack(float fireX, float fireY, bool skillUsed)
{
	
}