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
	npcBase::init();
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

	_isCollisionNpc = false;							//플레이어와 충돌했는가? true : 그렇다, false : 아니다
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

	_isChange = false;
	_textOut = false;						//테스트용
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

		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			Rectangle(getMemDC(), CAMERAMANAGER->getX(_rc.left),
				CAMERAMANAGER->getY(_rc.top),
				CAMERAMANAGER->getX(_rc.right),
				CAMERAMANAGER->getY(_rc.bottom));
		}
	}
	if (_textOut==true)
	{
		TTTextOut(500, 100, "바드나이트에서플레이어돈", _money);
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

void BardKnight::isCollision(bool collision)
{
	if (collision)
	{
		
		//soundChange();
		//텍스트 아웃으로 "너 이거 살래? Yes or No(bool값<-변수 하나 추가해야함 1.25)
		//아래는 Yes 선택했을때의 함수
		char* str1 = "Welcome, Welcome My friend";
		char* str2 = "you wanna buy some weed?:P";
		char* str3 = "if u OK press 'O', or not press 'P'";
		char* str4 = "get the fuck off!!!!";

		////init
		//int stats = 0;
		//
		//char* str = str1;
		//if(strlen(str)==strlen(str1) && stats = 0) str = str2;
		////


		TTTextOut(500, 300, "으앙충돌1", 0);
		
		_textOut = true;
		_isChange = true;
		soundChange();
		//if (KEYMANAGER->isOnceKeyDown('O'))				//O눌렀을때
		//{
		//	//TTTextOut(300, 300, "으앙충돌", 0);
		//	if (!_stock)					//한번도 상점에서 구매를 하지 않았으면
		//	{
		//		if (_money >= 1000)				//1000원보다 돈이 많다면
		//			{
		//				_minusMoney -= 1000;			//플레이어 골드에서 1000원을 감소하고
		//				_stock = 1;						//한번 구매했으니까 stock을 1로 반환해준다.
		//			}
		//			if (_money < 1000)						//플레이어 골드가 1000원보다 작다면
		//			{
		//				//str = str4;
		//			}
		//		}

		//	}

		//	if (_stock == 1)							//한번도 상점에서 구매를 하지 않았으면
		//	{
		//		if (_skillUnlockLv == 1)					//플레이어 스킬이 1, 파이어볼이라면 
		//		{
		//			if (_money >= 3000)					//3000원보다 돈이 많다면
		//			{
		//				_minusMoney -= 3000;						//플레이어 골드에서 3000원을 감소하고 
		//				_skillUnlockLv += 1;					//플레이어 스킬을 2로 바꿔준다 (선더볼트)
		//				_stock = 2;						//한번 구매했으니까 stock을 1로 반환해준다.
		//			}
		//			if (_money < 3000)						//플레이어 골드가 3000원보다 작다면
		//			{
		//				//str = str4;
		//			}
		//		}
		//	}
		//}

		//if (KEYMANAGER->isOnceKeyDown('P'))
		//{

		//}
		////NO했을때는 텍스트 아웃으로
		////"어 그...그래? 안녕 ㅃㅃ " 다이얼로그 출력 ㅃㅃ
		////_isCollisionNpc == false;



	}
}

void BardKnight::soundChange()
{
	SOUNDMANAGER->stop("GamePlayBGM");
	if (!SOUNDMANAGER->isPlaySound("BardKnightChange1"))
	{
		SOUNDMANAGER->play("BardKnightChange1", 0.3f);
		
	}
}
