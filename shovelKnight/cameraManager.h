#pragma once
#include "singletonBase.h"
#include "image.h"
#include <vector>

struct tagMULTICAM
{
	int camNum;
	float destX;
	float destY;
	float cameraWidth;
	float focusX;
	float focusY;
	float width;
	float height;
};

class cameraManager : public singletonBase<cameraManager>
{
private:
	float _focusX;
	float _focusY;
	float _width;
	float _height;
	vector<tagMULTICAM> _vMulticam;
	vector<tagMULTICAM>::iterator _viMulticam;

public:
	HRESULT init(void);
	void release(void);

	void setSingleFocus(float x, float y);
	void setSingleFocus(float x, float y, float width);
	void setDoubleFocus(float x1, float y1, float x2, float y2, float blankRatio);
	void setMulticam(int camNum, float destX, float destY, float width);
	float getX(float x);
	float getY(float y);
	float getMousePointX(float mousePtX);
	float getMousePointY(float mousePtY);

	void renderBackground(HDC hdc, image* img);
	void renderBackground(HDC hdc, image* img, int camNum);
	void renderTile(HDC hdc, image* img, float destX, float destY, float sourX, float sourY, int tileWidth);
	void renderMap(HDC hdc, image* img);
	void renderMap(HDC hdc, image* img, int camNum);
	void renderObject(HDC hdc, image* img, float destX, float destY);
	void renderObject(HDC hdc, image* img, float destX, float destY, int sourX, int sourY, int width, int height);
	void renderObject(HDC hdc, image* img, int camNum, float destX, float destY);
	void frameRenderObject(HDC hdc, image* img, float destX, float destY, int currentFrameX, int currentFrameY);
	void aniRenderObject(HDC hdc, image* img, animation* ani, float destX, float destY);
	void aniRenderObject(HDC hdc, image* img, int camNum, animation* ani, float destX, float destY);

	cameraManager();
	~cameraManager();
};

