#include "stdafx.h"
#include "gameObjectBase.h"


gameObjectBase::gameObjectBase()
{
}


gameObjectBase::~gameObjectBase()
{
}

HRESULT gameObjectBase::init(float x, float y)
{

	return S_OK;
}
void gameObjectBase::release()
{

}
void gameObjectBase::update()
{

}
void gameObjectBase::render()
{
	
}
void gameObjectBase::settingObj(float x, float y, int dur, bool isDelete, COLORREF color)
{
	_x = x;
	_y = y;
	_dur = dur;
	_isDelete = isDelete;
	_color = color;
	
}
void gameObjectBase::durAct()
{


}

void gameObjectBase::collisionBox()
{
	HDC hdc = IMAGEMANAGER->findImage("bgMap")->getMemDC();
	HBRUSH brush = CreateSolidBrush(_color);;
	HBRUSH oBrush = (HBRUSH)SelectObject(hdc, brush);
	HPEN pen = CreatePen(PS_SOLID, 1, _color);
	HPEN oPen = (HPEN)SelectObject(hdc, pen);
	Rectangle(hdc, _rc.left
		, _rc.top
		, _rc.right
		, _rc.bottom);
	SelectObject(hdc, oBrush);
	SelectObject(hdc, oPen);
	DeleteObject(brush);
	DeleteObject(pen);
	DeleteObject(oBrush);
	DeleteObject(oPen);
}
