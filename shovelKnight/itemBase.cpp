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
	_isFire = 0;
	_aniName = 0;
	_speed = 0;
	_angle = 0;

	_rc = { 0, 0, 0, 0 };
	_ani = 0;

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
	switch (_moveType)
	{
	case ITEM_MOVE_GRAVITY:
		{
			switch (itemFire)
			{
			case ITEM_FIRE_NULL:
				_speed = 0;
				break;
			case ITEM_FIRE_CENTER: case ITEM_FIRE_LEFT: case ITEM_FIRE_RIGHT:
				_speed = RND->getFromFloatTo(5.f, 6.f);
				break;
			}

			switch (itemFire)
			{
			case ITEM_FIRE_NULL:
				_angle = 0;
				break;
			case ITEM_FIRE_CENTER:
				_angle = RND->getFromFloatTo(PI16 * 3, PI16 * 13);
				break;
			case ITEM_FIRE_LEFT:
				_angle = RND->getFromFloatTo(PI16 * 10, PI16 * 13);
				break;
			case ITEM_FIRE_RIGHT:
				_angle = RND->getFromFloatTo(PI16 * 3, PI16 * 6);
				break;
			}
			_gravity = 0.3f;
			_stats = ITEM_STATS_GRAVITY;
		}
		break;
	case ITEM_MOVE_STOP:
		break;
	case ITEM_MOVE_PETROL:
		_time = 0;
		_petrol = false;
		break;
	}
	
	//1.7ch
	

	_pt = pt;

	_img = IMAGEMANAGER->findImage(_imgName);
	_imgWidth =	_img->getFrameWidth();
	_imgHeight =_img->getFrameHeight();

	_pt = pt;
	_add.x = +cosf(_angle) * _speed;
	_add.y = -sinf(_angle) * _speed;


	int a = 0;
	char* str = _imgName;
	char* str2 = new char[strlen(str) + 1 + 4];

	sprintf(str2, "%s%d", _imgName, a);

	while (KEYANIMANAGER->findAnimation(str2) != NULL)
	{
		++a;
		ZeroMemory(str2, sizeof(str2));
		sprintf(str2, "%s%d", _imgName, a);
	}

	_ani = KEYANIMANAGER->addDefaultFrameAnimation(str2, _imgName, 5, true, true);
}


