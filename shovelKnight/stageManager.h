#pragma once
#include "gameNode.h"
#include <vector>

class playerManager;
class StoreManager;
class frontObjectManager;

struct tagMAPTRANSITION
{
	RECT rc;
	int mapNum;
	int direction;
};

class stageManager : public gameNode
{
private:
	int _x, _y;
	int _cameraX, _cameraY;
	int _loopX1;
	float _loopX2;
	int _mapNum;
	int _transverseTileNum = 0;
	int _verticalTileNum = 0;
	int _maxFrameImage = 0;
	int _transitionNum = 0;
	int _maxLayer = 0;
	int _currentMapWidth = 0;
	int _currentMapHeight = 0;
	int _nextMapWidth = 0;
	int _nextMapHeight = 0;
	int _transitionCounter = 0;
	int _transitionMapTransverseTileNum = 0;
	bool _mapLoaded = false;
	bool _transition = false;
	bool _nextMap;
	bool _previousMap;
	bool _warpTransition = false;
	image* _frameImage;
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;
	vector<int> _vTileNum;
	vector<int>::iterator _viTileNum;
	vector<int> _vTransitionTileNum;
	vector<int>::iterator _viTransitionTileNum;
	tagMAPTRANSITION _mapTransition[4];
	playerManager* _PM;
	StoreManager* _storeM;
	frontObjectManager* _FOM;
public:

	HRESULT init();
	void release();
	void update();
	void render();

	void loadData();
	void renderTiles();
	void transition();
	void renderTransitionTiles();

	inline void setPlayerManagerMemoryAddressLink(playerManager* pm) { _PM = pm; }
	inline void setStoreManagerMemoryAddressLink(StoreManager* sm) { _storeM = sm; }
	inline void setFrontObjectManagerMemoryAddressLink(frontObjectManager* object) { _FOM = object; }
	inline void setLayer2LoopX(float loopx) { _loopX2 += loopx; }


	stageManager();
	~stageManager();
};

