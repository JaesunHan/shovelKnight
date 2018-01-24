#pragma once
#define MAXBTN	4
#include "optionMenu.h"
class gameTitleScene
{
private : 
	image* _bachgroundImg;			//백그라운드 이미지
	image* _shovelImg;				//삽이미지
	float _shovelX, _shovelY;		//삽 이미지를 출력할 위치
		
	RECT _rcBtn[MAXBTN];			//게임 스타트, 공적, 옵션, 게임 종료 버튼 자리에 렉트를 깐다.

	menuBase* _option;				//옵션
	menuBase* _soundset;			//사운드 조정




public:
	gameTitleScene();
	~gameTitleScene();
};

