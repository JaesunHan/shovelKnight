#pragma once
class menuBase
{
protected:
	image * _menuImg;		//메뉴 이미지
	string _imgKeyString;	//이미지 매니저에 등록할 이미지 키값
	char* _imgFileName;		//메뉴 이미지 파일 이름(경로 포함)
	float _x, _y;			//메뉴 를 출력할 중앙좌표
	int _width, _height;	//메뉴의 가로세로 크기
	
public:
	virtual HRESULT init();
	virtual HRESULT init(string imgKeyString, char* imgFileNmae, float x, float y, int imgWidth, int imgHeight);
	virtual void update();
	virtual void release();
	virtual void render();
	virtual void draw(HDC hdc);

	menuBase();
	~menuBase();
};

