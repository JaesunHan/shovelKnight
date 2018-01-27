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
private:
	vector<string>			 _vString;
	vector<string>::iterator _vStringIter;

	int _dialogueTime;
	int _elapsedTime;

	string _scriptStr;
	image* _scriptwindow;

public:
	
	//		���� ����� �ð� ����
	HRESULT init(float dt);
	void release();
	void update();
	void render(HDC hdc);

	void setScriptNScriptWindow(string script, image* scriptWindow);

	//���ڸ� ����ϴ� �ð� ���� �����ϱ�
	inline void setDialogueTime(float dt) { _dialogueTime = dt; }

	//Ÿ�� ���ϴ� �Լ�
	time_t getTime();
	dialogueManager();
	~dialogueManager();
};
