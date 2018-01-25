#include "stdafx.h"
#include "npcBase.h"


npcBase::npcBase()
{
}


npcBase::~npcBase()
{

}

HRESULT npcBase::init(string imgKeyString, char* imgFileNmae, float x, float y, int totalWidth, int totalHeight, int frameX, int frameY, NPCTYPE npcType)
{
	_imgKeyString = imgKeyString;
	_imgFileName = imgFileNmae;
	_x = x;
	_y = y;

	_npcType = npcType;
	
	_img = IMAGEMANAGER->addFrameImage(_imgKeyString, _imgFileName, _x, _y, totalWidth, totalHeight, frameX, frameY, true, RGB(255, 0, 255));
	_width = _img->getFrameWidth();
	_height = _img->getFrameHeight();


	return S_OK;
}
void npcBase::release()
{

}
void npcBase::update() 
{
	_rc = RectMakeCenter(_x, _y, _width, _height);
}
void npcBase::render() 
{
	//자식클래스에 있는 draw() 이던지, 아니면 부모클래스에 있는 draw() 던지 하나는 출력된다.
	//필요하다면 자식클래스의 draw() 함수에서 부모클래스의 draw()를 호출하도록 하자
	draw();
}
void npcBase::draw()
{

}