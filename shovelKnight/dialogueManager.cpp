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

	//일정 시간 간격으로 
	if (getTime() % _dialogueTime == 0)
	{
		_cnt++;
	}
}
void dialogueManager::render(HDC hdc)
{
	SetTextColor(hdc, RGB(_r, _g, _b));
	RECT rcScriptArea = { _scriptwindow->getX(), _scriptwindow->getY(), _scriptwindow->getWidth(), _scriptwindow->getHeight() };
	DrawText(hdc, _scriptStr.c_str(), _cnt, &rcScriptArea, DT_SINGLELINE | DT_VCENTER);
}

void dialogueManager::setScriptNScriptWindow(string script, image* scriptWindow, int r, int g, int b)
{
	_cnt = 0;
	_scriptStr = script;
	_scriptwindow = scriptWindow;

	_r = r;
	_g = g;
	_b = b;
}

time_t dialogueManager::getTime()
{
	time_t timer;
	timer = time(NULL);//현재 시각을 초 단위로 읽는 함수

	return timer;
}