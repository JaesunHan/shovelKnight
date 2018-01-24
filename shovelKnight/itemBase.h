#pragma once
class itemBase
{
protected:
	image * _img;				//아이템 이미지
	string _imgKeyString;		//이미지매니저에 등록할 이미지 키값
	char* _imgFileName;			//아이템 이미지 파일(경로 포함)

	float _x, _y;				//중점 좌표
	float _jumpPower;			//아이템이 드랍될때 위로 뛰어올랐다가 떨어짐
	float _itemGravity;			//그렇다면 중력이 적용되어야 게찌요?
	int _width, _height;		//아이템 충돌 렉트 그릴 때 쓸 가로세로 크기

	RECT _rc;					//아이템 충돌 렉트

public:
	itemBase();
	~itemBase();

	virtual HRESULT init(string imgKeyString, char* imgFileName, float x, float y, int totalWidth, int totalHeight, int frameX, int frameY);
	virtual void update();
	virtual void release();
	virtual void render();
	virtual void draw();

	//==================================== Start 게터 세터 작성하기===================================
	//중점X 게터 세터
	inline float getX() { return _x; }		inline void setX(float x) { _x = x; }
	//중점Y 게터 세터
	inline float getY() { return _y; }		inline void setY(float y) { _y = y; }
	//가로크기 게터 세터
	inline int getWidth() { return _width; }	inline void setWidth(int w) { _width = w; }
	//세로크기 게터 세터
	inline int getHeight() { return _height; }	inline void setHeight(int h) { _height = h; }
	//점프파워 게터 세터
	inline float getJumpPower() { return _jumpPower; }	inline void setJumpPower(float jp) { _jumpPower = jp; }

	//렉트 게터
	inline RECT getRect() { return _rc; }
	//==================================== End 게터 세터 작성하기===================================
};

