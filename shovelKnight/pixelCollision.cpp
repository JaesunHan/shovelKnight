#include "stdafx.h"
#include "pixelCollision.h"


pixelCollision::pixelCollision()
{

}
pixelCollision::~pixelCollision()
{
}

HRESULT pixelCollision::init(RECT &rc, float enmeyX, float enemyY)
{
	_rc = rc;

	_x = enmeyX;
	_y = enemyY;

	_collisionGround = false;


	return S_OK;
}
void pixelCollision::pixelCollisonY()
{
	_hdc = IMAGEMANAGER->findImage("bgMap")->getMemDC();


	for (int i = _rc.left; i <= _rc.right; i += (_rc.right - _rc.left) / 2)
	{
		for (int j = _y + (_rc.bottom - _rc.top) / 2 - 1; j <= _y + (_rc.bottom - _rc.top) / 2 + 1; ++j)
		{
			COLORREF color = GetPixel(_hdc, i, j);

			//¹Ù´ÚÃæµ¹
			if (GetRValue(color) == 0 &&
				GetGValue(color) == 255 &&
				GetBValue(color) == 0)
			{
				_y = j - (_rc.bottom - _rc.top) / 2;

				_collisionGround = true;
				break;
			}

			//ÀÚÀ¯³«ÇÏ
			if (GetRValue(color) == 255 &&
				GetGValue(color) == 0 &&
				GetBValue(color) == 255)
			{
				_collisionGround = false;
			}

		}
	}

}

bool pixelCollision::pixelCollisonX()
{
	_hdc = IMAGEMANAGER->findImage("bgMap")->getMemDC();


		for (int i = _rc.top; i <= _rc.bottom; i += (_rc.right - _rc.left) / 4)
		{
			for (int j = _x + (_rc.right - _rc.left) / 2; j <= _x + (_rc.right - _rc.left) / 2; ++j)
			{
				COLORREF color = GetPixel(_hdc, j, i);

				if (GetRValue(color) == 0 &&
					GetGValue(color) == 255 &&
					GetBValue(color) == 0)
				{
					_x = j - (_rc.right - _rc.left) / 2;
					return true;

					break;
				}
			}
		}


	return false;
}
