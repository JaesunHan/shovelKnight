#pragma once
#include "gameNode.h"
#include "player1.h"
#include "playerListMenu.h"
#include "createCharacterMenu.h"

#define MAXPLAYERLIST 10

class gamePlayScene;
struct playerList
{
	int pNum;			//저장되어 있는 캐릭터슬롯 번호
	image* img;			//캐릭터 이미지
	int characterkind;	//캐릭터 종류 : 0번은 삽기사
	TCHAR name[128];			//캐릭터의 닉넴
	int hp;				//HP
	int mana;			//마나
	int money;			//가지고 있는 돈
	int suit;			//0 번이 기본수트
	int weapon;			//0 번이 기본무기(삽)
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
	//현재 선택한 슬롯 인텍스
	int _pSlotIdx;
	//플레이어 리스트 정보를 답고있는 배열
	playerList _pList[MAXPLAYERLIST];

	//플레이어 정보를 보여주는 메뉴
	playerListMenu* _plm[MAXPLAYERLIST];
	//캐릭터 만들으러 가자는 메뉴 (게임에서  "처음부터"라고 뜨는 메뉴 말하는 거임)
	createCharacterMenu* _ccm;

	image* _testScript;

	//플레이 그라운드가 가지고 있는 게임플ㄹ레이 씬의 정보를 저장할 변수
	gamePlayScene* _GPS;
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

	//새로운 캐릭터를 생성해서 ini 데이터 파일에저장하는 함수
	void createNewDefaultCharacter();
	//인트형을 ini 파일에 저장하기 위한 함수
	//							저장할 ini파일이름, 서브젝트 네임,			타이틀,			저장할 인트형 데이터
	void addNsaveINTDataInINIFile(char* fileName, char subjectName[256], char title[256], int data);

	//플레이 그라운드가 가지고 있는 게임플레이씬의 정복 가져오기
	void setGamePlaySceneAdressLink(gamePlayScene* gps) { _GPS = gps; }

	gameMenuScene();
	~gameMenuScene();
};

