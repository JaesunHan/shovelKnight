#include "stdafx.h"
#include "item_gems_emerald.h"


item_gems_emerald::item_gems_emerald()
{
}


item_gems_emerald::~item_gems_emerald()
{
}

HRESULT item_gems_emerald::init()
{
	_imgName = "image/item/gems_emerald";
	char* str = new char[strlen(_imgName) + 5];
	sprintf(str, "%s%s", _imgName, ".bmp");

	_img = IMAGEMANAGER->addFrameImage(_imgName, str, 8, 8, 1, 1);
	itemBase::init();

	return S_OK;
}

void item_gems_emerald::release()
{
}

void item_gems_emerald::update()
{
}