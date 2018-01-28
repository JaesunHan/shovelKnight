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
	_gravity = 0.3f;
	_isFire = 0;
	_stats = ITEM_STATS_GRAVITY;
	_aniName = 0;
	_speed = 0;
	_angle = 0;

	_rc = { 0, 0, 0, 0 };
	_ani = 0;
	_imgWidth = IMAGEMANAGER->findImage(_imgName)->getFrameWidth();
	_imgHeight = IMAGEMANAGER->findImage(_imgName)->getFrameHeight();

	return S_OK;
}

void itemBase::update()
{
	switch (_stats)
	{
	case ITEM_STATS_STOP:
		_add.x = 0;
		_add.y = 0;
		break;
	case ITEM_STATS_GRAVITY:
		_add.y += _gravity;
		break;
	}
	_pt.x += _add.x;
	_pt.y += _add.y;
	reRect();
}

void itemBase::render()
{
	_img->aniRender(BACKBUFFER, _rc.left, _rc.top, _ani);
}

void itemBase::reRect()
{
	_rc = RectMakePointCenter(_pt, _imgWidth, _imgHeight);
}

void itemBase::eatItem()
{
	_isFire = false;
}

void itemBase::fire(ITEM_FIRE itemFire, FPOINT pt)
{
	switch (itemFire)
	{
	case ITEM_FIRE_NULL:
		_speed = 0;
		break;
	case ITEM_FIRE_CENTER:
		_speed = RND->getFromFloatTo(2.f, 5.f);
		_angle = RND->getFromFloatTo(PI16 * 4, PI16 * 12);
		break;
	case ITEM_FIRE_LEFT:
		_speed = RND->getFromFloatTo(2.f, 5.f);
		_angle = RND->getFromFloatTo(PI16 * 9, PI16 * 12);
		break;
	case ITEM_FIRE_RIGHT:
		_speed = RND->getFromFloatTo(2.f, 5.f);
		_angle = RND->getFromFloatTo(PI16 * 4, PI16 * 7);
		break;

		_pt = pt;

		int a = 0;
		string str = _imgName;
		char* str2 = new char[strlen(str.c_str()) + 1 + 4];

		sprintf(str2, "%s%d", _imgName, a);

		while (KEYANIMANAGER->findAnimation(str2) == NULL)
		{
			++a;
			ZeroMemory(str2, sizeof(str2));
			sprintf(str2, "%s%d", _imgName, a);
		}

		_ani = KEYANIMANAGER->addDefaultFrameAnimation(str2, _imgName, 5, true, true);

	}
}


