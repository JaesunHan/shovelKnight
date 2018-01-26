#pragma once
#include "gameNode.h"

class jump : public gameNode
{
private:
	float _jumpPower;
	float _gravity;

	//¶Û¶§ ÁÂÇ¥
	float* _x;
	float* _y;

	//Ã³À½ ¶Ù¾úÀ»‹š À§Ä¡
	float _startX;
	float _startY;

	bool _isJumping;

public:
	jump();
	~jump();

	HRESULT init();
	void release();
	void update();
	void render();

	void jumping(float* x, float* y, float power, float gravity);

	bool getIsJumping(void) { return _isJumping; }

};