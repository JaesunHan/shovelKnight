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
	_npcStatus = NPCIDLE;							//NPC상태 기본은 IDLE
	_isCollisionNpc = false;						//플레이어와 충돌했는가? true : 그렇다, false : 아니다

	_isAppear = true;								//기본상태로 맵에서 등장한다.
	//_showshowshowshow = 0;
	//KEYANIMANAGER->addDefaultFrameAnimation("매직걸아이들", "magicGIRLIDLE", 6, false, true);
	int arrIDLE1[46];
	for (int i = 0; i < 46; ++i)
	{
		arrIDLE1[i] = i;
	}
	KEYANIMANAGER->addArrayFrameAnimation("매직걸아이들", "magicGIRLIDLE", arrIDLE1, 46, 3, true);
	
	int arrBow[6];
	for (int i = 0; i < 6; ++i)
	{
		arrBow[i] = i;
	}
	KEYANIMANAGER->addArrayFrameAnimation("매직걸인사", "magicGirlBow", arrBow, 6, 3, true);


	_anim = KEYANIMANAGER->findAnimation("매직걸아이들");		//NPC 애니메이션
	_anim2 = KEYANIMANAGER->findAnimation("매직걸인사");
	KEYANIMANAGER->start("매직걸아이들");
	KEYANIMANAGER->start("매직걸인사");

	_textOut = false;
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
	if (_isAppear)
	{
		if (collision)
		{
			
			////다이얼로그로 
			////마법상점에 온걸 환영해	
			////너가 살수 있는 스킬은 파이어볼이야 
			////살래?
			//if (_buyYesorNo == true)
			//{
			_textOut = true;
			//	_npcStatus = NPCTALK;
			//	if (KEYMANAGER->isOnceKeyDown('O'))				//산다고 했을때
			//	{
					if (!_stock)					//한번도 상점에서 구매를 하지 않았으면
					{
						if (_skillUnlockLv == 0)			//플레이어 스킬이 0(삽질)만 있다면
						{
							if (_money >= 1000)				//1000원보다 돈이 많다면
							{
								_minusMoney -= 1000;						//플레이어 골드에서 1000원을 감소하고
								_skillUnlockLv += 1;						//플레이어 스킬을 1로 바꿔준다 (파이어볼)
								_stock = 1;									//한번 구매했으니까 stock을 1로 반환해준다.
							}
							if (_money < 1000)						//플레이어 골드가 1000원보다 작다면
							{
								//다이얼로그로 너 돈이 부족하네?	
								
							}
						}

					}
				}
			}
			if (KEYMANAGER->isOnceKeyDown('P'))
			{
				//NO했을때는 텍스트 아웃으로
				//"어 그...그래? 안녕 ㅃㅃ " 다이얼로그 출력 ㅃㅃ
			}
			
			else
			{
				_textOut = false;
			}
		//}
	//}
}

void MagicGirl::magicGirlImageControl()
{

	switch (_npcStatus)
	{
	case NPCIDLE:
		_anim = KEYANIMANAGER->findAnimation("매직걸아이들");		//NPC 애니메이션
															//KEYANIMANAGER->start("매직걸아이들");
		break;

	case NPCTALK:
		_img = IMAGEMANAGER->findImage("magicGirlBow");
		_anim2 = KEYANIMANAGER->findAnimation("매직걸인사");		//NPC 애니메이션
															//KEYANIMANAGER->start("매직걸인사");
		break;

	case NPCUNDERATTACKED:
		break;
	}

}

void MagicGirl::render()
{
	if (_isAppear==true)
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
	if (_textOut)
	{
		TTTextOut(500, 400, "매직걸에서플레이어돈", _money);
		TTTextOut(500, 300, "스킬", _skillUnlockLv);
	}
}

void MagicGirl::draw()
{
	//_img->aniRender(getMemDC(), _rc.left, _rc.top, _anim);
	switch (_npcStatus)
	{
	case NPCIDLE: CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left, _rc.top);
		break;
	case NPCTALK: CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim2, _rc.left, _rc.top);
		break;
	case NPCUNDERATTACKED:
		break;
	default: CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left, _rc.top);
		break;
	}
	
	
}

void MagicGirl::update()
{
	npcBase::update();
	magicGirlImageControl();
}
