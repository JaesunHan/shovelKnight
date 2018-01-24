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
	viSkill iter;

	if (_vSkill.size())
	{
		for (iter = _vSkill.begin(); iter != _vSkill.end();)
		{
			(*iter)->release();
		}
	}

	return S_OK;
}

void skillManager::release()
{
}

void skillManager::update()
{
	viSkill iter;
	
	if (_vSkill.size())
	{
		for (iter = _vSkill.begin(); iter != _vSkill.end(); ++iter)
		{
			(*iter)->update();
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
