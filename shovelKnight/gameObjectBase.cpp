#include "stdafx.h"
#include "gameObjectBase.h"


gameObjectBase::gameObjectBase()
{
}


gameObjectBase::~gameObjectBase()
{
}

HRESULT gameObjectBase::init(float x, float y, string imageKeyName, int dur)
{
	_x = x;
	_y = y;
	_dur = dur;
	_image = IMAGEMANAGER->findImage(imageKeyName);
	_rc = RectMakeCenter(x, y, _image->getWidth(), _image->getHeight());
	
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
	//_image->render(getMemDC(), _rc.left, _rc.top);
}