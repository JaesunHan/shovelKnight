#pragma once
#include "itemBase.h"

class itemManager
{
public:
	itemManager();
	~itemManager();

	virtual HRESULT init()	;
	virtual void release()	;
	virtual void update()	;
	virtual void render()	;
};

