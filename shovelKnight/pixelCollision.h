#pragma once
#include "gameNode.h"


class pixelCollision : public gameNode
{
private:
	HDC _hdc;
	RECT _rc;

	float _x, _y;
	bool _collisionGround;




public:
	pixelCollision();
	~pixelCollision();

	HRESULT init(RECT &rc, float enmeyX, float enemyY);
	bool pixelCollisonX();
	void pixelCollisonY();


	//접근자 설정자
	inline bool getIsGround() { return _collisionGround; }
	inline void setIsGround(bool isGround) { _collisionGround = isGround; }
};

