#pragma once
#include "gameNode.h"

enum NPCTYPE			//NPC 타입
{
	MAGICGIRL,			//마법상인
	HEALTYGUY,			//체력상인
	BARDKNIGHT,			//음악상인
	ENDNPCTYPE
};


enum NPCSTATUS			//NPC 상태
{
	NPCIDLE,				//대기상태
	NPCTALK,				//대화상태(플레이어와 상호상태)
	NPCUNDERATTACKED,		//공격당하는 상태(플레이어가 공격했을시)//이스터에그로 나중에 넣을까.
	ENDNPCSTATUS
};
//==========================NPC가 어떤 기능이 있어야 할까 고민을 적어놓습니다.==============================
//1. npc타입
//2. npc상태
//3. npc이미지 랜더 
//4. npc대화 다이얼로그
//5. npc대화 후 실제 상점 기능 
//======healthGuy기능======================= 
//5-1. 상점 기능 -> 플레이어 최대체력을 늘려주는 닭고기 -> 플레이어의 최대체력 변수를 받아와서 +1 해줘야함
//5-2. 닭고기 구매하면 골드 차감. 처음은 1000골드 , 두번째는 4500골드, 3번째는 10000골드
//======magicgirl기능=======================
//5-3. 파이어볼 스킬 -> 플레이어 스킬에서 선 작업으로 fireball 스킬 생성
//5-4. 상점에서 파이어 볼을 구매하면 스트링값으로 fireball을 플레이어에서 연결
//6. 이스터에그 - 엔터더건전처럼 만약 플레이어가 상인에게 공격시 3번까지 피격당하며 3회 이후에는 "삐져서 사라짐" 하고 사라지는 기능
//7. 이걸 어떻게 구현하지.....


class npcBase : public gameNode
{
protected:
	image* _img;			// NPC 이미지
	image* _img2;			// NPC 이미지2
	string _imgKeyString;	//이미지 매니저에 등록할 이미지 키갑
	char* _imgFileName;		//이미지 파일 이름(경로 포함)
	animation* _anim;		//NPC 애니메이션
	animation* _anim2;		//npc 애미메이션2

	float _x, _y;			//중점좌표
	int _width, _height;	//충돌 렉트를 만들 때 쓸 가로 세로 크기
	
	RECT _rc;				//상점NPC 렉트
	NPCTYPE _npcType;		//NPC타입
	NPCSTATUS _npcStatus;	//npc스테이터스

	bool _isCollisionNpc;		//플레이어와 충돌했는가? true : 그렇다, false : 아니다
	bool _isAppear;			//등장할때니? 아니니? (맵에서 등장하는지 아닌지 체크)


	int _stock;				//몇번 구매했는지 확인하는 변수
	bool _buyYesorNo;		//상점 열었을때 살래말래?
	bool _isReturn;			//엔터 눌렀느냐

	//===============다이얼로그 변수==================//
	image* _testScript;		
	image* _testScript1;
	image* _testScript2;
	image* _testScript3;
	image* _testScript4;
	image* _testScript5;


	//===========다이얼로그용 벡터 선언===============//
	typedef vector<string> vDialog;
	typedef vector<string>::iterator viDialog;

	vDialog _vDialog;									//npc벡터
	viDialog _viDialog;									//npc벡터이터레이터

public:
	npcBase();
	~npcBase();

	//virtual HRESULT init(string imgKeyString, char* imgFileNmae, float x, float y, int totalWidth, int totalHeight, int frameXx, int frameY, NPCTYPE npctype);
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void draw();

	//==================================== Start 게터 세터 작성하기===================================
	//중점X 게터 세터
	inline float getX() { return _x; }		inline void setX(float x) { _x = x; }
	//중점Y 게터 세터
	inline float getY() { return _y; }		inline void setY(float y) { _y = y; }
	//가로크기 게터 세터
	inline int getWidth() { return _width; }	inline void setWidth(int w) { _width = w; }
	//세로크기 게터 세터
	inline int getHeight() { return _height; }	inline void setHeight(int h) { _height = h; }
	
	//렉트 게터
	inline RECT getRect() { return _rc; }

	//NPC타입 게터
	inline NPCTYPE getNpcType() { return _npcType; }

	//스톡변수 게터 (상점구매횟수)
	inline int getStock() { return _stock; }
	void setStock(int stock) { _stock = stock; }

	//등장변수 셋함수 
	inline void setAppear(bool isAppear) { _isAppear = isAppear; }

	//충돌했나 셋함수
	//void setIsCollision(bool isCollision) { _isCollisionNpc = isCollision; }

	virtual void isCollision(bool collision) = 0;
	bool getIsCollisionNPC() { return _isCollisionNpc; }


	//===========================================ㅈㅅ합니다========================================

	int _skillUnlockLv;
	int getSkillUnlockLv() { return _skillUnlockLv; }
	void setSkillUnlockLv(int asd) { _skillUnlockLv = asd; }


	int _money;
	void setMoney(int asd) { _money = asd; }

	//돈감소
	int _minusMoney;
	int getMinusMoney() { return _minusMoney; }
	void setMinusMoney(int minusMoney) { _minusMoney = minusMoney; }


	//체력상인용 체력겟셋
	int _setMaxHp;
	void setMaxHp(int setMaxHp) { _setMaxHp = setMaxHp; }
	int getMaxHp() { return _setMaxHp; }

	


	//==================================== End 게터 세터 작성하기===================================
};

