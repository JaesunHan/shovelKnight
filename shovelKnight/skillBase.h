#pragma once
#include "gameNode.h"

enum SKILL_STATS
{
	SKILL_START,
	SKILL_LOOP,
	SKILL_OUT,
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
	

public:
	skillBase();
	~skillBase();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(float x, float y);
	virtual void reRect();
	virtual void setIsFire(bool fire) { _isFire = fire; }

	virtual SKILL_STATS getSkillStats() { return _stats; }
	virtual void setSkillStats(SKILL_STATS stats) { _stats = stats; }

	virtual animation* getSkillAni() { return _ani; }
	virtual void setSkillAni(animation* ani) { _ani = ani; }
};

