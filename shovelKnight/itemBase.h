#pragma once
#include "gameNode.h"

enum ITEM_STATS
{
	ITEM_STATS_STOP,
	ITEM_STATS_GRAVITY,
};

enum ITEM_FIRE
{
	ITEM_FIRE_NULL,
	ITEM_FIRE_CENTER,
	ITEM_FIRE_LEFT,
	ITEM_FIRE_RIGHT,
};

enum ITEM_MOVE_TYPE
{
	ITEM_MOVE_GRAVITY,
	ITEM_MOVE_STOP,
	ITEM_MOVE_PETROL,
};

class itemBase
{
protected:
	FPOINT _pt;
	FPOINT _add;
	float _gravity;
	bool _isFire;
	ITEM_STATS _stats;
	ITEM_MOVE_TYPE _moveType;
	char* _imgName;
	char* _aniName;
	float _speed;
	float _angle;

	RECT _rc;
	image* _img;
	animation* _ani;
	int _imgWidth;
	int _imgHeight;


public:
	itemBase();
	~itemBase();

	virtual HRESULT init();
	virtual void release() = 0;
	virtual void update();
	virtual void render();

	virtual void reRect();
	virtual void eatItem();

	virtual void setImageName(char* img) { _imgName = img; }
	virtual void setMoveType(ITEM_MOVE_TYPE moveType) { _moveType = moveType; }
	
	virtual void fire(ITEM_FIRE itemFire, FPOINT pt);
};

