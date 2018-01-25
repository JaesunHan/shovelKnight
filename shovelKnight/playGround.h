#pragma once
#include "gameNode.h"
#include "gameTitleScene.h"
#include "gameMenuScene.h"

class playGround : public gameNode
{
private:
	gameTitleScene * _GTS;
	string _gtsStr;
	gameMenuScene * _GMS;
	string _gmsStr;
	

public:
	virtual HRESULT init(void);		//초기화 함수
	virtual void release(void);		//메모리 관련 해제
	virtual void update(void);		//업데이트(연산)
	virtual void render(void);		//그려주는 함수



	playGround();
	~playGround();
};

