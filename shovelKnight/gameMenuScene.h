#pragma once
#include "gameNode.h"
#include "player1.h"

#define MAXPLAYERLIST 10

struct playerList
{
	int pNum;
	image* img;
	char* name;
	int hp;
	int mana;
	int money;
};

struct playerNumberBox
{
	RECT numberBox;
	float x;
	float y;
	image* img;
};

class gameMenuScene : public gameNode
{
private:
	string _sceneName;						//씬매니저에 등록할 씬 이름

	image* _backgroundImg;					//백그라운드 이미지
	string _menuBGImgKeyStr;				//이미지 매니저에 등록할 메뉴씬 백그라운드 이미지 키값
	char* _menuBGImgFileName;				//메뉴 씬 백그라운드 파일

	vector<playerList> _vPList; 
	vector<playerList>::iterator _viPList;

	playerNumberBox _pNumberBox[MAXPLAYERLIST];

	//현재 선택한 슬롯을 표시하는 타겟이미지
	image* _targetImg;
	animation* _animTarget;

	int _pSlotIdx;

public:

	HRESULT init();
	void update();
	void release();
	void render();
	void draw();


	
	//======================= Start 게터 세터 =============================
	string getSceneName() { return _sceneName; }
	
	//======================= End 게터 세터 ===============================

	void makePlayerListData();
	//플레이어 리스트가 담긴 ini 파일이 있는지 검사하여 있으면 데이터 읽어오는 기능을 하는 함수
	void loadPlayerListData();

	gameMenuScene();
	~gameMenuScene();
};

