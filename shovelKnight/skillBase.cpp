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

void skillBase::render()
{
	if (!_isFire) return;

	CAMERAMANAGER->aniRenderObject(BACKBUFFER, _img, _ani, _rc.left, _rc.top);
}

void skillBase::fire(SKILL_FIRE charType, float x, float y)
{
	_saveX = _x = x;
	_y = y;
	reRect();

	_isFire = true;
}

void skillBase::reRect()
{
	_rc = RectMakeCenter(_x, _y, _imgWidth, _imgHeight);
}

void skillBase::reAction(SKILL_REACTION reaction)
{
	switch (reaction)
	{
	case SKILL_REACTION_DELETE:
		_isFire = false;
		break;
	}
}
