#include "stdafx.h"
#include "item_apple.h"


item_apple::item_apple()
{
}


item_apple::~item_apple()
{
	IMAGEMANAGER->addImage("image/item/drop/apple", "image/item/drop/apple.bmp", 12, 11, true, MAZEN);
}

HRESULT item_apple::init()
{
	return S_OK;
}

void item_apple::release()
{
}

void item_apple::update()
{
}

void item_apple::render()
{
}
