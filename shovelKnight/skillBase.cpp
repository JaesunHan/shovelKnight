#include "stdafx.h"
#include "skillBase.h"


skillBase::skillBase()
{
}


skillBase::~skillBase()
{
}

HRESULT skillBase::init()
{
	_x = 0;
	_y = 0;
	_rc = { 0, 0, 0, 0 };
	_img = 0;
	_imgWidth = 0;
	_imgHeight = 0;
	_ani = 0;
	_isFire = 0;
	_isRight = 0;

	return S_OK;
}

void skillBase::release()
{
}

void skillBase::update()
{
}

void skillBase::render()
{
}

void skillBase::fire(float x, float y)
{
	_x = x;
	_y = y;
}

void skillBase::reRect()
{
	_rc = RectMakeCenter(_x, _y, _imgWidth, _imgHeight);
}
