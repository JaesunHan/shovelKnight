#pragma once
#include "singletonBase.h"
enum LANGUAGE
{
	LANGUAGE_DEFAULT = 1,
	LANGUAGE_KOREAN,
	LANGUAGE_END
};
class dialogueManager : public singletonBase<dialogueManager>
{
	vector<string>			 _vString;
	vector<string>::iterator _vStringIter;

	int _dialogueTime;
	int _elapsedTime;

	float _startX, _startY;
	int* _length;

	int _currentLine;
	int _printLinesNum;
	LANGUAGE _language;

public:
	
	//=========================== Jaeusn 이 작성한 init - 우리 플젝에 맞게 고친거 ===========================
	HRESULT init(float dt, LANGUAGE lan);
	//====================================================================================================

	HRESULT init(float dt, int printLines, LANGUAGE lan);
	void release();
	void update();
	void render(HDC hdc);

	void loadingTextFile(const char* fileName);

	//							sour를				dest로 바꿔줌
	void replaceAll(const string sour, const string dest);

	inline int getCurrentLine() { return _currentLine; }
	inline void setCurrentLine(int line)
	{
		_currentLine = line;
		if (_currentLine > _vString.size() - (_printLinesNum - 1))
			_currentLine = _vString.size() - (_printLinesNum - 1);

		for (int i = 0; i < _printLinesNum; ++i)
			_length[i] = 0;
	}

	inline POINT getPoint() { return PointMake(_startX, _startY); }
	inline void setPoint(POINT pos)
	{
		_startX = pos.x;
		_startY = pos.y;
	}
	inline void setDialogueTime(float dt) { _dialogueTime = dt; }
	dialogueManager();
	~dialogueManager();
};

