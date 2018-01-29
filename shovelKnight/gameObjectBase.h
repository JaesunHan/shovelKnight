#pragma once
#include "gameNode.h"

class gameObjectBase:public gameNode
{
protected:
	float _x, _y;			//좌표(좌상)
	int _dur;				//내구도
	bool _isDelete;			//지워주는지
	int _currentFrameX;		//프레임
	int _currentFrameY;		//
	bool _isOn;				//체크포인트 켜졌는지
	bool _isCheck;			//체크 완료
	image* _image;			//이미지
	RECT _rc;				//
	COLORREF _color;		//픽셀박스 컬러

public:
	gameObjectBase();
	~gameObjectBase();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void settingObj(float x, float y,int dur, bool isDelete, COLORREF color);
	virtual void durAct();
	virtual void collisionBox();

	inline bool getDelete(){ return _isDelete; }

	inline int getDur() { return _dur; }
	inline void setDur(int decreaseDur) { _dur -= decreaseDur; }

	inline float getX() { return _x; }
	inline float getY() { return _y; }
};

