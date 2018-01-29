#pragma once
#include "gameNode.h"
class graphicUI : gameNode
{
protected:
	image * _uiBackImg;		//UI 바탕 이미지
public:
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);
	virtual void draw(HDC hdc);

	graphicUI();
	~graphicUI();
};

