#include "stdafx.h"
#include "TTUtils.h"


namespace 트윈테일쟝
{
	BOOL isCollisionEllRect(RECT& rcEll, RECT& rcRect)
	{
		RECT ell = rcEll;
		RECT rc = rcRect;

		FPOINT ptell = FPointMakeRect(ell);

		if (rc.left <= ptell.x && ptell.x <= rc.right
			|| rc.top <= ptell.y && ptell.y <= rc.bottom)
		{
			RECT temp;

			float radius = getRectWidth(ell) / 2;

			temp.left = rc.left - radius;
			temp.top = rc.top - radius;
			temp.right = rc.right + radius;
			temp.bottom = rc.bottom + radius;

			if (PtInRect(temp, ptell)) return TRUE;
		}

		//모서리조건
		if (PtInEll(ell, FPointMake(rc.left, rc.top))) return TRUE;

		if (PtInEll(ell, FPointMake(rc.left, rc.bottom))) return TRUE;

		if (PtInEll(ell, FPointMake(rc.right, rc.top))) return TRUE;

		if (PtInEll(ell, FPointMake(rc.right, rc.bottom))) return TRUE;

		return FALSE;
	}

	BOOL isCollisionEllEll(RECT & rcEll1, RECT & rcEll2)
	{
		float ell1Radius = getRectWidth(rcEll1) / 2;
		float ell2Radius = getRectWidth(rcEll2) / 2;

		FPOINT ell1pt = FPointMakeRect(rcEll1);
		FPOINT ell2pt = FPointMakeRect(rcEll2);

		if (ell1Radius + ell2Radius >= getDistanceFPoint(ell1pt, ell2pt))
		{
			return TRUE;
		}

		return FALSE;
	}

	float getDistancePoint(POINT ptStart, POINT ptEnd)
	{
		float x = ptEnd.x - ptStart.x;
		float y = ptEnd.y - ptStart.y;

		return sqrtf(x * x + y * y);
	}

	float getAnglePoint(POINT pt1, POINT pt2)
	{
		float x = pt2.x - pt1.x;
		float y = pt2.y - pt1.y;

		float angle = acosf(x / sqrtf(x * x + y * y));

		if (pt2.y > pt1.y)
		{
			angle = PI2 - angle;
			if (angle >= PI2) angle -= PI2;
		}

		return angle;
	}

	float getDistanceFPoint(FPOINT ptStart, FPOINT ptEnd)
	{
		float x = ptEnd.x - ptStart.x;
		float y = ptEnd.y - ptStart.y;

		return sqrtf(x * x + y * y);
	}

	float getAngleFPoint(FPOINT pt1, FPOINT pt2)
	{
		float x = pt2.x - pt1.x;
		float y = pt2.y - pt1.y;

		float angle = acosf(x / sqrtf(x * x + y * y));

		if (pt2.y > pt1.y)
		{
			angle = PI2 - angle;
			if (angle >= PI2) angle -= PI2;
		}

		return angle;
	}

	BOOL PtInEll(RECT rc, FPOINT pt)
	{
		FPOINT ptRc = FPointMakeRect(rc);

		if (getDistanceFPoint(ptRc, pt) <= getRectWidth(rc) / 2)
		{
			return TRUE;
		}

		return FALSE;
	}

	BOOL PtInEll(RECT rc, POINT pt)
	{
		POINT ptRc = PointMakeRect(rc);

		if (getDistancePoint(ptRc, pt) <= getRectWidth(rc) / 2)
		{
			return TRUE;
		}

		return FALSE;
	}

	BOOL PtInRect(RECT rc, FPOINT pt)
	{
		if (rc.left <= pt.x && pt.x <= rc.right
			&& rc.top <= pt.y && pt.y <= rc.bottom)
		{
			return TRUE;
		}
		return FALSE;
	}

	FPOINT FPointMake(float x, float y)
	{
		FPOINT pt = { x, y };

		return pt;
	}

	POINT PointMakeRect(RECT rc)
	{
		POINT pt = {
			rc.left,
			rc.top
		};

		return pt;
	}

	POINT PointMakeRectCenter(RECT rc)
	{
		POINT pt = {
			rc.right / 2 + rc.left / 2,
			rc.bottom / 2 + rc.top / 2
		};

		return pt;
	}

	FPOINT FPointMakeRect(RECT rc)
	{
		FPOINT pt = {
			rc.left,
			rc.top
		};

		return pt;
	}

	FPOINT FPointMakeRectCenter(RECT rc)
	{
		FPOINT pt = {
			rc.right / 2 + rc.left / 2,
			rc.bottom / 2 + rc.top / 2
		};

		return pt;
	}

	RECT RectMakePoint(FPOINT pt, float width, float height)
	{
		return {
			long(pt.x),
			long(pt.y),
			long(pt.x + width),
			long(pt.y + height) };
	}

	RECT RectMakePointCenter(POINT pt, float width, float height)
	{
		return {
			long(pt.x - width / 2),
			long(pt.y - height / 2),
			long(pt.x + width / 2),
			long(pt.y + height / 2) };
	}

	RECT RectMakePointCenter(FPOINT pt, float width, float height)
	{
		return {
			long(pt.x - width / 2),
			long(pt.y - height / 2),
			long(pt.x + width / 2),
			long(pt.y + height / 2) };
	}

