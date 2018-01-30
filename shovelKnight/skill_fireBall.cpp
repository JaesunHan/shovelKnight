#include "stdafx.h"
#include "skill_fireBall.h"
#include "skillManager.h"


skill_fireBall::skill_fireBall()
{
}


skill_fireBall::~skill_fireBall()
{
}

HRESULT skill_fireBall::init()
{
	skillBase::init();

	IMAGEMANAGER->addFrameImage("image/skill/fireBall", "image/skill/fireBall.bmp", 252, 42, 12, 2, true, MAZEN);

	return S_OK;
}

void skill_fireBall::release()
{
	KEYANIMANAGER->deleteOne("skillFireBallStart");
	KEYANIMANAGER->deleteOne("skillFireBallLoop");
	KEYANIMANAGER->deleteOne("skillFireBallOut");
	IMAGEMANAGER->deleteImage("image/skill/fireBall");
}

void skill_fireBall::update()
{
	if (!_isFire) return;

	float speed = 3.f;

	switch (_stats)
	{
	case SKILL_STATS_START:
		break;
	case SKILL_STATS_LOOP_L:
		if (_isRight) _x += speed;
		else if (!_isRight) _x -= speed;
		reRect();
		if (getDistance(_x, 0, _saveX, 0) > 100)
		{
			_ani = KEYANIMANAGER->findAnimation(_outName);
			_stats = SKILL_STATS_OUT;
			_ani->start();
		}
		break;
	case SKILL_STATS_OUT:
		break;
	}
	reRect();
}

void skill_fireBall::fire(SKILL_FIRE charType, float x, float y)
{
	skillBase::fire(charType, x, y);

	{
		string str1, str2, str3;
		str1 = "skillFireBallStart";
		str2 = "skillFireBallLoop";
		str3 = "skillFireBallOut";

		int num = 0;

		char* str4 = LPSTR_To_String(str1);
		char* str5 = LPSTR_To_String(str2);
		char* str6 = LPSTR_To_String(str3);

		char str7[128];

		itoa(num, str7, 10);

		strcat(str4, str7);

		while (KEYANIMANAGER->findAnimation(str4) != NULL)
		{
			str4 = LPSTR_To_String(str1);
			++num;
			itoa(num, str7, 10);
			strcat(str4, str7);
		}
		strcat(str5, str7);
		strcat(str6, str7);

		_startName = str4;
		_loopNameL = str5;
		_outName = str6;
	}

	int fireBallStart[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation(_startName, "image/skill/fireBall", fireBallStart, 10, 4, false, goLoop, this);

	int fireBallLoop[] = { 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation(_loopNameL, "image/skill/fireBall", fireBallLoop, 2, 8, true);

	int fireBallOut[] = { 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation(_outName, "image/skill/fireBall", fireBallOut, 6, 7, false, isOut, this);

	_img = IMAGEMANAGER->findImage("image/skill/fireBall");
	_imgWidth = _img->getFrameWidth();
	_imgHeight = _img->getFrameHeight();
	reRect();

	_ani = KEYANIMANAGER->findAnimation(_startName);
	_stats = SKILL_STATS_START;

	_isRight = RND->getInt(2);
	_isFire = true;
	_ani->start();

	//어따쓰지
	_skillWhoDamage = SKILL_DAMAGE_NONE;

}

void * skill_fireBall::goLoop(void* obj)
{
	skill_fireBall* f = (skill_fireBall*)obj;
	f->_ani = KEYANIMANAGER->findAnimation(f->_loopNameL);
	f->_stats = SKILL_STATS_LOOP_L;
	f->_ani->start();

	return NULL;
}

void * skill_fireBall::isOut(void* obj)
{
	skill_fireBall* f = (skill_fireBall*)obj;
	f->_isFire = false;

	return NULL;
}