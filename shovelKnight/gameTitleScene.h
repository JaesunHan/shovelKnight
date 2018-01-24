#pragma once

#include "optionMenu.h"
#include "gameNode.h"

#define MAXBTN	4

class gameTitleScene : public gameNode	
{
private : 
	image* _backgroundImg;			//백그라운드 이미지
	string _titleBGImgKeyStr;		//이미지 매니저에 등록할 타이틀 신 백그라운드 이미지 키값
	char* _titleBGImgFileName;		//타이틀 신 백그라운드 파일	
	image* _shovelImg;				//삽이미지
	string _shovelImgKeyStr;		//이미지 매니저에 등록할 삽 이미지 키값
	char* _shovelImgFileName;		//삽 이미지 파일 이름
	float _shovelX, _shovelY;		//삽 이미지를 출력할 위치(중점)
	int _shovelW, _shovelH;			//삽 이미지의 가로 세로 크기 -> 렉트 만들때 사용할 거임
		
	RECT _rcBtn[MAXBTN];			//게임 스타트, 공적, 옵션, 게임 종료 버튼 자리에 렉트를 깐다.
	int _shovelIdx;

	menuBase* _option;				//옵션
	menuBase* _soundset;			//사운드 조정

	bool _isOption;					//옵션을 선택하면 옵션메뉴 출력 ( true : 출력, false : 출력 안함)
	bool _isSound;					//사운드조절 선택하면 사운드 메뉴 출력 ( true : 출력, false : 출력 안함)

public:

	HRESULT init();
	void update();
	void release();
	void render();
	void draw();


	gameTitleScene();
	~gameTitleScene();
};

