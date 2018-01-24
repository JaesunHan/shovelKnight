#pragma once
#include "skill1.h"

class skillManager
{
private:
	typedef vector<skillBase*> vSkill;
	typedef vector<skillBase*>::iterator viSkill;

private:
	vSkill _vSkill;

public:
	skillManager();
	~skillManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

