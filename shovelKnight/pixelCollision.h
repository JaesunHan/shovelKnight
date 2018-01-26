#pragma once
#include "gameNode.h"


class pixelCollision : public gameNode
{
private:
	HDC _hdc;
	RECT _rc;

	float _x, _y;
	float _gravity;
	float _speed;

	bool _isProbe;
	bool _isProbeX;
	bool _isProbeY;
	bool _direction;


public:
	pixelCollision();
	~pixelCollision();

	HRESULT init(string strKey, RECT &rc, float enmeyX, float enemyY, float speed);
	float pixelCollisonX(bool direction);
	float pixelCollisonY();

	bool pixelDirection() { return _direction; }
	
};

