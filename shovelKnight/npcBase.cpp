#include "stdafx.h"
#include "npcBase.h"


npcBase::npcBase()
{
}


npcBase::~npcBase()
{

}
//NPC 생성 방향이 바뀌어서 구 init은 폐기 
//HRESULT npcBase::init(string imgKeyString, char* imgFileNmae, float x, float y, int totalWidth, int totalHeight, int frameX, int frameY, NPCTYPE npcType)
//{
//	_imgKeyString = imgKeyString;
//	_imgFileName = imgFileNmae;
//	_x = x;
//	_y = y;
//
//	_npcType = npcType;
//	
//	_img = IMAGEMANAGER->addFrameImage(_imgKeyString, _imgFileName, _x, _y, totalWidth, totalHeight, frameX, frameY, true, RGB(255, 0, 255));
//	_width = _img->getFrameWidth();
//	_height = _img->getFrameHeight();
//	_stock = 0;
//
//	return S_OK;
//}
//새로운 init
HRESULT npcBase::init()
{
	//좌표값, 이미지 기본세팅은 아예 NPC각 클래스에서 세팅되어있으니
	//실제 불러올때는 NPC타입이랑 _isAppear만 받아서 할수 있지 않을까. 
	//_isAppear = appaear;
	_minusMoney = 0;

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
	//draw();
}
void npcBase::draw()
{
	//_img->aniRender(getMemDC(), _rc.left, _rc.top, _anim);
	//CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left, _rc.top);
}

//void npcBase::collisionSignalFromCollisionManager(bool collision)
//{
//	//콜리전 매니저에서 받아오는걸로. 
//	//콜리전 매니저에서 이넘값으로 받아오고
//	//해당 이넘값으로 충돌이 확인되면 w키를 눌러 대화가 가능해지는것으로 구현할것
//
//	if (collision)
//	{
//		isCollision();
//	}
//
//}

void npcBase::isCollision(bool collision)
{
}
