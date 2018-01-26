#pragma once
#include "menuBase.h"
#define MAXHPIMAGE 4
#define MAXCHARACTERKIND	1	//캐릭터 종류 최대 몇개
//HP 관련 구조체
struct tagHPImage
{
	image* hpFull[MAXHPIMAGE];		//2칸짜리 이미지
	image* hpHalf[MAXHPIMAGE];		//한칸짜리 이미지
	int hp;
	float x, y; 
};
//마나 관련 구조체
struct tagMana
{
	image* manaImg;
	int mana;
	float x, y;
};
//자금 관련 구조체
struct tagMoney
{
	image* moneyImg;
	int money;
	float x, y;
};
//캐릭터 이미지 등록할 때 사용할 이미지 KeyString 과 이미지 File Name 을 관리하기 편하게 하기 위한 구조체
struct tagImageKeyNFileName
{
	string imageKeyStr;
	char* imageFileName;
	int totalWidth, totalHeight;
	int frameX, frameY;
};


class playerListMenu : public menuBase
{
	//플레이어의 정보를 보여주는 메뉴(UI)

	//캐릭터를 둘러싼 틀 이미지
	image* _characterTitle;


	//캐릭터 이미지			//애니메이셔
	image* _characterImg;	animation* _characterAnim;
	//이미지 등록할 때 쓸 이미지 키값과 파일 이름
	tagImageKeyNFileName _imgKeyNFile[MAXCHARACTERKIND];	//미리 캐릭터 종류별로 이미지 키값과 파일이름을 저장해두자
	//캐릭터 종류(0 번 : 삽기사)
	int _characterKind;
	//캐릭터 이미지를 출력할 위치
	float _characterX, _characterY;
	//캐릭터의 가로세로 크기
	int _characterW, _characterH;
	//캐릭터 이름 을 저장할 변수
	TCHAR _cName[128];
	//체력 이미지
	tagHPImage _hp;
	//마나 이미지 및 수치
	tagMana _mana;
	//내 자금 이미지 및 수치
	tagMoney _money;
	//내 장비	-> 지금은 안쓸듯
	image* _suit;
	//내 무기	-> 지금은 안쓸듯ㄴ
	image* _weapon;
	

public:
	HRESULT init();
	HRESULT init(char* name, int characterKind, int hp, int mana, int money, int suit, int weapon);
	void update();
	void release();
	void render(HDC hdc);
	void draw(HDC hdc);

	int getHP() { return _hp.hp; }
	playerListMenu();
	~playerListMenu();
};

