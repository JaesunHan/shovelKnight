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
	_playerMeetNPC = false;

	return S_OK;
}

void gameCollision::release()
{
}

void gameCollision::update()
{
	enemyDead();
	enemyDetectPlayer();
	if(KEYMANAGER->isOnceKeyDown(0x31) || _playerMeetNPC) PlayerMeetNPC();
	PlayerAndEnemy();
	
	//collisionPlayerMapRight();
	//collisionPlayerMapLeft();
	//collisionPlayerMapDown(); 
	//collisionPlayerMapUp();
	//collisionPlayerInAir();

	//플레이어와 스킬의 충돌	 
	//적과 스킬의 충돌
	//플레이어와 item의 충돌

}

void gameCollision::render()
{

	RECT rc = _player->getPlayerRC();

	for (int i = 0; i < _store->getVNpc().size(); ++i)
	{
		if (_store->getVNpc()[i]->getNpcType() != MAGICGIRL) continue;

		RECT rc2 = _store->getVNpc()[i]->getRect();

		TTTextOut(200, 200, "", rc2);
	}
	TTTextOut(300, 200, "", rc);
	for (int i = 0; i != _item->getVSkill().size(); ++i)
	{
		TTTextOut(300, 0, "", _item->getVSkill()[i]->getAdd().x);
		TTTextOut(300, 20, "", _item->getVSkill()[i]->getAdd().y);
		TTTextOut(300, 40, "", _item->getVSkill()[i]->getGravity());
	}
}

void gameCollision::enemyDead()
{
	//몬스터에 따라 죽는게 다르므로 스위치로 나눔
	for (int i = 0; i != _enemy->getVEnemy().size(); ++i)
	{
		switch (_enemy->getVEnemy()[i]->getEnemyType())
		{
		case ENEMY_BEETO:
			if (_enemy->getVEnemy()[i]->getStatus() == ENEMY_LEFT_DEAD ||
				_enemy->getVEnemy()[i]->getStatus() == ENEMY_RIGHT_DEAD)
			{
				_skill->Fire(SKILL_FIRE_CENTER, SKILL_ENEMYDEADFX, _enemy->getVEnemy()[i]->getX(), _enemy->getVEnemy()[i]->getY());
			}
			break;
		case ENEMY_BLORB:
			if (_enemy->getVEnemy()[i]->getStatus() == ENEMY_LEFT_DEAD ||
				_enemy->getVEnemy()[i]->getStatus() == ENEMY_RIGHT_DEAD)
			{
				_skill->Fire(SKILL_FIRE_CENTER, SKILL_ENEMYDEADFX, _enemy->getVEnemy()[i]->getX(), _enemy->getVEnemy()[i]->getY());
			}
			break;
		case ELEMY_DRAKE:
			if (_enemy->getVEnemy()[i]->getStatus() == ENEMY_LEFT_DEAD ||
				_enemy->getVEnemy()[i]->getStatus() == ENEMY_RIGHT_DEAD)
			{
				_skill->Fire(SKILL_FIRE_CENTER, SKILL_ENEMYDEADFX, _enemy->getVEnemy()[i]->getX(), _enemy->getVEnemy()[i]->getY());
			}
			break;
		case ENEMY_SKELETON:
			if (_enemy->getVEnemy()[i]->getStatus() == ENEMY_LEFT_DEAD ||
				_enemy->getVEnemy()[i]->getStatus() == ENEMY_RIGHT_DEAD)
			{
				_skill->Fire(SKILL_FIRE_CENTER, SKILL_ENEMYDEADFX, _enemy->getVEnemy()[i]->getX(), _enemy->getVEnemy()[i]->getY());
			}
			break;
		case ENEMY_DRAGON:
			if (_enemy->getVEnemy()[i]->getStatus() == ENEMY_LEFT_DEAD ||
				_enemy->getVEnemy()[i]->getStatus() == ENEMY_RIGHT_DEAD)
			{
				_skill->Fire(SKILL_FIRE_CENTER, SKILL_ENEMYDEADFX, _enemy->getVEnemy()[i]->getX(), _enemy->getVEnemy()[i]->getY());
			}
			break;
		case ENEMY_BLACKKNIGHT:
			if (_enemy->getVEnemy()[i]->getStatus() == ENEMY_LEFT_DEAD ||
				_enemy->getVEnemy()[i]->getStatus() == ENEMY_RIGHT_DEAD)
			{
				_skill->Fire(SKILL_FIRE_CENTER, SKILL_ENEMYDEADFX, _enemy->getVEnemy()[i]->getX(), _enemy->getVEnemy()[i]->getY());
			}
			break;
		}
	}
}

void gameCollision::enemyDetectPlayer()
{
	for (int i = 0; i != _enemy->getVEnemy().size(); ++i)
	{
		_enemy->getVEnemy()[i]->getPlayerX(_player->getX());
		_enemy->getVEnemy()[i]->getPlayerStatus(_player->getPlayerAction());
	}
}

