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
	if (_scriptStr == "")
	{
		return;
	}
	if (getTime() % _dialogueTime)
	{

	}
}
void dialogueManager::render(HDC hdc)
{

}

void dialogueManager::setScriptNScriptWindow(string script, image* scriptWindow)

{

}

time_t dialogueManager::getTime()
{
	time_t timer;
	timer = time(NULL);//현재 시각을 초 단위로 읽는 함수

	return timer;
}