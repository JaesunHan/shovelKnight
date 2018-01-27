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
	_directionChange = false;

	return S_OK;
}


void pixelCollision::pixelCollisonY(RECT &rc)
{
	_rc = rc;

	_hdc = IMAGEMANAGER->findImage("bgMap")->getMemDC();


	for (int i = _rc.left; i <= _rc.right; i += (_rc.right - _rc.left) / 2)
	{
		for (int j = _rc.bottom - 1; j <= _rc.bottom + 1; ++j)
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

void pixelCollision::pixelCollisonX(RECT &rc, bool direction)
{
	_rc = rc;

	_hdc = IMAGEMANAGER->findImage("bgMap")->getMemDC();

	if (direction)  //¿À¸¥ÂÊ
	{
		for (int i = _rc.top; i <= _rc.bottom; i += (_rc.right - _rc.left) / 4)
		{
			for (int j = _rc.right - 1; j <= _rc.right + 1; ++j)
			{
				COLORREF color = GetPixel(_hdc, j, i);

				if (GetRValue(color) == 0 &&
					GetGValue(color) == 255 &&
					GetBValue(color) == 0)
				{
					_x = j - (_rc.right - _rc.left) / 2;

					_directionChange = true;
					break;
				}
			}
		}
	}
	else  //¿ÞÂÊ
	{
		for (int i = _rc.top; i <= _rc.bottom; i += (_rc.right - _rc.left) / 4)
		{
			for (int j = _rc.left - 1; j <= _rc.left + 1; ++j)
			{
				COLORREF color = GetPixel(_hdc, j, i);

				if (GetRValue(color) == 0 &&
					GetGValue(color) == 255 &&
					GetBValue(color) == 0)
				{
					_x = j + (_rc.right - _rc.left) / 2;

					_directionChange = true;
					break;
				}
			}
		}
	}




}
