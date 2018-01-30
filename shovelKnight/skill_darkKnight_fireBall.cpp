#include "stdafx.h"
#include "skill_darkKnight_fireBall.h"


skill_darkKnight_fireBall::skill_darkKnight_fireBall()
{
}


skill_darkKnight_fireBall::~skill_darkKnight_fireBall()
{
}

HRESULT skill_darkKnight_fireBall::init()
{
	skillBase::init();

	IMAGEMANAGER->addFrameImage("image/skill/darkKnight_fireBall", "image/skill/darkKnight_fireBall.bmp", 136, 40, 4, 2, true, MAZEN);

	return S_OK;
}

void skill_darkKnight_fireBall::release()
{
}

void skill_darkKnight_fireBall::update()
{
	if (!_isFire) return;

	float speed = 3.f;

	switch (_stats)
	{
	case SKILL_STATS_START:
		break;
	case SKILL_STATS_LOOP_L:
		if (!_isRight) _x -= speed;
		reRect();
		break;

	case SKILL_STATS_LOOP_R:
		if (_isRight) _x += speed;
		reRect();
		break;
	case SKILL_STATS_OUT:
		break;
	}
	reRect();
}

void skill_darkKnight_fireBall::fire(SKILL_FIRE charType, float x, float y)
{

	_img = IMAGEMANAGER->findImage("image/skill/darkKnight_fireBall");
	_imgWidth = _img->getFrameWidth();
	_imgHeight = _img->getFrameHeight();

	skillBase::fire(charType, x, y);

	{
		switch (charType)
		{
		case SKILL_FIRE_DARKKNIGHT_LEFT:
			_isRight = false;
			break;
		case SKILL_FIRE_DARKKNIGHT_RIGHT:
			_isRight = true;
			break;
		}


		int num = 0;
		char str7[128];

		itoa(num, str7, 10);
		char str5[128] = "skillFireBallLoop";

		strcat(str5, str7);


		while (KEYANIMANAGER->findAnimation(str5) != NULL)
		{
			ZeroMemory(str5, sizeof(str5));
			++num;
			itoa(num, str7, 10);
			strcat(str5, str7);

		}
		char str0[128];

		strcpy(str0, str5);
		char* str9;
		str9 = "R";
		strcat(str5, str9);
		str9 = "L";
		strcat(str0, str9);

		_loopNameL = str0;
		_loopNameR = str5;
	}

	int fireBallLoopR[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_loopNameR, "image/skill/darkKnight_fireBall", fireBallLoopR, 4, 8, true);


	int fireBallLoopL[] = { 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation(_loopNameL, "image/skill/darkKnight_fireBall", fireBallLoopL, 4, 8, true);


	int variable = 20;

	if (_isRight)
	{
		_ani = KEYANIMANAGER->findAnimation(_loopNameR);
		_stats = SKILL_STATS_LOOP_R;
		_x += variable;
	}
	else
	{
		_ani = KEYANIMANAGER->findAnimation(_loopNameL);
		_stats = SKILL_STATS_LOOP_L;
		_x -= variable;
	}

	_skillType = SKILL_TYPE_DARKKNIGHT_FIREBALL;

	_isFire = true;
	_ani->start();

	_skillWhoDamage = SKILL_DAMAGE_PLAYER;
}