#include "stdafx.h"
#include "item_gems_diared.h"


item_gems_diared::item_gems_diared()
{
}


item_gems_diared::~item_gems_diared()
{
}

HRESULT item_gems_diared::init()
{
	_imgName = "image/item/gems_diared";
	char* str = new char[strlen(_imgName) + 5];
	sprintf(str, "%s%s", _imgName, ".bmp");

	_img = IMAGEMANAGER->addFrameImage(_imgName, str, 17, 13, 1, 1);
	itemBase::init();

	return S_OK;
}

void item_gems_diared::release()
{
}

void item_gems_diared::update()
{
}
