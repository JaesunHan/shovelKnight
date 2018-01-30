#pragma once
#include "gameNode.h"
#define HIT_BOX_WIDTH 12
#define HIT_BOX_HEIGHT 25
#define ATTACK_DAMAGE_BOX_WIDTH 10
#define ATTACK_DAMAGE_BOX_HEIGHT 6
#define DOWNATTACK_DAMAGE_BOX_WIDTH 6
#define	DOWNATTACK_DAMAGE_BOX_HEIGHT 10
#define SPEED 1.7f
#define GRAVITY 0.2f
#define JUMPPOWER 3.0f

enum PLAYER_SKILL
{
	SK_NULL,
	SK_FIREBALL
};

enum PLAYERDIRECTION
{
	RIGHT,
	LEFT
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
	HANGING,
	ROOTING,
	DAMAGED,
	DIE
};

class stageManager;
class gameCollision;
class skillManager;
class gamePlayUI;
class frontObjectManager;

class playerBase : public gameNode
{
protected : 
	PLAYERDIRECTION		_direction;				//플레이어 상태
	PLAYERSTATE			_state;					//플레이어 위치
	PLAYERACTION		_action;				//플레이어 동작
	RECT _playerRC;					
	RECT _attackRC;
	char*				_characterName;			//캐릭터 네임
	int	_frameX = 0;	
	int _shineFrameX = 0;						//빛나기 휘안 밫나기만을 위한 프레임
	int _counter = 0;
	int _jumpCounter = 0;
	int _shineCounter = 0;						//빛나기 위한 빛나기만을 위한 카운터
	int _invincibilityCounter = 0;
	int	_currentSkill = 0;			//현재 장착된 스킬
	int					_currentHP;				//현재 체력
	int					_maxHP;					//최대 체력
	int					_currentMP;				//현재 마나
	int					_maxMP;					//최대 마나
	int	_money = 40000;							//소지금액
	int					_skill;					//스킬넘버
	int					_alpha;					//알파값
	float				_x, _y;					//이동좌표	
	float				_jumpPower;				//점프파워
	float				_gravity;				//중력값
	float				_moveSpeed;				//이동속도
	bool _rtBlock = false;				
	bool _ltBlock = false;				
	bool _rtMoving = false;
	bool _ltMoving = false;
	bool _jumpKeyDown = false;
	bool _isAttacking = false;
	bool _downwardThrust = false;
	bool _shine = false;
	bool _pause = false;
	bool _isDamaged = false;				//맞았는지
	bool				_skillUsed;				//스킬발동했는지
	bool				_isDead;				//죽었냐?
	bool _invincibility = false;
	bool _fireBall = false;	//파이어볼 스킬

	stageManager* _SM;
	gameCollision* _GC;
	skillManager* _skillM;
	gamePlayUI* _GPU;
	frontObjectManager* _FOM;

public:
	playerBase();
	~playerBase();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void control();
	void physics();
	void pixelCollision();
	void hangPixelDetect();
	bool hangPixelDetectUp();
	void hangPixelDetectDown();
	void frameCounter(float frameMax, float counterMax);
	void invincibilityCount();
	void attackReaction();
	void setDamagePlayer();
	void setPlatformMovementLR(int speed);


	inline float getPlayerX() { return _x; }
	inline void setPlayerX(float x) { _x = x; }
	inline float getPlayerY() { return _y; }
	inline void setPlayerY(float y) { _y = y; }
	inline void setPlayerHp(int maxHp) { _currentHP = maxHp; }
	inline int	getPlayerMaxHP() { return _maxHP; }
	inline void setPlayerMaxHP(int increaseHP) { _maxHP += increaseHP; }
	inline int	getPlayerMaxMP() { return _maxMP; }
	inline void setPlayerMaxMP(int increaseMP) { _maxMP += increaseMP; }
	inline int	getMoney() { return _money; }
	inline void setMoney(int increaseMoney) { _money += increaseMoney; }
	inline char* getName() { return _characterName; }
	inline void setName(char* name) { _characterName = name; }
	inline void setSkillUnlockLv(int skillLv) 
	{ 
		int skillLevel = skillLv; 
		switch (skillLevel)
		{
		case(1):
			_fireBall = true;
			break;
		}
	}
	inline void setSMMemoryAddressLink(stageManager* sm) { _SM = sm; }
	inline void setGameCollisinMemoryAddressLink(gameCollision* gc) { _GC = gc; }
	inline void setSkillManagerMemoryAddressLink(skillManager* skillm) { _skillM = skillm; }
	inline void setGamePlayUIMemoryAddressLink(gamePlayUI* gpu) { _GPU = gpu; }
	inline void setFrontObjectManagerMemoryAddressLink(frontObjectManager* fom) { _FOM = fom; }
	inline void setPause(bool pause) { _pause = pause; }
	inline RECT getPlayerRC() { return _playerRC; }
	inline RECT getAttackRC() { return _attackRC; }
	//IDLE = 0, MOVE = 1, ATTACK = 2, JUMP = 3, ROOTING = 4, DAMAGED = 5, DIE = 6
	inline int getPlayerAction() { return _action; }
	inline void setAttackReaction() 
	{
		if (_downwardThrust == true)
		{
			_jumpPower = 4;
			_jumpCounter = 30;
		}
		else
		{
			if (_direction == RIGHT)
			{
				_x -= 2;
			}
			else if (_direction == LEFT)
			{
				_x += 2;
			}
		}
	}
	
};

