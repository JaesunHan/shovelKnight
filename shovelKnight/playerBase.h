#pragma once
#include "gameNode.h"
#define HIT_BOX_WIDTH 12
#define HIT_BOX_HEIGHT 25
#define ATTACK_DAMAGE_BOX_WIDTH 10
#define ATTACK_DAMAGE_BOX_HEIGHT 6
#define DOWNATTACK_DAMAGE_BOX_WIDTH 6
#define	DOWNATTACK_DAMAGE_BOX_HEIGHT 10
#define SPEED 4.0f
#define GRAVITY 0.2f
#define JUMPPOWER 6.0f

enum PLAYERDIRECTION
{
	RIGHT = 1,
	LEFT = -1
};

enum PLAYERSTATE
{
	ONLAND,
	INAIR,
	HANG
};

enum PLAYERACTION
{
	IDLE,
	MOVE,
	ATTACK,
	JUMP,
	ROOTING,
	DAMAGED,
	DIE
};

enum COLLISION_PLAYER
{
	CP_NULL,
	CP_OBJECT,
	CP_PLAYER_ENEMY_LEFT,
	CP_PLAYER_ENEMY_RIGHT,
	CP_PLAYER_
};



class playerBase : public gameNode
{
protected : 
	image*				_image;					//플레이어 이미지
	PLAYERDIRECTION		_direction;				//플레이어 상태
	PLAYERSTATE			_state;					//플레이어 위치
	PLAYERACTION		_action;				//플레이어 동작
	COLLISION_PLAYER	_cp;					//플레이어 충돌
	RECT				_rc;					//플레이어 렉트(충돌렉트)
	int					_frameCount;			//프레임카운트
	int					_currentFrameX;			//
	int					_currentFrameY;			//
	int					_currentHP;				//현재 체력
	int					_maxHP;					//최대 체력
	int					_currentMP;				//현재 마나
	int					_money;					//소지금액
	int					_maxMP;					//최대 마나
	int					_skill;					//스킬넘버
	int					_alpha;					//알파값
	float				_x, _y;					//이동좌표	
	float				_jumpPower;				//점프파워
	float				_gravity;				//중력값
	float				_moveSpeed;				//이동속도
	bool				_rtBlock;				//오른쪽 막힘
	bool				_ltBlock;				//왼쪽막힘
	bool				_isDamaged;				//맞았는지
	bool				_skillUsed;				//스킬발동했는지
	bool				_isDead;				//죽었냐?

public:
	playerBase();
	~playerBase();

	virtual HRESULT init(float startX, float startY);
	virtual void release();
	virtual void update();
	virtual void render();

	void hitReAction(int num);
	void attack(float fireX, float fireY, bool skillUsed);
	void move();

	inline float getX() { return _x; }
	inline void setX(float x) { _x = x; }
	inline float getY() { return _y; }
	inline void setY(float y) { _y = y; }
	inline int	getMaxHP() { return _maxHP; }
	inline void setMaxHP(int increaseHP) { _maxHP += increaseHP; }
	inline int	getMaxMP() { return _maxMP; }
	inline void setMaxMP(int increaseMP) { _maxMP += increaseMP; }
	inline int	getMoney() { return _money; }
	inline void setMoney(int increaseMoney) { _money += increaseMoney; }


	inline RECT getPlayerRc() { return _rc; }
	inline COLLISION_PLAYER getCollisionPlayer() { return _cp; }
};

