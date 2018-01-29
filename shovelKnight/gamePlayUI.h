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
	void setPlayerIdx(int* idx) { _playerIdx = *idx; }
	void setPlayerInfo(int* idx);
	//void setGold(int gold) { _gold = gold; }
	//void setItem(int item) { _item = item; }
	//void setLife(int life) { _life = life; }
	//void setBoss(int boss) { _boss = boss; }
	//================== End 씬에서 UI 로 변경된 정보를 보낼 때 세터를 호출한다 ==================

	gamePlayUI();
	~gamePlayUI();
};

