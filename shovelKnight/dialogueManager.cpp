#include "stdafx.h"
#include "dialogueManager.h"


dialogueManager::dialogueManager()
{
}


dialogueManager::~dialogueManager()
{
}

HRESULT dialogueManager::init(float dt)
{
	
	_dialogueTime = dt;		//이 시간이 문자 출력되는 시간 간격이다

	_elapsedTime = 0;
	//_language = lan;
	ZeroMemory(_scriptStr, sizeof(_scriptStr));

	return S_OK;
}

void dialogueManager::release()
{

}
void dialogueManager::update()
{
	//스크립트가 없으면 그냥 업데이트 함수를 종료
	if (_scriptStr == "")
	{
		return;
	}

	_time = TIMEMANAGER->getWorldTime();

	if ((int)(_time*100) % _dialogueTime == 0)
	{
		
		_cnt++;
	}
}
void dialogueManager::render(HDC hdc, float x, float y, int width , int height)
{
	if (_scriptStr == "")
	{
		return;
	}
	_scriptwindow->render(hdc, x, y);
	SetTextColor(hdc, RGB(_r, _g, _b));
	RECT rcScriptArea = { x+150, y, width, height };
	if (_cnt >= strlen(_scriptStr))	_cnt = strlen(_scriptStr);
	DrawText(hdc, _scriptStr, _cnt, &rcScriptArea, DT_SINGLELINE | DT_VCENTER);
}

void dialogueManager::setScriptNScriptWindow(string script, image* scriptWindow, int r, int g, int b)
{
	_cnt = 0;
	
	wsprintf(_scriptStr, "%s", script.c_str());
	_scriptwindow = scriptWindow;

	_r = r;
	_g = g;
	_b = b;
}

void dialogueManager::setScript(string script, int r, int g, int b)
{
	_cnt = 0;

	wsprintf(_scriptStr, "%s", script.c_str());
	
	_r = r;
	_g = g;
	_b = b;
}

//float dialogueManager::getTime()
//{
//	//time_t timer;
//	//timer = time(NULL);//현재 시각을 초 단위로 읽는 함수
//	_time = TIMEMANAGER->getWorldTime();
//	return _time;
//}
void dialogueManager::setScriptWindow(image* scriptWindow)
{
	_scriptwindow = scriptWindow;
}