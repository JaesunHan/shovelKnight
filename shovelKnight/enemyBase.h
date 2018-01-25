#pragma once
#include "gameNode.h"

#define GRAVITY	0.9f

//에너미의 상태는 이 부분 맡은 사람이 만들기!
enum ENEMYSTATUS
{
	ENEMY_LEFT_STOP,
	ENEMY_RIGHT_STOP,
	ENEMY_LEFT_MOVE,
	ENEMY_RIGHT_MOVE,
	ENEMY_LEFT_JUMP,
	ENEMY_RIGHT_JUMP,
	ENMEY_LEFT_ATTACK,
	ENEMY_RIGHT_ATTACK,
	ENEMY_LEFT_JUMP_ATTACK,
	ENEMY_RIGHT_JUMP_ATTACK
};

class enemyBase : public gameNode
{
protected:
	image * _img;			  //사용할 이미지
	animation* _anim;		  //사용할 애니메이션
	string _imgKeyString;	  //이미지 매니저에 등록할 이미지 키값

	ENEMYSTATUS _status;	//에너미 상태

	char* _imgFileName;		//이미지 파일 이름(경로 포함)
	float _x, _y;			//적의 중점좌표
	float _jumpPower;		//점프 파워
	float _gravity;			//적용할 중력
	int _width, _height;	//적의 가로, 세로 크기(렉트를 만들 때 사용할 가로세로크기이다.)
	float _playerDistance;  //플레이어와의 거리
	float _speed;

	RECT _rc;				//혹시 사용하게될지도 모를 렉트(충돌용)

public:
	enemyBase();
	~enemyBase();

	virtual HRESULT init(float x, float y) = 0;
	//					이미지매니저에 등록할 키값, 파일 이름,		출력할 초기 위치 x,y
	virtual HRESULT init(string imgKeyString, char* imgFileName, float x, float y, int totalWidth, int totalHeight, int frameX, int frameY);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void draw();

	virtual void move();
	bool isPlayerFind(float playerX, float playerY, int distance);

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
	inline float getJumpPower() { return _jumpPower; }	inline void setJumpPower(float jp) { _jumpPower = jp; }

	//렉트 게터
	inline RECT getRect() { return _rc; }

	//==================================== End 게터 세터 작성하기===================================


};

