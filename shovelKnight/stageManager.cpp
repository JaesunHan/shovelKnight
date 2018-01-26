#include "stdafx.h"
#include "stageManager.h"
#include <vector>


stageManager::stageManager()
{
}


stageManager::~stageManager()
{

}


HRESULT stageManager::init()
{
	_x = 200;
	_y = 150;
	_mapLoaded = false;
	_mapNum = 1;
	_loopX1 = 0;
	_loopX2 = 100;
	return S_OK;
}

void stageManager::release()
{

}

void stageManager::update()	
{
	loadData();
	_loopX1 += 1;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 5;
		_loopX2 += 0.3f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 5;
		_loopX2 -= 0.3f;
	}

	//CAMERAMANAGER->setSingleFocus(_x, _y, 800);

}

void stageManager::render()	
{
	IMAGEMANAGER->findImage("layer1")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX1, 0);
	IMAGEMANAGER->findImage("layer2")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX2, 0);
	CAMERAMANAGER->renderMap(getMemDC(), IMAGEMANAGER->findImage("bgMap"));
	renderTiles();
	//TTTextOut(getMemDC(), _ptMouse.x, _ptMouse.y - 40, "¸¶¿ì½ºX", CAMERAMANAGER->getMousePointX(_ptMouse.x) / 16, false);
	//TTTextOut(getMemDC(), _ptMouse.x, _ptMouse.y - 20, "¸¶¿ì½ºY", CAMERAMANAGER->getMousePointY(_ptMouse.y) / 16, false);
	//CAMERAMANAGER->renderTile(getMemDC(), IMAGEMANAGER->findImage("tile1"), 0, 13, 10, 14, 16);
}

void stageManager::loadData()
{
	if (_mapLoaded == false)
	{
		TCHAR key[255];
		TCHAR directory[255];
		char mapName[128];
		wsprintf(mapName, "map00%d", _mapNum);
		char iniDir[128];
		wsprintf(iniDir, ".\\map00%d.ini", _mapNum);
		char txtDir[128];
		wsprintf(txtDir, "map00%d.txt", _mapNum);
		int maxlayer = INIDATA->loadDataInterger(mapName, "imageTotal", "maxNum");
		int maxTile = INIDATA->loadDataInterger(mapName, "tileTotal", "maxNum");

		for (int i = 0; i < maxlayer; ++i)
		{
			char bgImage[128];
			wsprintf(bgImage, "bgImage%d", i + 1);
			GetPrivateProfileString(_T(bgImage), _T("key"), NULL, key, 255, _T(iniDir));
			GetPrivateProfileString(_T(bgImage), _T("directory"), NULL, directory, 255, _T(iniDir));
			if (IMAGEMANAGER->findImage(key)) IMAGEMANAGER->deleteImage(key);
			IMAGEMANAGER->addImage(key, directory,
				INIDATA->loadDataInterger(mapName, bgImage, "width"),
				INIDATA->loadDataInterger(mapName, bgImage, "height"),
				true, RGB(255, 0, 255), false);
		}

		char mapImage[128];
		wsprintf(mapImage, "mapImage");
		GetPrivateProfileString(_T(mapImage), _T("key"), NULL, key, 255, _T(iniDir));
		GetPrivateProfileString(_T(mapImage), _T("directory"), NULL, directory, 255, _T(iniDir));
		_transverseTileNum = INIDATA->loadDataInterger(mapName, mapImage, "transverseNum");
		_verticalTileNum = INIDATA->loadDataInterger(mapName, mapImage, "verticalNum");
		if (IMAGEMANAGER->findImage(key)) IMAGEMANAGER->deleteImage(key);
		IMAGEMANAGER->addImage(key, directory,
			INIDATA->loadDataInterger(mapName, mapImage, "width"),
			INIDATA->loadDataInterger(mapName, mapImage, "height"),
			true, RGB(255, 0, 255), false);

		for (int i = 0; i < maxTile; ++i)
		{
			char tile[128];
			wsprintf(tile, "tile%d", i + 1);
			GetPrivateProfileString(_T(tile), _T("key"), NULL, key, 255, _T(iniDir));
			GetPrivateProfileString(_T(tile), _T("directory"), NULL, directory, 255, _T(iniDir));
			if (IMAGEMANAGER->findImage(key)) IMAGEMANAGER->deleteImage(key);
			IMAGEMANAGER->addImage(key, directory,
				INIDATA->loadDataInterger(mapName, tile, "width"),
				INIDATA->loadDataInterger(mapName, tile, "height"),
				true, RGB(255, 0, 255), false);
		}

		arrElements vTemp = TXTDATA->txtLoad(txtDir);
		for (int i = 0; i < vTemp.size(); ++i)
		{
			_vTileNum.push_back(atoi(vTemp[i].c_str()));
		}

		_mapLoaded = true;
	}
}

void stageManager::renderTiles()
{
	for (int i = 0; i < _transverseTileNum; ++i)						//¸Ê °¡·Î Å¸ÀÏ °¹¼ö
	{
		for (int j = 0; j < _verticalTileNum; ++j)						//¸Ê ¼¼·Î Å¸ÀÏ °¹¼ö
		{
			if (_vTileNum[(i * _verticalTileNum) + j] == 0) continue;
			if ((_vTileNum[(i * _verticalTileNum) + j] / 10000) == 1)
			{
				CAMERAMANAGER->renderTile(getMemDC(), IMAGEMANAGER->findImage("tile1"), i, j,
					(_vTileNum[(i * _verticalTileNum) + j] / 100) % 100,
					_vTileNum[(i * _verticalTileNum) + j] % 100, 16);
			}
		}
	}
}