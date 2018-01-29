#pragma once
#include "dirtBlock.h"
#include "dirtPile.h"
#include "checkPoint.h"
#include "tresureBox.h"
#include <vector>
enum OBJECTNUM
{
	OBJ_DIRTBLOCK,
	OBJ_DIRTPILE,
	OBJ_CHECKPOINT,
	OBJ_TRESUREBOX
};

class gameObjectManager
{
private :
	typedef vector<gameObjectBase*> vObj;
private : 
	vObj _vObj;

public:
	gameObjectManager();
	~gameObjectManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual vObj getVObj() { return _vObj; }
	//virtual void setVObjDur(int i, int dur) { _vObj[i]->setDur(dur); }
	virtual void settingObject(float x, float y, OBJECTNUM obj);
};

