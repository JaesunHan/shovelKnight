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

	_isCollisionNpc = false;						//플레이어와 충돌했는가? true : 그렇다, false : 아니다
	_isAppear = true;								//기본상태로 맵에서 등장하지 않는다.

	int arrIDLE1[26];
	for (int i = 0; i < 26; ++i)
	{
		arrIDLE1[i] = i;
	}										
	KEYANIMANAGER->addArrayFrameAnimation("바드나이트아이들", "BardKnightIDLE", arrIDLE1, 26, 6, true);


	int arrJump[14];
	for (int i = 0; i < 14; ++i)
	{
		arrJump[i] = i;
	}
	KEYANIMANAGER->addArrayFrameAnimation("바드나이트점프", "BardKnightJump", arrJump, 14, 6, true);
	
	//테스트용
	_anim = KEYANIMANAGER->findAnimation("바드나이트아이들");		//NPC 애니메이션
	_anim2 = KEYANIMANAGER->findAnimation("바드나이트점프");		//NPC 애니메이션
	KEYANIMANAGER->start("바드나이트아이들");
	KEYANIMANAGER->start("바드나이트점프");
	

	_testScript = new image;
	_testScript = IMAGEMANAGER->addImage("scriptWindow", "./image/UI/Script_window.bmp", 0, 0, 800, 96, true, RGB(255, 0, 255));
	DIALOGUEMANAGER->setScriptWindow(_testScript);
	
	

	//_testScript1 = new image;
	//_testScript1 = IMAGEMANAGER->addImage("scriptWindow", "./image/UI/Script_window.bmp", 0, 0, 800, 96, true, RGB(255, 0, 255));
	//DIALOGUEMANAGER->setScript("사려면 O키를 안사려면 K키를누르게",255,255,255);
	
	_isCollisionPlayer = false;
	
	_vDialog.push_back("힘세고 좋은 아침, 묻는다면 나는 바드나이트 배경음악을 바꾸겠나?"); //0번
	_vDialog.push_back("바꾸려면 O키를 안바꾸려면 P키를누르게");//1번
	_vDialog.push_back("배경음악을 바꿔주겠네");//2번
	
	//분기선택
	_vDialog2.push_back("배경음악을 바꾸고 싶으면 언제든 말을 걸도록 하게");//0번
	

	_idx = 0;
	_isChange = false;
	_textOut = false;
	_isReturn = false;
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


void BardKnight::isCollision(bool collision)
{
	if (_isAppear)
	{
		if (collision)
		{
			_isCollisionPlayer = collision;
			
			//_idx = 0;
		
			//if (_isReturn)
			//{
			//	DIALOGUEMANAGER->setScript(_vDialog[_idx], 255, 255, 255);
			//}
			//soundChange();
			//텍스트 아웃으로 "너 이거 살래? Yes or No(bool값<-변수 하나 추가해야함 1.25)
			//아래는 Yes 선택했을때의 함수
			//_textOut = true;
			
			_npcStatus = NPCTALK;

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
		else
		{
			_textOut = false;
			_isCollisionPlayer = false;
		}
	}
}

void BardKnight::soundChange()
{
	if (_isChange)
	{
		SOUNDMANAGER->stop("GamePlayBGM");
		if (!SOUNDMANAGER->isPlaySound("BardKnightChange1"))
		{
			SOUNDMANAGER->play("BardKnightChange1", 0.3f);

		}
	}
}

void BardKnight::bardKnightImageControl()
{

	switch (_npcStatus)
	{
	case NPCIDLE:
		_anim = KEYANIMANAGER->findAnimation("바드나이트아이들");		//NPC 애니메이션

		break;

	case NPCTALK:
		_img = IMAGEMANAGER->findImage("BardKnightJump");
		_anim2 = KEYANIMANAGER->findAnimation("바드나이트점프");		//NPC 애니메이션

		break;

	case NPCUNDERATTACKED:
		break;
	}

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

		

		//콜리션 상태일 때만 다이어로그 출력
		if (_isCollisionPlayer)
		{
			DIALOGUEMANAGER->render(getMemDC(), 0, 0, 800, 96);
		}
		


		if (_textOut == true)
		{
			//TTTextOut(500, 100, "바드나이트에서플레이어돈", _money);
			
		}
	}
}

void BardKnight::draw()
{
	//_img->aniRender(getMemDC(), _rc.left, _rc.top, _anim);
	switch (_npcStatus)
	{
	case NPCIDLE: CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left, _rc.top);
		break;
	case NPCTALK: CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim2, _rc.left, _rc.top-10);
		break;
	case NPCUNDERATTACKED:
		break;
	default: CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left, _rc.top);
		break;
	}
	
}



void BardKnight::update()
{
	npcBase::update();
	bardKnightImageControl();
	//콜리션 상태일 때만 업데이트 돈다.
	if(_isCollisionPlayer)
	{
		DIALOGUEMANAGER->update();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _isCollisionPlayer)
	{
		//인덱스값으로 다이얼로그 벡터에 있는 값을 빼낸다
	
			DIALOGUEMANAGER->setScript(_vDialog[_idx], 255, 255, 255);
			
			_idx += 1;
			

		
		if (_idx >= _vDialog.size())	_idx = 0;
	//	if (_idx >= _vDialog2.size())  
	}

	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		soundChange();
		_branch1 = true;
		_branch2 = false;
	}
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		_branch2 = true;
		_branch1 = false;
	}

	if (_branch1)
	{
		_isChange = true;
		DIALOGUEMANAGER->setScript(_vDialog[2], 255, 255, 255);
		_branch1 = false;
		
		
	}
	if (_branch2)
	{
		DIALOGUEMANAGER->setScript(_vDialog2[0], 255, 255, 255);
		_branch2 = false;
	}
}