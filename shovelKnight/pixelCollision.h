#pragma once
#include "gameNode.h"


class pixelCollision : public gameNode
{
private:
	HDC _hdc;
	RECT _rc;

	float _x, _y;
	float _speed;
	bool _isProbeY;

public:
	pixelCollision();
	~pixelCollision();

	HRESULT init(string strKey, RECT &rc, float enmeyX, float enemyY, float speed);
	float pixelCollisonX();
	float pixelCollisonY();
	
};

