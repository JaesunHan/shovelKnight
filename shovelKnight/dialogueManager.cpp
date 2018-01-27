#include "stdafx.h"
#include "dialogueManager.h"


dialogueManager::dialogueManager()
{
}


dialogueManager::~dialogueManager()
{
}

HRESULT dialogueManager::init(float dt, LANGUAGE lan)
{
	_dialogueTime = dt;
	_elapsedTime = 0;
	_language = lan;
	return S_OK;
}
HRESULT dialogueManager::init(float dt, int printLines, LANGUAGE lan)
{
	_dialogueTime = dt;
	_elapsedTime = 0;
	_printLinesNum = printLines;
	_language = lan;

	_length = new int[_printLinesNum];

	return S_OK;
}

void dialogueManager::release()
{
	SAFE_DELETE_ARRAY(_length);
}

void dialogueManager::update()
{
	_elapsedTime++;
	if (_elapsedTime % _dialogueTime == 0)
	{
		for (int i = 0; i < _printLinesNum; ++i)
		{
			if (i >= _vString.size()) break;
			if (_currentLine + i >= _vString.size()) break;
			if (_length[i] >= strlen(_vString[_currentLine + i].c_str())) continue;

			_length[i] += _language;
			if (_length[i] > strlen(_vString[_currentLine + i].c_str()))
				_length[i] = strlen(_vString[_currentLine + i].c_str());

			break;
		}
	}
}

void dialogueManager::render(HDC hdc)
{
	for (int i = 0; i < _printLinesNum; ++i)
	{
		if (i >= _vString.size()) break;
		if (_currentLine + i >= _vString.size()) break;

		TextOut(hdc, _startX, _startY + 20 * i, _vString[_currentLine + i].c_str(), _length[i]);
	}
}

void dialogueManager::loadingTextFile(const char* fileName)
{
	// 일단 벡터 비우고
	_vString.clear();

	// 맨 처음 대사부터 뜨게 하고
	_currentLine = 0;

	for (int i = 0; i < _printLinesNum; ++i)
		_length[i] = 0;

	// Text파일을 읽어와서 벡터에 넣어줌
	_vString = TXTDATA->txtLoad(fileName);
}

//								  	    from을	    		to로 바꿔줌
void dialogueManager::replaceAll(const string from, const string to)
{
	for (int i = 0; i < _vString.size(); ++i)
	{
		size_t start_pos = 0; //string처음부터 검사

		while ((start_pos = _vString[i].find(from, start_pos)) != std::string::npos)  //from을 찾을 수 없을 때까지
		{
			_vString[i].replace(start_pos, from.length(), to);
			start_pos += to.length(); // 중복검사를 피하고 from.length() > to.length()인 경우를 위해서
		}
	}
}