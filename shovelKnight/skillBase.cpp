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

void skillBase::goLoopL(void * obj)
{
	skillBase* f = (skillBase*)obj;

	f->_ani = KEYANIMANAGER->findAnimation(f->_loopNameL);
	f->_stats = SKILL_STATS_LOOP_L;
	f->_ani->start();
}

void skillBase::goLoopR(void * obj)
{
	skillBase* f = (skillBase*)obj;
	f->_ani = KEYANIMANAGER->findAnimation(f->_loopNameR);
	f->_stats = SKILL_STATS_LOOP_R;
	f->_ani->start();
}

void skillBase::goLoop(void * obj)
{
	skillBase* f = (skillBase*)obj;

	if (f->_isRight)
	{
		f->_ani = KEYANIMANAGER->findAnimation(f->_loopNameR);
		f->_stats = SKILL_STATS_LOOP_R;
	}
	else
	{
		f->_ani = KEYANIMANAGER->findAnimation(f->_loopNameL);
		f->_stats = SKILL_STATS_LOOP_L;
	}

	f->_ani->start();
}

void skillBase::goOut(void* obj)
{
	skillBase* k = (skillBase*)obj;
	k->_ani = KEYANIMANAGER->findAnimation(k->_outName);
	k->_stats = SKILL_STATS_OUT;
	k->_ani->start();
}

void skillBase::isOut(void* obj)
{
	skillBase* k = (skillBase*)obj;
	k->_isFire = false;
}
