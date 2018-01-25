#include "stdafx.h"
#include "TTUtils.h"


namespace 트윈테일쟝
{
	BOOL isCollisionEllRect(RECT& rcEll, RECT& rcRect)
	{
		RECT ell = rcEll;
		RECT rc = rcRect;

		FPOINT ptell = PointMakeRect(ell);

		if (rc.left <= ptell.x && ptell.x <= rc.right
			|| rc.top <= ptell.y && ptell.y <= rc.bottom)
		{
			RECT temp;

			float radius = getRectWidth(ell) / 2;

			temp.left = rc.left - radius;
			temp.top = rc.top - radius;
			temp.right = rc.right + radius;
			temp.bottom = rc.bottom + radius;

			if (PtInRc(temp, ptell)) return TRUE;
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

		FPOINT ell1pt = PointMakeRect(rcEll1);
		FPOINT ell2pt = PointMakeRect(rcEll2);

		if (ell1Radius + ell2Radius >= getDistancePoint(ell1pt, ell2pt))
		{
			return TRUE;
		}

		return FALSE;
	}

	float getDistancePoint(FPOINT ptStart, FPOINT ptEnd)
	{
		float x = ptEnd.x - ptStart.x;
		float y = ptEnd.y - ptStart.y;

		return sqrtf(x * x + y * y);
	}

	float getAnglePoint(FPOINT pt1, FPOINT pt2)
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
		FPOINT ptRc = PointMakeRect(rc);

		if (getDistancePoint(ptRc, pt) <= getRectWidth(rc) / 2)
		{
			return TRUE;
		}

		return FALSE;
	}

	BOOL PtInRc(RECT rc, FPOINT pt)
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

	FPOINT PointMakeRect(RECT rc)
	{
		FPOINT pt = {
			rc.left,
			rc.top
		};

		return pt;
	}

	FPOINT PointMakeRectCenter(RECT rc)
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

	void PtMoveAngleSpeed(FPOINT& pt, float& angle, float& speed)
	{
		pt.x += +cosf(angle) * speed;
		pt.y += -sinf(angle) * speed;
		return;
	}

	void XYMoveAngleSpeed(float& x, float& y, float& angle, float& speed)
	{
		x += +cosf(angle) * speed;
		y += -sinf(angle) * speed;
	}

	void TTTextOut(HDC hdc, int x, int y, char* stri, float f, bool backGround)
	{
		int buffer = 3 + 4 + 1;	//" : ", "0.00", ""
		int unit = 10;
		while (f / (float)unit > 1)
		{
			buffer++;
			unit *= 10;
		}
		//진짜 float인지는 모르고 소수점 있으면 float으로 인식
		bool isfloat = (f - (int)f != 0);
		if (isfloat)
		{
			char* str = new char[buffer + strlen(stri)];
			sprintf(str, "%s : %.2f", stri, f);
			//SetTextColor(hdc, COLORREF)
			if (!backGround) SetBkMode(hdc, TRANSPARENT);
			TextOut(hdc, x, y, str, strlen(str));
		}
		else
		{
			char* str = new char[buffer - 3 + strlen(stri)];
			sprintf(str, "%s : %d", stri, f);
			if (!backGround) SetBkMode(hdc, TRANSPARENT);
			TextOut(hdc, x, y, str, strlen(str));
		}
	}

	BOOL ThisPixelIsMazen(HDC hdc, int x, int y)
	{
		COLORREF color = GetPixel(hdc, x, y);

		int r2 = GetRValue(color);
		int g2 = GetGValue(color);
		int b2 = GetBValue(color);

		if (r2 == 255 && g2 == 0 && b2 == 255)
		{
			return TRUE;
		}
		return FALSE;
	}

	RECT RectMakeSmall(RECT rc)
	{
		return {
			long(rc.left * SMALLX),
			long(rc.top * SMALLY),
			long(rc.right * SMALLX),
			long(rc.bottom * SMALLY) };
	}

	RECT RectMakeBig(RECT rc)
	{
		return {
			long(rc.left * BIGX),
			long(rc.top * BIGY),
			long(rc.right * BIGX),
			long(rc.bottom * BIGY) };
	}

	FPOINT PointMakeSmall(FPOINT pt)
	{
		return {
			pt.x * SMALLX,
			pt.y * SMALLY };
	}

	FPOINT PointMakeBig(FPOINT pt)
	{
		return {
			pt.x * BIGX,
			pt.y * BIGY };
	}
}
