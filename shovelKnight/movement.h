#pragma once
#include "gameNode.h"
class movement : public gameNode
{
private : 
	float _jumpPower;
	float _gravity;
	float* _x;
	float* _y;
	bool _isJumping;

public:
	movement();
	~movement();

	HRESULT init();
	void release();
	void update();
	void render();

	void jump(float* x, float* y, float jumpPower, float gravity);
	void backStep(float* x, float* y, float speed, float distance);

};

