#include "stdafx.h"
#include "item_gems_money.h"


item_gems_money::item_gems_money()
{
}


item_gems_money::~item_gems_money()
{
}

HRESULT item_gems_money::init()
{
	_imgName = "image/item/gems_money";
	char* str = new char[strlen(_imgName) + 5];
	sprintf(str, "%s%s", _imgName, ".bmp");

	_img = IMAGEMANAGER->addFrameImage(_imgName, str, 13, 9, 1, 1);

	return S_OK;
}

void item_gems_money::release()
{
}
