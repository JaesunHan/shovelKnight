#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

//씬
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*>			 mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode* _currentScene;	//현재 씬
	static gameNode* _loadingScene;	//로딩 씬(안쓰일듯)
	static gameNode* _readyScene;	//대기 씬

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadingThreadID;			//혹시 몰라 넣어놓는 쓰레드용 ID

public:
	sceneManager();
	~sceneManager();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//씬 추가 함수
	gameNode* addScene(string sceneName, gameNode* scene);
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	//씬 변경
	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);

	//friend란 선언하면 클래스의 private까지 그냥 접근 가능케 한다
	//남발하면 안되는데, 구조상 왠지 1~2개정도는 해두면 좋을 것 같으면 해도됨
	friend DWORD CALLBACK loadingThread(LPVOID prc);

};

