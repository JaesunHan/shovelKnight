#include "stdafx.h"
#include "skill_Bubble.h"


skill_Bubble::skill_Bubble()
{
}


skill_Bubble::~skill_Bubble()
{
}

HRESULT skill_Bubble::init()
{
	skillBase::init();

	IMAGEMANAGER->addFrameImage("image/skill/bubble", "image/skill/bubble.bmp", 148, 70, 4, 2, true, MAZEN);

	return S_OK;
}

void skill_Bubble::release()
{
}

void skill_Bubble::update()
{
	if (!_isFire) return;

	float speed = 3.f;

	switch (_stats)
	{
	case SKILL_STATS_LOOP_L:
		if (_startX - 200 > _x)
		{
			_y -= speed / 2;
		}
		else
		{
			if (_isRight) _x += speed;
			else if (!_isRight) _x -= speed;
		}
		reRect();
		break;
	case SKILL_STATS_OUT:
		break;
	}
	reRect();
}

void skill_Bubble::fire(SKILL_FIRE charType, float x, float y)
{
	skillBase::fire(charType, x - 50, y + 30);
	_startX = x - 50;

	{
		string str2, str3;
		str2 = "skillBubbleLoop";
		str3 = "skillBubbleOut";

		int num = 0;
		char* str5 = LPSTR_To_String(str2);
		char* str6 = LPSTR_To_String(str3);

		char str7[128];

		itoa(num, str7, 10);

		strcat(str5, str7);

		while (KEYANIMANAGER->findAnimation(str5) != NULL)
		{
			str5 = LPSTR_To_String(str2);
			++num;
			itoa(num, str7, 10);
			strcat(str5, str7);
		}
		strcat(str6, str7);

		_loopNameL = str5;
		_outName = str6;
	}

	int fireBallLoop[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_loopNameL, "image/skill/bubble", fireBallLoop, 4, 8, true);

	int fireBallOut[] = { 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation(_outName, "image/skill/bubble", fireBallOut, 2, 3, false, isOut, this);

	_img = IMAGEMANAGER->findImage("image/skill/bubble");
	_imgWidth = _img->getFrameWidth();
	_imgHeight = _img->getFrameHeight();
	reRect();

	_ani = KEYANIMANAGER->findAnimation(_loopNameL);
	_stats = SKILL_STATS_LOOP_L;

	_isRight = false;
	_isFire = true;
	_ani->start();
}

void * skill_Bubble::isOut(void * obj)
{
	skill_Bubble* f = (skill_Bubble*)obj;
	f->_isFire = false;

	return NULL;
}
