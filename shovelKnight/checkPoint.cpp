#include "stdafx.h"
#include "checkPoint.h"


checkPoint::checkPoint()
{
}


checkPoint::~checkPoint()
{

}

HRESULT checkPoint::init(float x, float y)
{
	settingObj(x, y, 2, false, RGB(99, 99, 99));
	_isOn = false;
	_isCheck = false;
	_currentFrameX = 0;
	_currentFrameY = 0;
	return S_OK;

	int lightOn[] = { 0,1,2,3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("lightOn", "checkPoint", lightOn, 5, 10, false);

}
void checkPoint::update()
{
	if (_isOn)
	{
		
	}
}
void checkPoint::render()
{

}
