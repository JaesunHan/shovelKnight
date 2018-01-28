#include "stdafx.h"
#include "item_gems_silver.h"


item_gems_silver::item_gems_silver()
{
}


item_gems_silver::~item_gems_silver()
{
}

HRESULT item_gems_silver::init()
{
	_imgName = "image/item/gems_silver";
	char* str = new char[strlen(_imgName) + 5];
	sprintf(str, "%s%s", _imgName, ".bmp");

	_img = IMAGEMANAGER->addFrameImage(_imgName, str, 6, 6, 1, 1);
	itemBase::init();

	return S_OK;
}

void item_gems_silver::release()
{
}
