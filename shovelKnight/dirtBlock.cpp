#include "stdafx.h"
#include "dirtBlock.h"


dirtBlock::dirtBlock()
{
}


dirtBlock::~dirtBlock()
{
}
HRESULT dirtBlock::init(float x, float y)
{
	_image = IMAGEMANAGER->findImage("dirtBlock");
	
	settingObj(x, y, 1, true, RGB(100, 100, 100));

	_rc = RectMake(x, y, _image->getWidth(), _image->getHeight());
	return S_OK;
}
void dirtBlock::update()
{
	
}
void dirtBlock::render()
{
	CAMERAMANAGER->renderObject(getMemDC(), _image, _x, _y);
	collisionBox();
}