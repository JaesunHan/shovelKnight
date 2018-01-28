#include "stdafx.h"
#include "item_gems_sapphire.h"


item_gems_sapphire::item_gems_sapphire()
{
}


item_gems_sapphire::~item_gems_sapphire()
{
}

HRESULT item_gems_sapphire::init()
{
	_imgName = "image/item/gems_sapphire";
	char* str = new char[strlen(_imgName) + 5];
	sprintf(str, "%s%s", _imgName, ".bmp");

	_img = IMAGEMANAGER->addFrameImage(_imgName, str, 9, 12, 1, 1);

	return S_OK;
}

void item_gems_sapphire::release()
{
}
