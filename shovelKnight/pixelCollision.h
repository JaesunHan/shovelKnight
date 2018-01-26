#pragma once
#include "gameNode.h"


class pixelCollision : public gameNode
{
private:
	HDC _hdc;
	RECT _rc;

	float _x, _y;
	bool _collisionGround;
	bool _directionChange;



public:
	pixelCollision();
	~pixelCollision();

	HRESULT init(RECT &rc, float enmeyX, float enemyY);
	void pixelCollisonX(RECT &rc, bool direction);
	void pixelCollisonY(RECT &rc);


	//================================================================================ 접근자 설정자
	inline bool getIsGround() { return _collisionGround; }
	inline void setIsGround(bool isGround) { _collisionGround = isGround; }

	inline bool getDirectionChange() { return _directionChange; }
	inline void setDirectionChange(bool direction) { _directionChange = direction; }

	inline float getProbeX() { return _x; }
	inline float getProbeY() { return _y; }
	//================================================================================
};