	void RectangleMakeRect(HDC hdc, RECT rc)
	{
		Rectangle(hdc,
			rc.left,
			rc.top,
			rc.right,
			rc.bottom);
	}

	void EllipseMakeRect(HDC hdc, RECT rc)
	{
		Ellipse(hdc,
			rc.left,
			rc.top,
			rc.right,
			rc.bottom);
	}

	float getRectWidth(RECT rc)
	{
		return rc.right - rc.left;
	}

	float getRectHeight(RECT rc)
	{
		return rc.bottom - rc.top;
	}

	float getRectLeft(FPOINT pt, float width)
	{
		return pt.x - width / 2;
	}

	float getRectTop(FPOINT pt, float height)
	{
		return pt.y - height / 2;
	}

	FPOINT getRectLeftTop(FPOINT pt, float width, float height)
	{
		return {
			pt.x - width / 2,
			pt.y - height / 2 };
	}

	void PtMoveAngleSpeed(FPOINT& pt, float angle, float speed)
	{
		pt.x += +cosf(angle) * speed;
		pt.y += -sinf(angle) * speed;
		return;
	}

	void XYMoveAngleSpeed(float& x, float& y, float angle, float speed)
	{
		x += +cosf(angle) * speed;
		y += -sinf(angle) * speed;
	}

	void TTTextOut(int x, int y, string str, float num, BOOL backGround)
	{
		BOOL isfloat = (num != (int)num);

		if (isfloat)
		{
			int buffer = 4;
			{
				int ten = 1;
				while ((int)num > ten * 10 - 1)
				{
					ten *= 10;
					++buffer;
				}
			}

			char* str2 = new char[str.size() + 3 + buffer + 1];
			sprintf(str2, "%s : %.2f", str.c_str(), num);
			if (!backGround) SetBkMode((imageManager::getSingleton()->findImage("backbuffer")->getMemDC()), TRANSPARENT);
			TextOut((imageManager::getSingleton()->findImage("backbuffer")->getMemDC()), x, y, str2, strlen(str2));
		}
		else
		{
			int buffer = 1;
			{
				int ten = 1;
				while (num > ten * 10 - 1)
				{
					ten *= 10;
					++buffer;
				}
			}

			char* str2 = new char[str.size() + 3 + buffer + 1];
			sprintf(str2, "%s : %d", str.c_str(), (int)num);
			if (!backGround) SetBkMode(IMAGEMANAGER->findImage("backBuffer")->getMemDC(), TRANSPARENT);
			TextOut(IMAGEMANAGER->findImage("backBuffer")->getMemDC(), x, y, str2, strlen(str2));
		}

	}

	void TTTextOut(int x, int y, string str, RECT rc, BOOL backGround)
	{
		char* str2 = new char[str.size() + 1 + 7];
		char* str3 = new char[str.size() + 1 + 7];
		char* str4 = new char[str.size() + 1 + 7];
		char* str5 = new char[str.size() + 1 + 7];

		sprintf(str2, "%s%s", str.c_str(), ".left");
		sprintf(str3, "%s%s", str.c_str(), ".top");
		sprintf(str4, "%s%s", str.c_str(), ".right");
		sprintf(str5, "%s%s", str.c_str(), ".bottom");

		TTTextOut(x, y, str2, rc.left, backGround);
		TTTextOut(x, y+ 20, str3, rc.top, backGround);
		TTTextOut(x, y+ 40, str4, rc.right, backGround);
		TTTextOut(x, y+ 60, str5, rc.bottom, backGround);
	}


	void TTTextOut(string stri, float f)
	{
		cout << stri << " : " << f << endl;
	}

	void TTTextOut(string stri, int d)
	{
		cout << stri << " : " << d << endl;
	}

	BOOL ThisPixelIsMazen(HDC hdc, int x, int y, COLORREF cmpColor)
	{
		COLORREF color = GetPixel(hdc, x, y);

		int r2 = GetRValue(color);
		int g2 = GetGValue(color);
		int b2 = GetBValue(color);

		if (r2 == GetRValue(cmpColor) && g2 == GetGValue(cmpColor) && b2 == GetBValue(cmpColor))
		{
			return TRUE;
		}
		return FALSE;
	}

	BOOL ThisPixelIsMazen(COLORREF color, COLORREF cmpColor)
	{
		int r2 = GetRValue(color);
		int g2 = GetGValue(color);
		int b2 = GetBValue(color);

		if (r2 == GetRValue(cmpColor) && g2 == GetGValue(cmpColor) && b2 == GetBValue(cmpColor))
		{
			return TRUE;
		}
		return FALSE;
	}

	char* LPSTR_To_String(string str)
	{
		char* str2 = new char[str.size() + 1];

		strcpy(str2, str.c_str());

		return str2;
	}


	void strcat_ns(string& str, float f)
	{
		char* str2;
		bool isFloat = (f != (int)f);

		if(isFloat)
		{
			sprintf(str2, "%f", f);
		}
		else
		{
			itoa((int)f, str2, 10);
		}

		char* str3 = LPSTR_To_String(str);
		strcat_s(str3, strlen(str3) + strlen(str2) + 1, str2);

		str = str3;
	}

	void strcat_TT(char* str1, size_t buffer, const char* str2)
	{
		int len = strlen(str1);
		assert(buffer > (len + strlen(str2)));
		strcpy_s(str1 + len, buffer - len, str2);
	}

}
