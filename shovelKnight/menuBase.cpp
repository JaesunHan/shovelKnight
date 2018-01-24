#include "stdafx.h"
#include "menuBase.h"


menuBase::menuBase()
{
}


menuBase::~menuBase()
{

}

HRESULT menuBase::init()
{


	return S_OK;
}

HRESULT menuBase::init(string imgKeyString, char* imgFileNmae, float x, float y, int imgWidth, int imgHeight)
{
	_imgKeyString = imgKeyString;
	_imgFileName = imgFileNmae;
	_x = x, _y = y;
	_width = imgWidth;
	_height = imgHeight;

	_menuImg = IMAGEMANAGER->addImage(_imgKeyString, _imgFileName, _width, _height, true, RGB(255, 0, 255));


	return S_OK;
}
void menuBase::update()	
{

}
void menuBase::release()
{

}
void menuBase::render()	
{
	//draw();
}
void menuBase::draw(HDC hdc)	
{
	_menuImg->render(hdc, _x - _width / 2, _y - _height / 2);

}