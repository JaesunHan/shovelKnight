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
	_currentStage = 0;

	return S_OK;
}


void pixelCollision::pixelCollisonY(RECT &rc)
{
	_rc = rc;

	//픽셀충돌 hdc영역 설정
	switch (_currentStage)
	{
		case 0: //추후 이름변경 예정

			_hdc = IMAGEMANAGER->findImage("bgMap")->getMemDC();

		break;
		case 1: 

			

		break;
		case 2:



		break;
	}


	for (int i = _rc.left; i <= _rc.right; i += (_rc.right - _rc.left) / 2)
	{
		for (int j = _rc.bottom - 1; j <= _rc.bottom + 1; ++j)
		{
			COLORREF color = GetPixel(_hdc, i, j);

			//바닥충돌
			if (GetRValue(color) == 0 &&
				GetGValue(color) == 255 &&
				GetBValue(color) == 0)
			{
				_y = j - (_rc.bottom - _rc.top) / 2;

				_collisionGround = true;
				break;
			}

			//자유낙하
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

	if (direction)  //오른쪽
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
	else  //왼쪽
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
