#include "stdafx.h"
#include "movement.h"


movement::movement()
{
}


movement::~movement()
{

}


HRESULT movement::init()
{
	return S_OK;
}
void movement::release()
{

}
void movement::update()	
{

	if (_isJumping) jump();

}
void movement::render()	
{

}

void movement::jump(float* x, float* y, float jumpPower, float gravity)	
{
	_x = x;
	_y = y;
	_jumpPower = jumpPower;
	_gravity = gravity;


}
void movement::backStep(float* x, float* y, float speed, float distance)
{

}