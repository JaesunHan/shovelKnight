#include "stdafx.h"
#include "gameCollision.h"


gameCollision::gameCollision()
{
}


gameCollision::~gameCollision()
{
}

HRESULT gameCollision::init()
{

	return S_OK;
}

void gameCollision::release()
{
}

void gameCollision::update()
{
	RECT enemy;

	//collisionPlayerMap();

	//플레이어와 적의 충돌
	//for (int i = 0; i != enemy.size(); ++i)
	//{
	//	for (int j = 0; j != player.size(); ++j)
	//	{
	//		if (IntersectRect(&temp, &player, &enemy))
	//		{
	//
	//
	//
	//			player			[j]->Reaction(DAMAGE_MAX);
	//			enemy[i]->Reaction(2);
	//		}
	//	}
	//}
	//플레이어와 스킬의 충돌
	//적과 스킬의 충돌
	//플레이어와 item의 충돌

}

void gameCollision::render()
{
}

void gameCollision::collisionPlayerMap()
{
	HDC hdc = IMAGEMANAGER->findImage("bgMap")->getMemDC();

	RECT rc = _player->getPlayerRc();

	int probeX, probeY;

	probeY = rc.bottom;

	for (probeX = rc.left; probeX != rc.right; ++probeX)
	{
		while (!ThisPixelIsMazen(hdc, probeX, probeY))
		{
			--probeY;
		}
	}
	if (probeY == rc.bottom) return;

	_player->setY(_player->getY() + (probeY - rc.bottom));

}
