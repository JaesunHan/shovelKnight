#pragma once
#include "gameNode.h"
#include "enemyBase.h"

#include <vector>


class enemyManager : public gameNode
{
private:
	vector<enemyBase*>				_vEnemy;
	vector<enemyBase*>::iterator	_viEnemy;

private:
	class

public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

