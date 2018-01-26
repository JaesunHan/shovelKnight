#include "stdafx.h"
#include "jump.h"


jump::jump()
{
}
jump::~jump()
{
}



HRESULT jump::init()
{
	_isJumping = _jumpPower = _gravity = 0;

	return S_OK;
}

void jump::release()
{

}

void jump::update()
{
	//신호가 들어오지 않았을땐 실행되지 않게 한다
	if (!_isJumping) return;

	*_y -= _jumpPower;
	_jumpPower -= _gravity;

	//일단은 처음 뛴 위치보다 내려가면~
	if (_startY < *_y)
	{
		_isJumping = false;
		*_y = _startY;
	}
}

void jump::render()
{

}

//외부에서 신호를 줄 함수
void jump::jumping(float* x, float* y, float power, float gravity)
{
	//점프하고 있으면 건드리지 말 것
	if (_isJumping) return;

	_isJumping = true;

	_x = x;
	_y = y;

	_startX = *x;
	_startY = *y;

	_gravity = gravity;
	_jumpPower = power;
}
