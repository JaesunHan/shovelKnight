#pragma once
#include "gameNode.h"

class gameMenuScene : public gameNode
{
private:
	string _sceneName;				//씬매니저에 등록할 씬 이름

	image* _backgroundImg;			//백그라운드 이미지
	string _menuBGImgKeyStr;		//이미지 매니저에 등록할 메뉴씬 백그라운드 이미지 키값
	char* _menuBGImgFileName;		//메뉴 씬 백그라운드 파일


public:

	HRESULT init();
	void update();
	void release();
	void render();
	void draw();
	


	gameMenuScene();
	~gameMenuScene();
};

