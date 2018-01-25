#pragma once
#include "gameNode.h"
#include <vector>

class stageManager : public gameNode
{
private:
	int _x, _y;
	int _loopX1;
	float _loopX2;
	int _mapNum;
	bool _mapLoaded;
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;
	vector<int> _vTileNum;
	vector<int>::iterator _viTileNum;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void loadData();

	stageManager();
	~stageManager();
};

