#include "stdafx.h"
#include "skill_fireBall.h"


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
	KEYANIMANAGER->addArrayFrameAnimation("skillFireBallStart", "image/skill/fireBall", fireBallStart, 8, 1, false, startLoopFire, this);

	int fireBallLoop[] = { 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("skillFireBallLoop", "image/skill/fireBall", fireBallLoop, 4, 1, true);
	
	int fireBallOut[] = { 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("skillFireBallOut", "image/skill/fireBall", fireBallOut, 6, 1, false, outFire, this);


	_stats = SKILL_STATS_START;
	_stats = SKILL_STATS_LOOP;
	_stats = SKILL_STATS_OUT;

	_ani = KEYANIMANAGER->findAnimation("skillFireBallStart");
	_ani = KEYANIMANAGER->findAnimation("skillFireBallLoop");
	_ani = KEYANIMANAGER->findAnimation("skillFireBallOut");

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
	case SKILL_STATS_LOOP:
		if (_isRight) _x += speed;
		else if (!_isRight) _x -= speed;
		reRect();
		break;
	case SKILL_STATS_OUT:
		break;
	}
}

void skill_fireBall::render()
{
	if (!_isFire) return;
}

void skill_fireBall::startLoopFire(void* obj)
{
	skill_fireBall* fb = (skill_fireBall*)obj;
	fb->setSkillStats(SKILL_STATS_LOOP);
	fb->setSkillAni(KEYANIMANAGER->findAnimation("skillFireBallLoop"));
	fb->getSkillAni()->start();
}

void skill_fireBall::outFire(void * obj)
{
	skill_fireBall* fb = (skill_fireBall*)obj;
	fb->setIsFire(false);
}