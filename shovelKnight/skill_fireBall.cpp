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

	int fireBallStart[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("skillFireBallStart", "image/skill/fireBall", fireBallStart, 10, 6, false);

	int fireBallLoop[] = { 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("skillFireBallLoop", "image/skill/fireBall", fireBallLoop, 2, 6, true);
	
	int fireBallOut[] = { 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("skillFireBallOut", "image/skill/fireBall", fireBallOut, 6, 6, false);


	_stats = SKILL_STATS_START;

	_ani = KEYANIMANAGER->findAnimation("skillFireBallStart");

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
		if (_ani->getNowPlayIndex() == 9)
		{
			_stats = SKILL_STATS_LOOP;
			_ani = KEYANIMANAGER->findAnimation("skillFireBallLoop");
			_ani->start();
		}
		break;
	case SKILL_STATS_LOOP:
		break;
	case SKILL_STATS_OUT:

		if (_ani->getNowPlayIndex() == 17)
		{
		}
		break;
	}

	switch (_stats)
	{
	case SKILL_STATS_START:
		break;
	case SKILL_STATS_LOOP:
		if (_isRight) _x += speed;
		else if (!_isRight) _x -= speed;
		reRect();
		break;
	case SKILL_STATS_OUT:
		break;
	}

	KEYANIMANAGER->update();
}

void skill_fireBall::render()
{
	if (!_isFire) return;

	_img->aniRender(IMAGEMANAGER->findImage("backBuffer")->getMemDC(), _x, _y, _ani);
}

void skill_fireBall::fire(SKILL_FIRE charType, float x, float y)
{
	skillBase::fire(charType, x, y);

	_img = IMAGEMANAGER->findImage("image/skill/fireBall");
	_imgWidth = _img->getFrameWidth();
	_imgHeight = _img->getFrameHeight();
	reRect();

	_ani = KEYANIMANAGER->findAnimation("skillFireBallOut");
	_stats = SKILL_STATS_OUT;

	_isRight = RND->getInt(2);
	_isFire = true;
	_ani->start();

}



//void skill_fireBall::outFire(void* obj)
//{
//	skill_fireBall* fb = (skill_fireBall*)obj;
//	fb->setIsFire(false);
//}