#include "stdafx.h"
#include "skill_enemyDeadFx.h"


skill_enemyDeadFx::skill_enemyDeadFx()
{
}


skill_enemyDeadFx::~skill_enemyDeadFx()
{
}

HRESULT skill_enemyDeadFx::init()
{
	skillBase::init();

	IMAGEMANAGER->addFrameImage("image/fx/EnemyDeadFx", "image/fx/EnemyDeadFx.bmp", 120, 16, 5, 1, true, MAZEN);

	return S_OK;
}

void skill_enemyDeadFx::release()
{
	IMAGEMANAGER->deleteImage("image/fx/EnemyDeadFx");
}

void skill_enemyDeadFx::update()
{
	if (!_isFire) return;

	switch (_stats)
	{
	case SKILL_STATS_OUT:
		break;
	}
	reRect();
}

void skill_enemyDeadFx::fire(SKILL_FIRE charType, float x, float y)
{
	skillBase::fire(charType, x, y);

	{
		string str3;
		str3 = "skillEnemyDeadFxOut";

		int num = 0;

		char* str6 = LPSTR_To_String(str3);

		char str7[128];

		itoa(num, str7, 10);

		strcat(str6, str7);

		while (KEYANIMANAGER->findAnimation(str6) != NULL)
		{
			str6 = LPSTR_To_String(str3);
			++num;
			itoa(num, str7, 10);
			strcat(str6, str7);
		}

		_outName = str6;
	}

	int fireBallOut[] = { 0, 1, 2, 3, 4 };
	KEYANIMANAGER->addArrayFrameAnimation(_outName, "image/fx/EnemyDeadFx", fireBallOut, 5, 3, false, isOut, this);

	_img = IMAGEMANAGER->findImage("image/fx/EnemyDeadFx");
	_imgWidth = _img->getFrameWidth();
	_imgHeight = _img->getFrameHeight();
	reRect();

	_ani = KEYANIMANAGER->findAnimation(_outName);
	_stats = SKILL_STATS_OUT;

	_isRight = RND->getInt(2);
	_isFire = true;
	_ani->start();

	_skillWhoDamage = SKILL_DAMAGE_NONE;

}