void gameCollision::PlayerMeetNPC()
{
	RECT temp;
	for (int i = 0; i != _store->getVNpc().size(); ++i)
	{





		_store->getVNpc()[i]->setSkillUnlockLv(_player->getSkillUnlockLv());
		_store->getVNpc()[i]->setMoney(_player->getMoney());
		_player->setMoney(_store->getVNpc()[i]->getMinusMoney());
		_player->setSkillUnlockLv(_store->getVNpc()[i]->getSkillUnlockLv());

		_player->setMaxHP(_store->getVNpc()[i]->getMaxHp());
		_store->getVNpc()[i]->setMaxHp(_player->getMaxHP());
		






		if (IntersectRect(&temp, &_player->getPlayerRC(), &_store->getVNpc()[i]->getRect()))

		{
			_store->getVNpc()[i]->isCollision(true);
			_playerMeetNPC = true;
		}
		else
		{
			_store->getVNpc()[i]->isCollision(false);
			_playerMeetNPC = false;
		}
	}
}

void gameCollision::PlayerAndEnemy()
{
	for (int i = 0; i != _enemy->getVEnemy().size(); ++i)
	{
		RECT temp;

		if (IntersectRect(&temp, &_player->getPlayerRC(), &_enemy->getVEnemy()[i]->getRect()))
		{
			_player->setDamagePlayer();
			_player->setPlayerReaction();
		}
		if (IntersectRect(&temp, &_player->getAttackRC(), &_enemy->getVEnemy()[i]->getRect()))
		{
			_enemy->getVEnemy()[i]->setEnemyDamage();
			_player->setPlayerReaction();
		}
	}
}

//void gameCollision::collisionPlayerMapDown()
//{
//	RECT rc = _player->getPlayerRc();
//
//	int probeX, probeY;
//
//	probeY = rc.bottom;
//
//	for (probeX = rc.left + 1; probeX != rc.right - 1; +//+probeX)
//	{
//		while (ThisPixelIsMazen(BGMAP, probeX, probeY, RGB//(0,255,0)))
//		{
//			--probeY;
//			if (probeY < 0) return;
//		}
//	}
//	if (probeY == rc.bottom) return;
//
//	_player->setY(_player->getY() + (probeY - rc.bottom));
//	_player->setState(PLAYERSTATE_ONLAND);
//	_player->setJumpPower(0);
//}
//
//void gameCollision::collisionPlayerMapUp()
//{
//	RECT rc = _player->getPlayerRc();
//
//	int probeX, probeY;
//
//	probeY = rc.top + _player->getJumpPower();
//
//	for (probeX = rc.left + 1; probeX != rc.right-1 ; +//+probeX)
//	{
//		while (ThisPixelIsMazen(BGMAP, probeX, probeY, RGB//(0, 255, 0)))
//		{
//			++probeY;
//			if (probeY > WINSIZEY) return;
//		}
//	}
//	if (probeY == rc.top + _player->getJumpPower()) return;
//
//	_player->setY(_player->getY() + (probeY - rc.top ));
//	_player->setJumpPower(0);
//}
//
//void gameCollision::collisionPlayerMapRight()
//{
//	RECT rc = _player->getPlayerRc();
//
//	int probeX, probeY;
//
//	probeX = rc.right;
//
//	for (probeY = rc.top+1 ; probeY != rc.bottom-1; +//+probeY)
//	{
//		while (ThisPixelIsMazen(BGMAP, probeX, probeY, RGB//(0, 255, 0)))
//		{
//			--probeX;
//			if (probeX < 0) return;
//		}
//	}
//	if (probeX == rc.right) return;
//
//	_player->setX(_player->getX() + (probeX - rc.right ));
//}
//
//void gameCollision::collisionPlayerMapLeft()
//{
//	RECT rc = _player->getPlayerRc();
//
//	int probeX, probeY;
//
//	probeX = rc.left;
//
//	for (probeY = rc.top+1; probeY != rc.bottom - 1; +//+probeY)
//	{
//		while (ThisPixelIsMazen(BGMAP, probeX, probeY, RGB//(0, 255, 0)))
//		{
//			++probeX;
//			if (probeX > WINSIZEX) return;
//		}
//	}
//	if (probeX == rc.left) return;
//
//	_player->setX(_player->getX() + (probeX - rc.left ));
//}
//
//void gameCollision::collisionPlayerInAir()
//{
//
//	RECT rc = _player->getPlayerRc();
//
//	int probeX, probeY;
//
//	probeX = rc.left + 1;
//	probeY = rc.top;
//
//	if (collisionPlayerInAir2(probeX, probeY)) return;
//
//	while (probeX != rc.right)
//	{
//		++probeX;
//		if (collisionPlayerInAir2(probeX, probeY)) return;
//	}
//
//	while (probeY != rc.bottom)
//	{
//		++probeY;
//		if (collisionPlayerInAir2(probeX, probeY)) return;
//	}
//	while (probeX != rc.left)
//	{
//		--probeX;
//		if (collisionPlayerInAir2(probeX, probeY)) return;
//	}
//
//	while (probeY != rc.top)
//	{
//		--probeY;
//		if (collisionPlayerInAir2(probeX, probeY)) return;
//	}
//
//	return;
//}
//
//BOOL gameCollision::collisionPlayerInAir2(int probeX, /int /probeY)
//{
//	if (ThisPixelIsMazen(BGMAP, probeX, probeY, RGB(0, /255,/ 0)))
//	{
//		_player->setState(PLAYERSTATE_INAIR);
//		return TRUE;
//	}
//	return FALSE;
//}
