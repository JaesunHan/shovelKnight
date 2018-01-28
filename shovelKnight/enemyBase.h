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
	ENEMY_LEFT_MOVE,
	ENEMY_RIGHT_MOVE,
	ENEMY_LEFT_BACK_MOVE,
	ENEMY_LEFT_JUMP,
	ENEMY_RIGHT_JUMP,
	ENEMY_LEFT_ATTACK,
	ENEMY_RIGHT_ATTACK,
	ENEMY_LEFT_JUMP_ATTACK,
	ENEMY_RIGHT_JUMP_ATTACK,
	ENEMY_LEFT_HIT,
	ENEMY_RIGHT_HIT,
	ENEMY_LEFT_DEAD,
	ENEMY_RIGHT_DEAD
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


class enemyBase : public gameNode
{
protected:
	image * _img;				//사용할 이미지
	animation* _anim;			//사용할 애니메이션
	string _imgKeyString;		//이미지 매니저에 등록할 이미지 키값

	ENEMYSTATUS _status;		//에너미 상태


	char* _imgFileName;			//이미지 파일 이름(경로 포함)
	float _x, _y;				//적의 중점좌표
	float _gravity;				//적용할 중력
	int _width, _height;		//적의 가로, 세로 크기(렉트를 만들 때 사용할 가로세로크기이다.)
	float _angle;               //이동 각도

	float _getPlayerX;             //플레이어 x좌표 get
	int _playerStatus;          //플레이어 상태
	float _speed;				//스피드
	bool _isDead;				//죽었는지 여부
	bool _isDeadVanish;			//죽고 벡터에서 지울 불값
	int _vanishTime;			//죽었을때 사라지게할 여유타임 카운트
	bool _direction;            //방향
	bool _isJump;               //점프여부
	int _jumpCount;             //점프카운트
	int _directionCount;        //방향전환 카운트
	bool _isHit;                //플레이어 어택 충돌
	int _enemyHp;               //적 체력

	ENEMYTYPE _enemyType;       //에너미타입


	RECT _rc;					//혹시 사용하게될지도 모를 렉트(충돌용)

	jump* _jump;                //액션: 점프
	pixelCollision* _pixelC;    //액션: 픽셀충돌

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
	virtual void move() = 0;
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
	void setEnemyDamage(bool damage) { _isHit = damage; }

	//==================================== End 게터 세터 작성하기===================================


};

