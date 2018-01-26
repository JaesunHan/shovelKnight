#pragma once
#include "gameNode.h"
#include <vector>

class playerManager;

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
	int _loopX1;
	float _loopX2;
	int _mapNum;
	int _transverseTileNum;
	int _verticalTileNum;
	int _maxFrameImage;
	int _transitionNum;
	bool _mapLoaded;
	bool _transition;
	bool _nextMap;
	bool _previousMap;
	image* _frameImage;
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;
	vector<int> _vTileNum;
	vector<int>::iterator _viTileNum;
	vector<int> _vTransitionTileNum;
	vector<int>::iterator _viTransitionTileNum;
	tagMAPTRANSITION _mapTransition[4];
	playerManager* _PM;
public:

	HRESULT init();
	void release();
	void update();
	void render();

	void loadData();
	void renderTiles();
	void transition();

	void setPlayerManagerMemoryAddressLink(playerManager* pm) { _PM = pm; }



	stageManager();
	~stageManager();
};

