#pragma once

#define MAPSIZEX 2982.f
#define MAPSIZEY 1687.f

#define SEC 72.f

#define SMALLX		WINSIZEX / MAPSIZEX 
#define SMALLY		WINSIZEY / MAPSIZEY 
#define BIGX		MAPSIZEX / WINSIZEX 
#define BIGY		MAPSIZEY / WINSIZEY

#define MAZEN COLORREF RGB(255,0,255)


namespace 트윈테일쟝
{
	typedef struct tagFloatPoint
	{
		float x;
		float y;
	} FPOINT;

	//원+네모 충돌
	BOOL isCollisionEllRect(RECT& rcEll, RECT& rcRect);

	//원+원 충돌
	BOOL isCollisionEllEll(RECT& rcEll1, RECT& rcEll2);

	//FPT끼리의 거리
	float getDistancePoint(FPOINT ptStart, FPOINT ptEnd);

	//FPT끼리의 각도
	float getAnglePoint(FPOINT pt1, FPOINT pt2);

	//FPT가 원안에 들어갔는지
	BOOL PtInEll(RECT rc, FPOINT pt);

	//FPT가 네모안에 들어갔는지
	BOOL PtInRc(RECT rc, FPOINT pt);

	//FPT 만드는 메크로
	FPOINT FPointMake(float x, float y);

	//렉트 left top에 FPT를 만든다
	FPOINT PointMakeRect(RECT rc);

	//렉트 중심에 FPT를 만든다
	FPOINT PointMakeRectCenter(RECT rc);

	//
	RECT RectMakePoint(FPOINT pt, float width, float height);

	RECT RectMakePointCenter(POINT pt, float width, float height);

	void RectangleMakeRect(HDC hdc, RECT rc);

	void EllipseMakeRect(HDC hdc, RECT rc);

	//렉트 크기 받아오기
	float getRectWidth(RECT rc);

	float getRectHeight(RECT rc);


	//Pt, width, height로 렉트 left top 받아오기

	//left
	float getRectLeft(FPOINT pt, float width);

	//top
	float getRectTop(FPOINT pt, float height);

	//FPOINT left top
	FPOINT getRectLeftTop(FPOINT pt, float width, float height);


	void PtMoveAngleSpeed(FPOINT& pt, float& angle, float& speed);

	void XYMoveAngleSpeed(float& x, float& y, float& angle, float& speed);

	// hdc, x좌표, y좌표, 표시할텍스트"", 표시할값, 배경표시여부		":"는 자동으로 써줌
	void TTTextOut(HDC hdc, int x, int y, char* stri, float f, bool backGround);

	//x, y 픽셀이 마젠인지?
	BOOL ThisPixelIsMazen(HDC hdc, int x, int y);

	RECT RectMakeSmall(RECT rc);

	inline RECT RectMakeBig(RECT rc);

	inline FPOINT PointMakeSmall(FPOINT pt);

	inline FPOINT PointMakeBig(FPOINT pt);
}

