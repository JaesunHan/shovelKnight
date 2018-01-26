#include "stdafx.h"
#include "pixelCollision.h"


pixelCollision::pixelCollision()
{

}
pixelCollision::~pixelCollision()
{
}

HRESULT pixelCollision::init(string strKey, RECT &rc, float enmeyX, float enemyY, float speed)
{
	//픽셀충돌 이미지 추가
	IMAGEMANAGER->addImage("bgMap", ".//image//stage//backgroundMap.bmp", 1600, 240, false, RGB(0, 0, 0));


	_hdc = IMAGEMANAGER->findImage(strKey)->getMemDC();
	_rc = rc;

	_x = enmeyX;
	_y = enemyY;
	_speed = speed;

	_isProbeY = false;

	return S_OK;
}

float pixelCollision::pixelCollisonY()
{
	//float proveX, proveY;

	//proveY = _rc.bottom;

	//for (proveX = _rc.left; proveX != _rc.right; ++proveX)
	//{
	//	while (!ThisPixelIsMazen(_hdc, proveX, proveY))
	//	{
	//		--proveY;
	//	}
	//}

	//if (proveY == _rc.bottom) return NULL;
	//
	//return proveY;





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
				_y += 0.9f;
				return _y;
				break;
			}

		}
	}

	return _y;
}

float pixelCollision::pixelCollisonX()
{


	bool isProbe = false;


	for (int i = _rc.top; i <= _rc.bottom && !isProbe; i += (_rc.right - _rc.left) / 4)
	{
		for (int j = _x + (_rc.right - _rc.left) / 2 - _speed; j <= _x + (_rc.right - _rc.left) / 2 + _speed; ++j)
		{
			COLORREF color = GetPixel(_hdc, j, i);

			if (GetRValue(color) == 0 &&
				GetGValue(color) == 255 &&
				GetBValue(color) == 0)
			{
				_x = j - (_rc.right - _rc.left) / 2;
				isProbe = true;
				return _x;
				break;
			}
		}
	}

	return _x;
}