#pragma once
class npcBase
{
protected:
	image* _img;			// NPC 이미지
	string _imgKeyString;	//이미지 매니저에 등록할 이미지 키갑
	char* _imgFileName;		//이미지 파일 이름(경로 포함)
	animation* _anim;		//NPC 애니메이션
	float _x, _y;			//중점좌표
	int _width, _height;	//충돌 렉트를 만들 때 쓸 가로 세로 크기
	
	RECT _rc;				//충돌판정할 렉트

	bool _isCollision;		//플레이어와 충돌했는가? true : 그렇다, false : 아니다

public:
	npcBase();
	~npcBase();

	virtual HRESULT init(string imgKeyString, char* imgFileNmae, float x, float y, int totalWidth, int totalHeight, int frameXx, int frameY);
	virtual void release();
	virtual void update();
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
	
	//렉트 게터
	inline RECT getRect() { return _rc; }
	//==================================== End 게터 세터 작성하기===================================
};

