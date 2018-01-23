// stdafx.h : 미리 컴파일된 헤더파일 : 자주 사용하는 것들을 미리 정의해 두는 곳
#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "soundManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "iniDataManager.h"
#include "sceneManager.h"
#include "keyAniManager.h"
#include "utils.h"
#include "collision.h"
#include "txtData.h"
#include "database.h"

using namespace std;
using namespace HEPTA_UTIL;

//=======================================================
// ## 윈도우 설정 디파인 ## 2017.11.08 ##
//=======================================================

#define WINNAME		(LPTSTR)TEXT("Hepta Window API")
#define WINSTARTX	2000	//윈도우 시작좌표 X
#define WINSTARTY	50		//윈도우 시작좌표 Y
#define WINSIZEX	800		//윈도우 가로크기
#define WINSIZEY	800		//윈도우 세로크기
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define KEYMANAGER		keyManager::getSingleton()
#define RND				randomFunction::getSingleton()
#define IMAGEMANAGER	imageManager::getSingleton()
#define SOUNDMANAGER	soundManager::getSingleton()
#define TIMEMANAGER		timeManager::getSingleton()
#define EFFECTMANAGER	effectManager::getSingleton()
#define SCENEMANAGER	sceneManager::getSingleton()
#define KEYANIMANAGER	keyAniManager::getSingleton()
#define TXTDATA			txtData::getSingleton()
#define INIDATA			iniDataManager::getSingleton()
#define DATABASE		database::getSingleton()

//=======================================================
// ## 매크로 ## 2017.11.15 ##
//=======================================================

#define SAFE_DELETE(p) { if(p) {delete(p); (p) = NULL; }}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL; }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p) = NULL;}}

//=======================================================
// ## 윈도우 설정 extern ## 2017.11.08 ##
//=======================================================

extern HINSTANCE	_hInstance;		//인스턴스 핸들
extern HWND			_hWnd;			//핸들
extern POINT		_ptMouse;
