#pragma once
#include "player1.h"

class playerManager
{
private : 
	playerBase* _p1;


public:
	playerManager();
	~playerManager();

<<<<<<< HEAD
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();



=======
	virtual HRESULT init()	;
	virtual void release()	;
	virtual void update()	;
	virtual void render()	;
>>>>>>> c9811846013293f1afab64946bd0f7637a6e928e
};

