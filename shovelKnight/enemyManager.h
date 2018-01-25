#pragma once
<<<<<<< HEAD
//#include "enemy1.h"
=======
#include "gameNode.h"
>>>>>>> d68141a767356de0ea070c717c3f4f8ea9e50ab2

class enemyManager
{
public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

