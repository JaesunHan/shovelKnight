#include "stdafx.h"
#include "itemBase.h"


itemBase::itemBase()
{
	
}


itemBase::~itemBase()
{

}

HRESULT itemBase::init()
{
	_pt = { 0 ,0 };
	_add = { 0, 0 };
	_gravity = 0;
	_isFire = 0;
	_stats = ITEM_STATS_GRAVITY;
	_aniName = 0;

	_rc = { 0, 0, 0, 0 };
	_img = 0;
	_ani = 0;
	_imgWidth = 0;
	_imgHeight = 0;

	return S_OK;
}

void itemBase::render()	
{
	_img->aniRender(IMAGEMANAGER->findImage("backBuffer")->getMemDC(), _pt.x, _pt.y, _ani);
}

void itemBase::reRect()
{
	_rc = RectMakePointCenter(_pt, _imgWidth, _imgHeight);
}

void itemBase::eatItem()
{
	_isFire = false;
}


