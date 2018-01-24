#include "stdafx.h"
#include "itemBase.h"


itemBase::itemBase()
{
	
}


itemBase::~itemBase()
{

}

HRESULT itemBase::init(string imgKeyString, char* imgFileName, float x, float y, int totalWidth, int totalHeight, int frameX, int frameY)
{
	_imgKeyString = imgKeyString;
	_imgFileName = imgFileName;
	_x = x, _y = y;

	_img = IMAGEMANAGER->addFrameImage(_imgKeyString, _imgFileName, _x, _y, totalWidth, totalHeight, frameX, frameY, true, RGB(255, 0, 255));
	_width = _img->getFrameWidth();
	_height = _img->getFrameHeight();

	return S_OK;
}
void itemBase::update()	
{
	_rc = RectMakeCenter(_x, _y, _width, _height);
}
void itemBase::release()
{

}
void itemBase::render()	
{
	draw();
}
void itemBase::draw()	
{

}