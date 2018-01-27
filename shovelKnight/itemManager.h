#pragma once
#include "itemBase.h"

#define EFFECTNUM 5

enum ITEM
{
	
	
	
	
	
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

	virtual HRESULT init()	;
	virtual void release()	;
	virtual void update()	;
	virtual void render()	;
};

