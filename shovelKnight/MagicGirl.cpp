#include "stdafx.h"
#include "MagicGirl.h"


MagicGirl::MagicGirl()
{

	
}


MagicGirl::~MagicGirl()
{
}

HRESULT MagicGirl::init()
{
	npcBase::init();
	//생성자에 초기화
	//==========가격 세팅 변수===========//
	_fireBallPrice = 1000;							//파이어볼트 얼마니
	_thunderBoltPrice = 4500;						//썬더볼트 얼마니
	_bubblePrice = 9000;							//버블스킬 얼마니

	//==========팔렸는지 확인용 변수들==========//
	_stock = 0;										//몇번이나 상점에서 구매했는지 확인 변수
	_isSellFireBall = false;						//파이어볼 팔렸는지
	_isSellThunderBolt = false;						//썬더볼트 팔렸는지
	_isSellBubble = false;							//버블스킬 팔렸는지

	//=========마더클래스로부터 가져온 변수들 초기화 ==============//
	
	_imgKeyString = "magicGIRLIDLE";				//이미지 매니저에 등록할 이미지 키갑
	_imgFileName = "./image/npc/magicGirlFull.bmp";		//이미지 파일 이름(경로 포함)
		
	//npc이미지
	_img = IMAGEMANAGER->addFrameImage(_imgKeyString, _imgFileName, 1610, 50, 46, 1, true, RGB(255,0,255), false);											// NPC 이미지
	IMAGEMANAGER->addFrameImage("magicGirlBow", "./image/npc/magicGirlThankYou.bmp", 186, 53, 6, 1, true, RGB(255, 0, 255), false);

	_x = 633/2;
	_y = 280/2;

	_img->setCenter(_x, _y);						//이미지 중점좌표로 중점좌표 잡는다. 
	_width = _img->getFrameWidth();					//가로크기
	_height = _img->getFrameHeight();				//세로크기
	_rc = RectMakeCenter(_x, _y, _width, _height);	//상점NPC 렉트
	_npcType = MAGICGIRL;							//NPC타입

	_isCollisionNpc = false;							//플레이어와 충돌했는가? true : 그렇다, false : 아니다

	_isAppear = true;								//기본상태로 맵에서 등장한다.
	//_showshowshowshow = 0;
	//KEYANIMANAGER->addDefaultFrameAnimation("매직걸아이들", "magicGIRLIDLE", 6, false, true);
	int arrIDLE1[46];
	for (int i = 0; i < 46; ++i)
	{
		arrIDLE1[i] = i;
	}
	KEYANIMANAGER->addArrayFrameAnimation("매직걸아이들", "magicGIRLIDLE", arrIDLE1, 46, 3, true);
	

	_anim = KEYANIMANAGER->findAnimation("매직걸아이들");		//NPC 애니메이션
	KEYANIMANAGER->start("매직걸아이들");
	return S_OK;
}



void MagicGirl::sellSkill()
{
	//스킬상점 
	//storeManager에서 골드체크
	//여기서는 순수하게 스킬의 판매(스킬 bool값 true로 바꿔주는 함수)를 한다.
}

void MagicGirl::stockCount()
{
}

void MagicGirl::isCollision(bool collision)
{
	if (collision)
	{
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


			TTTextOut(500, 300, "으앙충돌", 0);
			if (KEYMANAGER->isOnceKeyDown('O'))				//O눌렀을때
			{
				//TTTextOut(300, 300, "으앙충돌", 0);
				if (!_stock)					//한번도 상점에서 구매를 하지 않았으면
				{
					if (_skillUnlockLv == 0)			//플레이어 스킬이 0(삽질)만 있다면
					{
						if (_money >= 1000)				//1000원보다 돈이 많다면
						{
							_minusMoney -= 1000;						//플레이어 골드에서 1000원을 감소하고
							_skillUnlockLv += 1;						//플레이어 스킬을 1로 바꿔준다 (파이어볼)
							_stock = 1;						//한번 구매했으니까 stock을 1로 반환해준다.
						}
						if (_money < 1000)						//플레이어 골드가 1000원보다 작다면
						{
							//str = str4;
						}
					}

				}

				if (_stock == 1)							//한번도 상점에서 구매를 하지 않았으면
				{
					if (_skillUnlockLv == 1)					//플레이어 스킬이 1, 파이어볼이라면 
					{
						if (_money >= 3000)					//3000원보다 돈이 많다면
						{
							_minusMoney -= 3000;						//플레이어 골드에서 3000원을 감소하고 
							_skillUnlockLv += 1;					//플레이어 스킬을 2로 바꿔준다 (선더볼트)
							_stock = 2;						//한번 구매했으니까 stock을 1로 반환해준다.
						}
						if (_money < 3000)						//플레이어 골드가 3000원보다 작다면
						{
							//str = str4;
						}
					}
				}
			}

			if (KEYMANAGER->isOnceKeyDown('P'))
			{

			}
			//NO했을때는 텍스트 아웃으로
			//"어 그...그래? 안녕 ㅃㅃ " 다이얼로그 출력 ㅃㅃ
			//_isCollisionNpc == false;

		}

}

void MagicGirl::render()
{
	if (_isAppear==true)
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

void MagicGirl::draw()
{
	//_img->aniRender(getMemDC(), _rc.left, _rc.top, _anim);
	CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left, _rc.top);
}

void MagicGirl::update()
{
	npcBase::update();

}
