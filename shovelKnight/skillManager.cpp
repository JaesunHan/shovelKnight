#include "stdafx.h"
#include "skillManager.h"


skillManager::skillManager()
{
}


skillManager::~skillManager()
{
}

HRESULT skillManager::init()
{
	for (int i = 0; i < 4; ++i)
	{
		skillBase* sk;
		switch (i)
		{
		case SKILL_BUBBLE:
			sk = new skill_Bubble;
			break;
		case SKILL_DARKKNIGHT_FIREBALL:
			sk = new skill_darkKnight_fireBall;
			break;
		case SKILL_DIRTBLOCKFX:
			sk = new skill_dirtBlockFx;
			break;
		case SKILL_FIREBALL:
			sk = new skill_fireBall;
			break;
		}
		sk->init();
	}

	return S_OK;
}

void skillManager::release()
{
	viSkill iter;

	if (_vSkill.size())
	{
		for (iter = _vSkill.begin(); iter != _vSkill.end();)
		{
			(*iter)->release();
		}
	}
}

void skillManager::update()
{
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		Fire(SKILL_FIRE_TEST, SKILL_FIREBALL, RND->getFromIntTo(100, WINSIZEX-100), RND->getInt(WINSIZEY));
	}

	if (_vSkill.size())	
	{
		viSkill iter = _vSkill.begin();

		for (; iter != _vSkill.end();)
		{
			if ((*iter)->getIsFire())
			{
				(*iter)->update();
				++iter;
			}
			else
			{
				_vSkill.erase(iter);
			}
		}
	}
}

void skillManager::render()
{
	viSkill iter;

	if (_vSkill.size())
	{
		for (iter = _vSkill.begin(); iter != _vSkill.end(); ++iter)
		{
			(*iter)->render();
		}
	}
}

void skillManager::Fire(SKILL_FIRE chartype, SKILL skill, float x, float y)
{
	skillBase* sk;
	switch (skill)
	{
	case SKILL_BUBBLE:
		sk = new skill_Bubble;
		break;
	case SKILL_DARKKNIGHT_FIREBALL:
		sk = new skill_darkKnight_fireBall;
		break;
	case SKILL_DIRTBLOCKFX:
		sk = new skill_dirtBlockFx;
		break;
	case SKILL_FIREBALL:
		sk = new skill_fireBall;
		break;
	}

	sk->fire(chartype, x, y);

	_vSkill.push_back(sk);
}