#pragma once
#include "gameNode.h"
#include "jump.h"
#include "pixelCollision.h"

#define GRAVITY	0.9f

//에너미의 상태는 이 부분 맡은 사람이 만들기!
enum ENEMYSTATUS
{
	ENEMY_LEFT_IDLE,
	ENEMY_RIGHT_IDLE,
	ENEMY_LEFT_SMILE,
	ENEMY_RIGHT_SMILE,
	ENEMY_LEFT_MOVE,
	ENEMY_RIGHT_MOVE,
	ENEMY_LEFT_BACK_MOVE,
	ENEMY_RIGHT_BACK_MOVE,
	ENEMY_LEFT_JUMP,
	ENEMY_RIGHT_JUMP,
	ENEMY_LEFT_ATTACK,
	ENEMY_RIGHT_ATTACK,
	ENEMY_LEFT_JUMP_ATTACK,
	ENEMY_RIGHT_JUMP_ATTACK,
	ENEMY_LEFT_FIRE_ATTACK,
	ENEMY_RIGHT_FIRE_ATTACK,
	ENEMY_LEFT_HIT,
	ENEMY_RIGHT_HIT,
	ENEMY_LEFT_DEAD,
	ENEMY_RIGHT_DEAD,
	ENEMY_LEFT_JUMP_DEAD,
	ENEMY_RIGHT_JUMP_DEAD
};

enum ENEMYTYPE
{
	ENEMY_BEETO,
	ENEMY_BLORB,
	ELEMY_DRAKE,
	ENEMY_SKELETON,
	ENEMY_DRAGON,
	ENEMY_BLACKKNIGHT
};

enum PATTERNTYPE
{
	ENEMY_BASIC,
	ENEMY_PATROL,
	ENEMY_LEFT_FOWARD,
	ENEMY_RIGHT_FOWARD
};

class enemyBase : public gameNode
{
protected:
	image * _img;					//사용할 이미지
	animation* _anim;				//사용할 애니메이션
	string _imgKeyString;			//이미지 매니저에 등록할 이미지 키값

	ENEMYSTATUS _status;			//에너미 상태
	ENEMYSTATUS _previousStatus;    //에너미 이전상태
	ENEMYTYPE _enemyType;			//에너미타입

	RECT _attackRect;               //공격 렉트
	RECT _rc;						//혹시 사용하게될지도 모를 렉트(충돌용)
	RECT _ImageRc;                  //보스1이미지렉트
	RECT _trunkRc;                  //보스1충돌렉트: 몸통

	char* _imgFileName;				//이미지 파일 이름(경로 포함)
	float _x, _y;					//적의 중점좌표
	float _gravity;					//적용할 중력
	int _width, _height;			//적의 가로, 세로 크기(렉트를 만들 때 사용할 가로세로크기이다.)
	float _angle;					//이동 각도
	int _enemyHp;					//적 체력
	float _speed;					//적 스피드
	bool _direction;				//적 방향

	float _getPlayerX;				//플레이어 x좌표 get
	int _playerStatus;				//플레이어 상태
	bool _playerFind;				//플레이어 발견

	bool _isDead;					//죽었는지 여부
	bool _isDeadVanish;				//죽고 벡터에서 지울 불값
	int _vanishTime;				//죽었을때 사라지게할 여유타임 카운트

	bool _isJump;					//점프여부
	int _jumpCount;					//점프카운트

	int _directionCount;			//방향전환 카운트
	bool _isCountStop;				//패턴카운트 스톱

	bool _isAttack;					//attack 상태
	bool _isHit;					//플레이어 어택 충돌
	bool _isHitDelayTime;           //hit 지연시간 불값
	int _delayCount;                //hit 지연시간 카운트

	int _patternTypeNum;            //패턴타입
	int _frameCount;                //상태별 프레임 카운트

	bool _isDialogueEnd;
	bool _isAniPlayEnd;
	int _patternTrun;
	int _patternCount;
	bool _isFight;

	

	jump* _jump;					//액션: 점프
	pixelCollision* _pixelC;		//액션: 픽셀충돌

public:
	enemyBase();
	~enemyBase();

	//					이미지매니저에 등록할 키값, 파일 이름,		출력할 초기 위치 x,y
	virtual HRESULT init(string imgKeyString, char* imgFileName, float x, float y, int totalWidth, int totalHeight, int frameX, int frameY);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void draw();

	virtual HRESULT init(float x, float y) = 0;
	virtual HRESULT init(float x, float y, int patternType) = 0;
	virtual void enemyInitSet() = 0;
	virtual void enemyPattern(int _patternTypeNum) = 0;
	virtual void move() = 0;
	virtual void attackCollisionRect();

	bool isPlayerFind(float enemyX, int distance);

	//==================================== Start 게터 세터 작성하기===================================

	//중점X 게터 세터
	inline float getX() { return _x; }		inline void setX(float x) { _x = x; }
	//중점Y 게터 세터
	inline float getY() { return _y; }		inline void setY(float y) { _y = y; }
	//가로크기 게터 세터
	inline int getWidth() { return _width; }	inline void setWidth(int w) { _width = w; }
	//세로크기 게터 세터
	inline int getHeight() { return _height; }	inline void setHeight(int h) { _height = h; }
	//점프파워 게터 세터
	/*inline float getJumpPower() { return _jumpPower; }	inline void setJumpPower(float jp) { _jumpPower = jp; }*/

	//렉트 게터
	inline RECT getRect() { return _rc; }

	//적 상태 접근자 & 설정자
	ENEMYSTATUS getStatus() { return _status; }   	
	void setStatus(ENEMYSTATUS status) { _status = status; }
	bool getIsDeadVanish() { return _isDeadVanish; }					//죽고 사라지는 불값
	ENEMYTYPE getEnemyType() { return _enemyType; }						//에네미타입

	//플레이어 참조 접근자
	void getPlayerX(float playerX) { _getPlayerX = playerX; }			//플레이어 X    get
	void getPlayerStatus(int status) { _playerStatus = status; }        //플레이어 상태 get

	//데미지 설정자
	int getEnemyHp() { return _enemyHp; }
	void setEnemyDamage() { _isHit = true; }

	//충돌렉트 게터
	RECT getBoss1TrunkRect() { return _trunkRc; }  //몸통렉트

	//==================================== End 게터 세터 작성하기===================================


};

