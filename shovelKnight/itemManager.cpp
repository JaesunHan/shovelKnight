#include "stdafx.h"
#include "itemManager.h"


itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	for (int i = 0; i < EFFECTNUM; ++i)
	{
		itemBase* qw;
	
		switch (i)
		{
		case ITEM_APPLE:
			qw = new item_apple;
			break;
		case ITEM_GEMS_DIAPINK:
			qw = new item_gems_diapink;
			break;
		case ITEM_GEMS_DIARED:
			qw = new item_gems_diared;
			break;
		case ITEM_GEMS_EMERALD:
			qw = new item_gems_emerald;
			break;
		case ITEM_GEMS_MONEY:
			qw = new item_gems_money;
			break;
		case ITEM_GEMS_SAPPHIRE:
			qw = new item_gems_sapphire;
			break;
		case ITEM_GEMS_SILVER:
			qw = new item_gems_silver;
			break;
		case ITEM_MONEYBUNCH:
			qw = new item_moneyBunch;
			break;
		}
		qw->init();
	}

	return S_OK;
}

void itemManager::release()
{
}

void itemManager::update()
{
	if (KEYMANAGER->isOnceKeyDown('Z'))//
	{
		Fire(ITEM_FIRE_NULL, ITEM_GEMS_DIAPINK, WINSIZEX / 2, WINSIZEY / 2);
	}
	
	if (KEYMANAGER->isOnceKeyDown('X'))//
	{
		Fire(ITEM_FIRE_NULL, ITEM_GEMS_DIARED, WINSIZEX / 2, WINSIZEY / 2);
	}
	
	if (KEYMANAGER->isOnceKeyDown('C'))//
	{
		Fire(ITEM_FIRE_NULL, ITEM_GEMS_EMERALD, WINSIZEX / 2, WINSIZEY / 2);
	}
	
	if (KEYMANAGER->isOnceKeyDown('V'))//
	{
		Fire(ITEM_FIRE_NULL, ITEM_MONEYBUNCH, WINSIZEX / 2, WINSIZEY / 2);
	}



	for (int i = 0; i != _vItem.size(); ++i)
	{
		_vItem[i]->update();
	}
}

void itemManager::render()
{
	for (int i = 0; i != _vItem.size(); ++i)
	{
		_vItem[i]->render();
	}
}

void itemManager::Fire(ITEM_FIRE fireType, ITEM item, float x, float y)
{
		itemBase* qw;

		switch (item)
		{
		case ITEM_APPLE:
			qw = new item_apple;
			qw->setImageName("image/item/apple");
			qw->setMoveType(ITEM_MOVE_GRAVITY);
			break;
		case ITEM_GEMS_DIAPINK:
			qw = new item_gems_diapink;
			qw->setImageName("image/item/gems_diapink");
			qw->setMoveType(ITEM_MOVE_STOP);
			break;
		case ITEM_GEMS_DIARED:
			qw = new item_gems_diared;
			qw->setImageName("image/item/gems_diared");
			qw->setMoveType(ITEM_MOVE_STOP);
			break;
		case ITEM_GEMS_EMERALD:
			qw = new item_gems_emerald;
			qw->setImageName("image/item/gems_emerald");
			qw->setMoveType(ITEM_MOVE_STOP);
			break;
		case ITEM_GEMS_MONEY:
			qw = new item_gems_money;
			qw->setImageName("image/item/gems_money");
			qw->setMoveType(ITEM_MOVE_GRAVITY);
			break;
		case ITEM_GEMS_SAPPHIRE:
			qw = new item_gems_sapphire;
			qw->setImageName("image/item/gems_sapphire");
			qw->setMoveType(ITEM_MOVE_GRAVITY);
			break;
		case ITEM_GEMS_SILVER:
			qw = new item_gems_silver;
			qw->setImageName("image/item/gems_silver");
			qw->setMoveType(ITEM_MOVE_GRAVITY);
			break;
		case ITEM_MONEYBUNCH:
			qw = new item_moneyBunch;
			qw->setImageName("image/item/moneyBunch");
			qw->setMoveType(ITEM_MOVE_PETROL);
			break;
		}

		qw->fire(fireType, FPointMake(x, y));

		_vItem.push_back(qw);
}
