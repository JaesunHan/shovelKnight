#include "stdafx.h"
#include "item_apple.h"


item_apple::item_apple()
{
}


item_apple::~item_apple()
{
}

HRESULT item_apple::init()
{
	_imgName = "image/item/apple";
	char* str = new char[strlen(_imgName) + 5];
	sprintf(str, "%s%s", _imgName, ".bmp");

	_img = IMAGEMANAGER->addFrameImage(_imgName, str, 12, 11, 1, 1);

	return S_OK;
}

void item_apple::release()
{
}
