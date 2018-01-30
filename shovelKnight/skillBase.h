#pragma once
#include "gameNode.h"

enum SKILL_STATS
{
	SKILL_STATS_START,
	SKILL_STATS_LOOP_L,
	SKILL_STATS_LOOP_R,
	SKILL_STATS_OUT,
};

enum SKILL_REACTION
{
	SKILL_REACTION_DELETE,
};

enum SKILL_FIRE
{
	SKILL_FIRE_CENTER,
	SKILL_FIRE_DRAGON_LEFT,
	SKILL_FIRE_DARKKNIGHT_LEFT,
	SKILL_FIRE_DARKKNIGHT_RIGHT,
};

enum SKILL_DAMAGE
{
	SKILL_DAMAGE_NONE,
	SKILL_DAMAGE_PLAYER,
	SKILL_DAMAGE_PLAYER_AND_ENEMY,
	SKILL_DAMAGE_ENEMY,
};

class skillBase
{
protected:
	float _x;
	float _y;
	RECT _rc;
	image* _img;
	int _imgWidth;
	int _imgHeight;
	animation* _ani;
	bool _isFire;
	bool _isRight;
	SKILL_STATS _stats;

	char* _startName;
	char* _loopNameL;
	char* _loopNameR;
	char* _outName;

	float _saveX;

	SKILL_DAMAGE _skillWhoDamage;

protected:
	char* getStartName() { return _startName; }
	char* getLoopNameL() { return _loopNameL; }
	char* getOutName() { return _outName; }

	void setStartName(char* str) { _startName = str; }
	void setLoopNameL(char* str) { _loopNameL = str; }
	void setOutName(char* str) { _outName = str; }
	virtual void reRect();

public:
	skillBase();
	~skillBase();

	virtual HRESULT init();
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render();

	virtual void fire(SKILL_FIRE charType, float x, float y);

	virtual bool getIsFire() { return _isFire; }
	virtual void setIsFire(bool fire) { _isFire = fire; }

	virtual bool getIsRight() { return _isRight; }
	virtual void setIsRight(bool right) { _isRight = right; }

	virtual SKILL_DAMAGE getIsHavePlayer() { return _skillWhoDamage; }
	virtual void setIsHavePlayer(SKILL_DAMAGE re) { _skillWhoDamage = re; }

	virtual void setPlusSaveX(float x) { _saveX += x; }

	virtual RECT getRect() { return _rc; }

	static void goLoopL(void* obj);
	static void goLoopR(void* obj);
	static void goOut(void* obj);
	static void isOut(void* obj);
};

