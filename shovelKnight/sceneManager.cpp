#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"


sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{

}


DWORD CALLBACK loadingThread(LPVOID prc)
{
	//바꿔줄 씬을 미리 초기화해 둔다
	sceneManager::_readyScene->init();

	//현재 씬으로 교체 해준다
	sceneManager::_currentScene = sceneManager::_readyScene;

	//로딩에 쓰인 씬을 해제해주고, 대기시켜놨던 씬도 해제
	sceneManager::_loadingScene->release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	//중요한건 아마 쓸일 없다는거 또르르르르...

	return 0;
}

//스태틱으로 선언 되어있으므로 초기화는 여기서
gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadingScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

HRESULT sceneManager::init(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;


	return S_OK;
}

void sceneManager::release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void sceneManager::update(void)	
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render(void)	
{
	if (_currentScene) _currentScene->render();
}


//씬 추가 함수
gameNode* sceneManager::addScene(string sceneName, gameNode* scene)
{
	//씬이 없다면 널값 반환
	if (!scene) return NULL;

	//씬에 키 값을 부여해서 map컨테이너에 담아준다
	_mSceneList.insert(make_pair(sceneName, scene));

	//반환
	return scene;
}

gameNode* sceneManager::addLoadingScene(string loadingSceneName, gameNode* scene)
{
	//역시 씬이 없다면 NULL값 반환
	if (!scene) return NULL;

	//로딩씬에 키값을 붙여서 맵컨테이너에 담아준다
	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

//씬 변경
HRESULT sceneManager::changeScene(string sceneName)
{
	//이터레이터에 찾고자하는 씬의 키 값을 대입
	mapSceneIter find = _mSceneList.find(sceneName);

	//이터레이터가 맵의 끝까지 갔다 == 찾고자하는게 없다 실패 반환
	if (find == _mSceneList.end()) return E_FAIL;

	//만약 바꾸려는 씬이 현재 씬이면 그냥 둔다
	if (find->second == _currentScene) return S_OK;

	//성공적으로 씬이 바뀐다면 init함수 실행 
	if (SUCCEEDED(find->second->init()))
	{
		//만약 현재씬에 다른 씬이 있다면 해제 해주고
		if (_currentScene) _currentScene->release();

		//바꾸려는 씬으로 체인지 한다
		_currentScene = find->second;

		//지금 씬 변환하는 이 구조는 여러분이 입맛에 따라 바꿔도 된다
		//디폴트로 만들어 놨지만 위에 구조의 단점이 딱 하나 있는데
		//스테이지1 -> 스테이지2로 씬이 바뀌었을때 스테이지1의 데이터를
		//넘기려고 할때 릴리즈가 먼저 호출이 되서 조금 신경을 써줘야한다

		//뭐 그렇다고.. ㅎ _ㅎ)

		return S_OK;
	}

	return E_FAIL;
}

HRESULT sceneManager::changeScene(string sceneName, string loadingSceneName)
{
	//이터레이터에 찾고자하는 씬의 키 값을 대입
	mapSceneIter find = _mSceneList.find(sceneName);


	if (find == _mSceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return S_OK;

	//로딩하려는 씬을 찾는다
	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	//예외처리 알죠?
	if (find == _mLoadingSceneList.end()) return changeScene(loadingSceneName);

	//성공적으로 씬이 바뀐다면 init함수 실행 
	if (SUCCEEDED(find->second->init()))
	{
		//만약 현재씬에 다른 씬이 있다면 해제 해주고
		if (_currentScene) _currentScene->release();

		//로딩씬을 찾아서 대입하고
		_loadingScene = findLoading->second;
		//바꾸려는 씬을 준비시켜둔다
		_readyScene = find->second;
		
		//로딩에 쓰인 쓰레드 꺼준다
		CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadingThreadID));
	
		return S_OK;
	}

	return E_FAIL;
}

