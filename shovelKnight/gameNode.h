#pragma once
#include "image.h"

//백버퍼라는 빈 비트맵 이미지를 하나 설정해둔다
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;		//매니저등을 초기화 할 것이냐

public:
	virtual HRESULT init(void);		//초기화 함수
	virtual HRESULT init(bool managerInit);
	virtual void release(void);		//메모리 관련 해제
	virtual void update(void);		//업데이트(연산)
	virtual void render(void);	//그려주는 함수

	//interface == 순수가상함수 == 추상성, 확장성
	//virtual void move(void) = 0; 
	//virtual void jump(void) = 0;
	//virtual void attack(void) = 0;

	image* getBackBuffer(void) { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }


	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

