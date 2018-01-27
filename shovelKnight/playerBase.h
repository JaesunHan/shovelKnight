#pragma once
#include "gameNode.h"
#define HIT_BOX_WIDTH 12
#define HIT_BOX_HEIGHT 25
#define ATTACK_DAMAGE_BOX_WIDTH 10
#define ATTACK_DAMAGE_BOX_HEIGHT 6
#define DOWNATTACK_DAMAGE_BOX_WIDTH 6
#define	DOWNATTACK_DAMAGE_BOX_HEIGHT 10
#define SPEED 4.0f
#define GRAVITY 0.01f
#define JUMPPOWER 0.1f

enum PLAYER_SKILL
{
	SK_NULL,
	SK_FIREBALL
};


enum COLLISIONTYPE
{
	CT_NULL,
	CT_TOP,
	CT_BOTTOM,
	CT_LEFT,
	CT_RIGHT,
	CT_LEFT_BOTTOM,
	CT_RIGHT_BOTTOM
};


enum PLAYERDIRECTION
{
	PD_RIGHT = 1,
	PD_LEFT = -1
};

enum PLAYERSTATE
{
	ONLAND,
	INAIR,
	HANG
};

enum PLAYERACTION
{
	PR_IDLE,
	PR_MOVE,
	PR_ATTACK,
	PR_JUMP,
	PR_ROOTING,
	PR_DAMAGED,
	PR_DIE
};

enum COLLISION_PLAYER //충돌 대상
{
	CP_NULL,
	CP_OBJECT,
	CP_ENEMY,
	CP_GROUND,
	CP_SHOVEL_OBJ,
	CP_SHOVEL_ENEMY

};

enum COLLISION_TB //충돌방향(상하) ->대상기준
{
	TB_NULL,
	TB_TOP,
	TB_BOTTOM
};

enum COLLISION_LR //충돌방향(좌우) ->대상기준
{
	LR_NULL,
	LR_LEFT,
	LR_RIGHT
};

class playerBase : public gameNode
{
protected : 
	image*				_image;					//플레이어 이미지
	PLAYERDIRECTION		_direction;				//플레이어 상태
	PLAYERSTATE			_state;					//플레이어 위치
	PLAYERACTION		_action;				//플레이어 동작
	COLLISION_PLAYER	_cPlayerTarget;			//플레이어 충돌
	COLLISION_TB		_cTB;					//플레이어 충돌방향
	COLLISION_LR		_cLR;					//플레이어 충돌방향
	COLLISIONTYPE		_cType;
	RECT				_rc;					//플레이어 렉트(충돌렉트)
	char*				_characterName;			//캐릭터 네임
	int					_jumpCount;				//점프카운트
	int					_frameCount;			//프레임카운트
	int					_currentFrameX;			//
	int					_currentFrameY;			//
	int					_currentSkill;			//현재 장착된 스킬
	int					_skillUnlockLv;			//스킬 해금 단계
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
	int					probeY;

public:
	playerBase();
	~playerBase();

	virtual HRESULT init(float startX, float startY);
	virtual void release();
	virtual void update();
	virtual void render();

	void hitReAction();
	void attack(float fireX, float fireY, bool skillUsed);
	void move();
	void imageSetting();


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
	inline char* getName() { return _characterName; }
	inline void setName(char* name) { _characterName = name; }
	inline int getSkillUnlockLv() { return _skillUnlockLv; }
	inline void setSkillUnlockLv(int increaseLv) { _skillUnlockLv += increaseLv; }
	inline PLAYERSTATE getState() { return _state; }
	inline void setState(PLAYERSTATE state) { _state = state; }
	inline void setPlayerState(PLAYERDIRECTION pd, PLAYERSTATE ps, PLAYERACTION pa, COLLISION_PLAYER cp, COLLISIONTYPE ct)
	{
		_direction = pd;
		_state = ps;
		_action = pa;
		_cPlayerTarget = cp;
		_cType = ct;
	}

	inline RECT getPlayerRc() { return _rc; }
	inline void setPlayerRc(RECT rc) { _rc = rc; }
	inline COLLISION_PLAYER getCollisionPlayer() { return _cPlayerTarget; }
	
};

