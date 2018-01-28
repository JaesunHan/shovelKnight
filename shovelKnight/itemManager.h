#pragma once
#include "item_apple.h"
#include "item_gems_diapink.h"
#include "item_gems_diared.h"
#include "item_gems_emerald.h"
#include "item_gems_money.h"
#include "item_gems_sapphire.h"
#include "item_gems_silver.h"
#include "item_moneyBunch.h"

#define EFFECTNUM 8

enum ITEM
{
	ITEM_APPLE,
	ITEM_GEMS_DIAPINK,
	ITEM_GEMS_DIARED,
	ITEM_GEMS_EMERALD,
	ITEM_GEMS_MONEY,
	ITEM_GEMS_SAPPHIRE,
	ITEM_GEMS_SILVER,
	ITEM_MONEYBUNCH,
};

class itemManager
{
private:
	typedef vector<itemBase*> vItem;
	typedef vector<itemBase*>::iterator  viItem;
private:
	vItem _vItem;

public:
	itemManager();
	~itemManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void Fire(ITEM_FIRE chartype, ITEM skill, float x, float y);

	virtual vItem getVSkill() { return _vItem; }
};

