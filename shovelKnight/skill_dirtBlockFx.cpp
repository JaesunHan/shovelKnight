#include "stdafx.h"
#include "skill_dirtBlockFx.h"


skill_dirtBlockFx::skill_dirtBlockFx()
{
}


skill_dirtBlockFx::~skill_dirtBlockFx()
{
}

HRESULT skill_dirtBlockFx::init()
{
	skillBase::init();

	IMAGEMANAGER->addFrameImage("image/fx/dirtBlockFx", "image/fx/dirtBlockFx.bmp", 135, 38, 3, 1, true, MAZEN);

	return S_OK;
}

void skill_dirtBlockFx::release()
{
	IMAGEMANAGER->deleteImage("image/fx/dirtBlockFx");
}

void skill_dirtBlockFx::update()
{
	if (!_isFire) return;

	float speed = 3.f;

	switch (_stats)
	{
		break;
	case SKILL_STATS_OUT:
		break;
	}
}

void skill_dirtBlockFx::fire(SKILL_FIRE charType, float x, float y)
{
	skillBase::fire(charType, x, y);

	{
		string str3;
		str3 = "skillFireBallOut";

		int num = 0;

		char* str6 = PTSTR_To_String(str3);

		char str7[128];

		itoa(num, str7, 10);

		strcat(str6, str7);

		while (KEYANIMANAGER->findAnimation(str6) != NULL)
		{
			str6 = PTSTR_To_String(str3);
			++num;
			itoa(num, str7, 10);
			strcat(str6, str7);
		}

		_outName = str6;
	}

	int fireBallOut[] = { 0, 1, 2 };
	KEYANIMANAGER->addArrayFrameAnimation(_outName, "image/fx/dirtBlockFx", fireBallOut, 3, 3, false, isOut, this);

	_img = IMAGEMANAGER->findImage("image/fx/dirtBlockFx");
	_imgWidth = _img->getFrameWidth();
	_imgHeight = _img->getFrameHeight();
	reRect();

	_ani = KEYANIMANAGER->findAnimation(_outName);
	_stats = SKILL_STATS_OUT;

	_isRight = RND->getInt(2);
	_isFire = true;
	_ani->start();

}

void * skill_dirtBlockFx::isOut(void * obj)
{
	skill_dirtBlockFx* k = (skill_dirtBlockFx*)obj;

	k->_isFire = false;

	return NULL;
}
