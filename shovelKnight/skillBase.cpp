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
