#include "stdafx.h"
#include "BardKnight.h"


BardKnight::BardKnight()
{
	//생성자에 초기화
	
}


BardKnight::~BardKnight()
{
}

HRESULT BardKnight::init()
{
	//==========가격 세팅 변수===========//
	_bgmPrice = 100;								//브금체인지 가격
	_effectSoundPrice = 500;						//이펙트사운드 체인지 가격


	//==========팔렸는지 확인용 변수들==========//
	_stock = 0;										//몇번이나 상점에서 구매했는지 확인 변수
	_isSellBgm = false;								//브금 팔렸는지
	_isSellEffectSound = false;						//이펙트 사운드 팔렸는지


	//=========마더클래스로부터 가져온 변수들 초기화 ==============//

	_imgKeyString = "BardKnightIDLE";				//이미지 매니저에 등록할 이미지 키갑
	_imgFileName = "./image/npc/bardKnight.bmp";		//이미지 파일 이름(경로 포함)`

	_img = IMAGEMANAGER->addFrameImage(_imgKeyString, _imgFileName, 1066, 42, 26, 1, true, RGB(255, 0, 255), false);		// NPC 이미지
	IMAGEMANAGER->addFrameImage("BardKnightJump", "./image/npc/bardKnight_jump.bmp", 798, 52, 14, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("BardKnightPlaying", "./image/npc/bardKnight_playing.bmp", 720, 39, 16, 1, true, RGB(255, 0, 255), false);



	_x = 400 / 2;
	_y = 410 / 2;

	_img->setCenter(_x, _y);						//이미지 중점좌표로 중점좌표 잡는다. 
	_width = _img->getFrameWidth();					//가로크기
	_height = _img->getFrameHeight();				//세로크기
	_rc = RectMakeCenter(_x, _y, _width, _height);	//상점NPC 렉트
	_npcType = BARDKNIGHT;							//NPC타입

	_isCollision = false;							//플레이어와 충돌했는가? true : 그렇다, false : 아니다
	_isAppear = true;								//기본상태로 맵에서 등장하지 않는다.

	int arrIDLE1[26];
	for (int i = 0; i < 26; ++i)
	{
		arrIDLE1[i] = i;
	}
	KEYANIMANAGER->addArrayFrameAnimation("바드나이트아이들", "BardKnightIDLE", arrIDLE1, 26, 6, true);
	KEYANIMANAGER->start("바드나이트아이들");

	_anim = KEYANIMANAGER->findAnimation("바드나이트아이들");		//NPC 애니메이션
	return S_OK;
}

void BardKnight::changeBGM()
{
	//fmod 에서 브금채널바꿔주자
}

void BardKnight::changeEffectSound()
{
	//fmod 에서 이펙트 사운드 바꿔주자
}



void BardKnight::render()
{
	if (_isAppear == true)
	{
		draw();
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), CAMERAMANAGER->getX(_rc.left),
			CAMERAMANAGER->getY(_rc.top),
			CAMERAMANAGER->getX(_rc.right),
			CAMERAMANAGER->getY(_rc.bottom));
	}
}

void BardKnight::draw()
{
	//_img->aniRender(getMemDC(), _rc.left, _rc.top, _anim);
	CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left, _rc.top);
}

void BardKnight::update()
{
	npcBase::update();
}
