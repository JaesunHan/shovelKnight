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
	spikeTrap,
	dirtPile,
	bubble,
	cliffTreeLeft,
	checkPoint
};

struct tagOBJECT
{
	image* img;
	RECT rc;
	RECT detectRC;
	int type;
	int x;
	int y;
	int frameX;
	int count;
	int durability;
	bool isPresent;
	bool isDestroyed;
};

class playerManager;
class stageManager;
class gamePlayUI;
class frontObjectManager : public gameNode
{
private:
	int _maxObj[10];
	int _mapNum;

	vector<tagOBJECT> _vObj[10];
	vector<tagOBJECT>::iterator _viObj;

	playerManager* _PM;
	stageManager* _SM;
	gamePlayUI* _GPUI;
public:
	frontObjectManager();
	~frontObjectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void loadData();
	void mapColoring();
	void objectInteraction();

	inline void setPlayerManagerMemoryAddressLink(playerManager* pm) { _PM = pm; }
	inline void setStageManagerMemoryAddressLink(stageManager* sm) { _SM = sm; }
	inline void setMapNumber(int number) { _mapNum = number; }

	inline void setGamePlayUIMemoryAddressLink(gamePlayUI* gpui) { _GPUI = gpui; }

	void addNsaveINTDataInINIFile(char* fileName, char subjectName[256], char title[256], int data);
	
};

