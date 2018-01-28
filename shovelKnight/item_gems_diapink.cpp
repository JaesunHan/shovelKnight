#include "stdafx.h"
#include "item_gems_diapink.h"


item_gems_diapink::item_gems_diapink()
{
}


item_gems_diapink::~item_gems_diapink()
{
}

HRESULT item_gems_diapink::init()
{
	_imgName = "image/item/gems_diapink";
	char* str = new char[strlen(_imgName) + 5];
	sprintf(str, "%s%s", _imgName, ".bmp");

	_img = IMAGEMANAGER->addFrameImage(_imgName, str, 21, 16, 1, 1);

	return S_OK;
}

void item_gems_diapink::release()
{
}

void item_gems_diapink::update()
{
}
