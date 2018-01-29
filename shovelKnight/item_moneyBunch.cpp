#include "stdafx.h"
#include "item_moneyBunch.h"


item_moneyBunch::item_moneyBunch()
{
}


item_moneyBunch::~item_moneyBunch()
{
}

HRESULT item_moneyBunch::init()
{
	_imgName = "image/item/moneyBunch";
	char* str = new char[strlen(_imgName) + 5];
	sprintf(str, "%s%s", _imgName, ".bmp");

	_img = IMAGEMANAGER->addFrameImage(_imgName, str, 114, 29, 3, 1);

	return S_OK;
}

void item_moneyBunch::release()
{
}

void item_moneyBunch::update()
{
	_time += TIMEMANAGER->getElapsedTime();

	while (_time > 1.8f)
	{
		_time -= 1.8f;
		_petrol = !_petrol;

	}

	_ani->getNowPlayIndex();

	if (_petrol)
	{
		_add.y += _gravity;
	}
	else
	{
		_add.y -= _gravity;
	}

	_pt.y += _add.y;
	reRect();
}