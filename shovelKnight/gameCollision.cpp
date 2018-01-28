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

	for (int i = 0; i != _enemy->getVEnemy().size(); ++i)
	{
		switch (_enemy->getVEnemy()[i]->getEnemyType())
		{
		case ENEMY_BEETO:
			if (_enemy->getVEnemy()[i]->getStatus() == ENEMY_LEFT_DEAD ||
				_enemy->getVEnemy()[i]->getStatus() == ENEMY_RIGHT_DEAD)
			{
				_skill->Fire(SKILL_FIRE_CENTER, SKILL_ENEMYDEADFX, _enemy->getVEnemy()[i]->getX(), _enemy->getVEnemy()[i]->getY());
				_enemy->removeEnemy(i);
			}
			break;
		case ENEMY_BLORB:
			if (_enemy->getVEnemy()[i]->getStatus() == ENEMY_LEFT_DEAD ||
				_enemy->getVEnemy()[i]->getStatus() == ENEMY_RIGHT_DEAD)
			{
				_skill->Fire(SKILL_FIRE_CENTER, SKILL_ENEMYDEADFX, _enemy->getVEnemy()[i]->getX(), _enemy->getVEnemy()[i]->getY());
				_enemy->removeEnemy(i);
			}
			break;
		case ELEMY_DRAKE:
			if (_enemy->getVEnemy()[i]->getStatus() == ENEMY_LEFT_DEAD ||
				_enemy->getVEnemy()[i]->getStatus() == ENEMY_RIGHT_DEAD)
			{
				_skill->Fire(SKILL_FIRE_CENTER, SKILL_ENEMYDEADFX, _enemy->getVEnemy()[i]->getX(), _enemy->getVEnemy()[i]->getY());
				_enemy->removeEnemy(i);
			}
			break;
		case ENEMY_SKELETON:
			if (_enemy->getVEnemy()[i]->getStatus() == ENEMY_LEFT_DEAD ||
				_enemy->getVEnemy()[i]->getStatus() == ENEMY_RIGHT_DEAD)
			{
				_skill->Fire(SKILL_FIRE_CENTER, SKILL_ENEMYDEADFX, _enemy->getVEnemy()[i]->getX(), _enemy->getVEnemy()[i]->getY());
				_enemy->removeEnemy(i);
			}
			break;
		case ENEMY_DRAGON:
			if (_enemy->getVEnemy()[i]->getStatus() == ENEMY_LEFT_DEAD ||
				_enemy->getVEnemy()[i]->getStatus() == ENEMY_RIGHT_DEAD)
			{
				_skill->Fire(SKILL_FIRE_CENTER, SKILL_ENEMYDEADFX, _enemy->getVEnemy()[i]->getX(), _enemy->getVEnemy()[i]->getY());
				_enemy->removeEnemy(i);
			}
			break;
		case ENEMY_BLACKKNIGHT:
			if (_enemy->getVEnemy()[i]->getStatus() == ENEMY_LEFT_DEAD ||
				_enemy->getVEnemy()[i]->getStatus() == ENEMY_RIGHT_DEAD)
			{
				_skill->Fire(SKILL_FIRE_CENTER, SKILL_ENEMYDEADFX, _enemy->getVEnemy()[i]->getX(), _enemy->getVEnemy()[i]->getY());
				_enemy->removeEnemy(i);
			}
			break;
		}
	}

	//collisionPlayerMap();

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

	probeY = rc.bottom - 1;

	for (probeX = rc.left + 1; probeX != rc.right - 1; ++probeX)
	{
		while (!ThisPixelIsMazen(hdc, probeX, probeY))
		{
			--probeY;
		}
	}
	if (probeY == rc.bottom - 1) return;

	_player->setY(_player->getY() + (probeY - rc.bottom));
	//_player->setState(PLAYERSTATE_ONLAND);
}
