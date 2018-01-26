#pragma once
#include "gameNode.h"

enum SKILL_STATS
{
	SKILL_STATS_START,
	SKILL_STATS_LOOP,
	SKILL_STATS_OUT,
};

enum SKILL_REACTION
{
	SKILL_REACTION_DELETE,
};

enum SKILL_FIRE
{
	SKILL_FIRE_TEST,
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
	char* _loopName;
	char* _outName;

	float _saveX;

public:
	skillBase();
	~skillBase();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(SKILL_FIRE charType, float x, float y);
	virtual void reRect();

	virtual bool getIsFire() { return _isFire; }
	virtual void setIsFire(bool fire) { _isFire = fire; }

	virtual void reAction(SKILL_REACTION reaction);

	char* getStartName() { return _startName; }
	char* getLoopName() { return _loopName; }
	char* getOutName() { return _outName; }

	void setStartName(char* str) { _startName = str; }
	void setLoopName(char* str) { _loopName = str; }
	void setOutName(char* str) { _outName = str; }
};

