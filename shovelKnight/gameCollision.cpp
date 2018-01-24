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
	//RECT temp;
	//RECT player;
	//RECT enemy;
	////플레이어와 적의 충돌
	//for (int i = 0; i != enemy.size(); ++i)
	//{
	//	for (int j = 0; j != player.size(); ++j)
	//	{
	//		if (IntersectRect(&temp, &player, &enemy))
	//		{
	//
	//
	//
	//			player[j]->Reaction(DAMAGE_MAX);
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
