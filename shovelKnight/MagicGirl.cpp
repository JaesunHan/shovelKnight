#include "stdafx.h"
#include "MagicGirl.h"


MagicGirl::MagicGirl()
{

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
	_imgFileName = ". / npc / magicGirl.bmp";		//이미지 파일 이름(경로 포함)`
		
	_img = IMAGEMANAGER->addFrameImage(_imgKeyString, _imgFileName, 420, 50, 12, 1, true, RGB(255,0,255), false);											// NPC 이미지

	_img->setCenter(_x, _y);						//이미지 중점좌표로 중점좌표 잡는다. 
	_width = _img->getFrameWidth();					//가로크기
	_height = _img->getFrameHeight();				//세로크기
	_rc = RectMakeCenter(_x, _y, _width, _height);	//상점NPC 렉트
	_npcType = MAGICGIRL;							//NPC타입

	_isCollision = false;							//플레이어와 충돌했는가? true : 그렇다, false : 아니다

	int arrIDLE1[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("매직걸아이들", "magicGIRLIDLE", arrIDLE1, 12, 5, true);
	

	_anim = KEYANIMANAGER->findAnimation("매직걸아이들");		//NPC 애니메이션
}


MagicGirl::~MagicGirl()
{
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
