#include "stdafx.h"
#include "HealtyGuy.h"


HealtyGuy::HealtyGuy()
{

	
}


HealtyGuy::~HealtyGuy()
{
}

HRESULT HealtyGuy::init()
{
	//생성자에 초기화
	//==========가격 세팅 변수===========//
	_chicken = 1000;								//칰힌 가격
	_drgonTail = 4500;								//용꼬리 가격


													//==========팔렸는지 확인용 변수들==========//
	_stock = 0;										//몇번이나 상점에서 구매했는지 확인 변수
	_isSellChicken = false;							//칰힌 팔렸는지
	_isSellDragonTail = false;						//용꼬리 팔렸는지


													//=========마더클래스로부터 가져온 변수들 초기화 ==============//

	_imgKeyString = "HealtyGuyIdle";				//이미지 매니저에 등록할 이미지 키갑
	_imgFileName = "./image/npc/healthGuyStand.bmp";		//이미지 파일 이름(경로 포함)`

	//NPC 이미지
	_img = IMAGEMANAGER->addFrameImage(_imgKeyString, _imgFileName, 70, 47, 2, 1, true, RGB(255, 0, 255), false);											// NPC 이미지
	IMAGEMANAGER->addFrameImage("HealtyGuyGood", "./image/npc/healthGuyGood.bmp", 168, 67, 4, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("HealtyGuyCook", "./image/npc/healthGuyBackCook.bmp", 897, 43, 23, 1, true, RGB(255, 0, 255), false);



	_x = 220/2;
	_y = 280/2;


	_img->setCenter(_x, _y);						//이미지 중점좌표로 중점좌표 잡는다. 
	_width = _img->getFrameWidth();					//가로크기
	_height = _img->getFrameHeight();				//세로크기
	_rc = RectMakeCenter(_x, _y, _width, _height);	//상점NPC 렉트
	_npcType = HEALTYGUY;							//NPC타입



	_isCollision = false;							//플레이어와 충돌했는가? true : 그렇다, false : 아니다
	_isAppear = true;								//기본상태로 맵에서 등장하지 않는다.

	int arrIDLE1[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("헬스가이아이들", "HealtyGuyIdle", arrIDLE1, 2, 2, true);
	KEYANIMANAGER->start("헬스가이아이들");

	_anim = KEYANIMANAGER->findAnimation("헬스가이아이들");		//NPC 애니메이션

	return S_OK;
}

void HealtyGuy::sellHpItem()
{
}

void HealtyGuy::render()
{
	if (_isAppear == true)
	{
		draw();
	}
}

void HealtyGuy::draw()
{
	//_img->aniRender(getMemDC(), _rc.left, _rc.top, _anim);
	CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left, _rc.top);
}
