#pragma once
#include "graphicUI.h"

class gamePlayUI : public graphicUI
{
private:
	int _playerIdx;

	int _gold;
	int _mana;
	int _life;
	int _maxLife;
	int _boss;

	image* _emptyHP;
	image* _fullHP;
	image* _halfHP;

public:

	HRESULT init();
	void update();
	void release();
	//	void render();
	void draw(HDC hdc);

	//================== Start 씬에서 UI 로 변경된 정보를 보낼 때 세터를 호출한다 ================
	void setPlayerInfo(int* idx);
	void setPlayerIdx(int* idx) { _playerIdx = *idx; }	int getPlayerIdx() { return _playerIdx; }
	void setGold(int gold) { _gold = gold; }			int getGold() { return _gold; }
	void setMana(int mana) { _mana = mana; }			int getMana() { return _mana; }
	void setLife(int life) { _life = life; }			int getLife() { return _life; }
	void setMaxLife(int maxlife) { _maxLife = maxlife; }int getMaxLife() { return _maxLife; }
	void setBoss(int boss) { _boss = boss; }			int getBoss() { return _boss; }
	//================== End 씬에서 UI 로 변경된 정보를 보낼 때 세터를 호출한다 ==================

	gamePlayUI();
	~gamePlayUI();
};