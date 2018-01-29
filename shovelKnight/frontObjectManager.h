#pragma once
#include "gameNode.h"
#include <vector>

enum OBJECTTYPE
{
	grassLarge,
	grassSmall,
	dirtBlockLarge,
	dirtBlockSmall,
	platform,
	ladder,
	spikeTrap

};

struct tagOBJECT
{
	image* img;
	int type;
	int x;
	int y;
	bool isPresent;
};

class playerManager;
class stageManager;

class frontObjectManager : public gameNode
{
private:
	int _maxObj[10];
	int _mapNum;

	vector<tagOBJECT> _vObj[10];
	vector<tagOBJECT>::iterator _viObj;

	playerManager* _PM;
	stageManager* _SM;
public:
	frontObjectManager();
	~frontObjectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void loadData();

	inline void setPlayerManagerMemoryAddressLink(playerManager* pm) { _PM = pm; }
	inline void setStageManagerMemoryAddressLink(stageManager* sm) { _SM = sm; }
	inline void setMapNumber(int number) { _mapNum = number; }
};

