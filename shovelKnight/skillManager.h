#pragma once
#include "skill_darkKnight_fireBall.h"
#include "skill_dirtBlockFx.h"
#include "skill_fireBall.h"
#include "skill_bubble.h"

enum SKILL
{
	SKILL_BUBBLE,
	SKILL_DARKKNIGHT_FIREBALL,
	SKILL_DIRTBLOCKFX,
	SKILL_FIREBALL,
};

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

	virtual void Fire(SKILL skill, float x, float y);
};

