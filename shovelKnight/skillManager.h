#pragma once
#include "skill_darkKnight_fireBall.h"
#include "skill_dirtBlockFx.h"
#include "skill_fireBall.h"
#include "skill_bubble.h"
#include "skill_enemyDeadFx.h"
#include "gameNode.h"

#define EFFECTNUM 5

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

	virtual void Fire(SKILL_FIRE chartype, SKILL skill, float x, float y);

	virtual vSkill getVSkill() { return _vSkill; }
};

