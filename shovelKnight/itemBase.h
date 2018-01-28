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

class itemBase
{
protected:
	FPOINT _pt;
	FPOINT _add;
	float _gravity;
	bool _isFire;
	ITEM_STATS _stats;
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


	virtual void fire(ITEM_FIRE itemFire, FPOINT pt);
};

