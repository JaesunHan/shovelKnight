#pragma once
#include "gameNode.h"
#include <vector>

class playerBase;

class stageManager : public gameNode
{
private:
	int _x, _y;
	int _loopX1;
	float _loopX2;
	int _mapNum;
	int _transverseTileNum;
	int _verticalTileNum;
	bool _mapLoaded;
	bool _transition;
	bool _nextMap;
	bool _previousMap;
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;
	vector<int> _vTileNum;
	vector<int>::iterator _viTileNum;
	playerBase* _player;
public:

	HRESULT init();
	void release();
	void update();
	void render();

	void loadData();
	void renderTiles();
	void transition();

	void setPlayerBaseMemoryAddressLink(playerBase* player) { _player = player; }



	stageManager();
	~stageManager();
};

