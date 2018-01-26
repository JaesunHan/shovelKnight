#include "stdafx.h"
#include "pixelCollision.h"


pixelCollision::pixelCollision()
{

}
pixelCollision::~pixelCollision()
{
}

HRESULT pixelCollision::init(RECT &rc, float enmeyX, float enemyY, float speed)
{
	_rc = rc;

	_x = enmeyX;
	_y = enemyY;
	_speed = speed;

	_gravity = 0.9f;

	_isProbeY = false;
	_direction = false;
	_isProbe = false;

	return S_OK;
}

float pixelCollision::pixelCollisonY()
{
	_hdc = IMAGEMANAGER->findImage("bgMap")->getMemDC();

	if (_isProbe) return _y;


	for (int i = _rc.left; i <= _rc.right && !_isProbeY; i += (_rc.right - _rc.left) / 2)
	{
		for (int j = _y + (_rc.bottom - _rc.top) / 2 - 1; j <= _y + (_rc.bottom - _rc.top) / 2 + 1; ++j)
		{
			COLORREF color = GetPixel(_hdc, i, j);
			if (GetRValue(color) == 0 &&
				GetGValue(color) == 255 &&
				GetBValue(color) == 0)
			{
				_y = j - (_rc.bottom - _rc.top) / 2;
				_isProbeY = true;
				return _y;

				break;
			}
			else if (GetRValue(color) == 255 &&
					GetGValue(color) == 0 &&
					GetBValue(color) == 255)
			{
				_gravity += 0.4f;

				_y += _gravity;
				return _y;

				break;
			}
		}
	}

	return _y;
}

float pixelCollision::pixelCollisonX(bool direction)
{
	_hdc = IMAGEMANAGER->findImage("bgMap")->getMemDC();

	if (direction)
	{
		for (int i = _rc.top; i <= _rc.bottom; i += (_rc.right - _rc.left) / 4)
		{
			for (int j = _x + (_rc.right - _rc.left) / 2 - _speed; j <= _x + (_rc.right - _rc.left) / 2 + _speed; ++j)
			{
				COLORREF color = GetPixel(_hdc, j, i);

				if (GetRValue(color) == 0 &&
					GetGValue(color) == 255 &&
					GetBValue(color) == 0)
				{
					_x = j - (_rc.right - _rc.left) / 2;
					return _x;
					_direction = false;

					break;
				}
			}
		}
	}
	else
	{
		for (int i = _rc.top; i <= _rc.bottom; i += (_rc.right - _rc.left) / 4)
		{
			for (int j = _x - (_rc.right - _rc.left) / 2 - _speed; j <= _x - (_rc.right - _rc.left) / 2 + _speed; ++j)
			{
				COLORREF color = GetPixel(_hdc, j, i);

				if (GetRValue(color) == 0 &&
					GetGValue(color) == 255 &&
					GetBValue(color) == 0)
				{
					_x = j + (_rc.right - _rc.left) / 2;
					return _x;
					_direction = true;

					break;
				}
			}
		}
	}




	return _x;
}
