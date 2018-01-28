#include "stdafx.h"
#include "stageManager.h"
#include "playerManager.h"
#include <vector>


stageManager::stageManager()
{
}


stageManager::~stageManager()
{

}


HRESULT stageManager::init()
{
	_mapLoaded = false;
	_transition = false;
	_mapNum = 1;
	_loopX1 = 0;
	_loopX2 = 100;
	_cameraX = 200;
	_cameraY = 120;
	for (int j = 0; j < 4; ++j)
	{
		_mapTransition[j].rc.left = 0;
		_mapTransition[j].rc.top = 0;
		_mapTransition[j].rc.right = 0;
		_mapTransition[j].rc.bottom = 0;
	}
	return S_OK;
}

void stageManager::release()
{

}

void stageManager::update()	
{
	_loopX1 += 1;

	if (_transition == false)
	{
		for (int i = 0; i < 4; ++i)
		{
			RECT temp;
			if (IntersectRect(&temp, &_PM->getPlayerRc(), &_mapTransition[i].rc))
			{
				_transitionNum = i;
				if (_mapTransition[i].direction == 1)
				{
					_cameraX = 200;
					_cameraY = 120;
					_PM->setPlayerPause(true);
					_PM->setX(_PM->getX() - _currentMapWidth + 400);
				}
				if (_mapTransition[i].direction == 3)
				{
					_cameraX = 600;
					_cameraY = 120;
					_PM->setPlayerPause(true);
					_PM->setX(_PM->getX() + 400);
				}
				if (_mapTransition[i].direction == 0) _warpTransition = true;
				else _warpTransition = false;
				transition();
				_transition = true;
			}
		}
	}
	if (_warpTransition == false)
	{
		if (_transition == true)
		{
			CAMERAMANAGER->setSingleFocus(_cameraX, _cameraY, 800);
			if (_mapTransition[_transitionNum].direction == 1)
			{
				_cameraX += 5;
				_PM->setX(_PM->getX() + 0.5f);
				if (_cameraX >= 600)
				{
					//_cameraX = 200;
					_PM->setX(_PM->getX() - 400);
					_PM->setPlayerPause(false);
					_mapLoaded = false;
					_transition = false;
				}
			}
			if (_mapTransition[_transitionNum].direction == 3)
			{
				_cameraX -= 5;
				_PM->setX(_PM->getX() - 0.5f);
				if (_cameraX <= 200)
				{
					_PM->setX(_PM->getX() + _nextMapWidth - 400);
					_PM->setPlayerPause(false);
					_mapLoaded = false;
					_transition = false;
				}
			}
		}
	}
	if (_warpTransition == true)
	{
		_transition = false;
	}
	
	loadData();
}

void stageManager::render()	
{
	CAMERAMANAGER->renderMap(getMemDC(), IMAGEMANAGER->findImage("bgMap"));
	if (_maxFrameImage > 0) _frameImage->aniRender(getMemDC(), 0, 0, KEYANIMANAGER->findAnimation("frameBG"));
	if (_maxLayer > 0)
	{
		IMAGEMANAGER->findImage("layer1")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX1, 0);
		if (_maxLayer > 1) IMAGEMANAGER->findImage("layer2")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX2, 0);
	}
	if (_transition == false) renderTiles();
	else if (_transition == true)
	{
		renderTransitionTiles();
	}
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
		_maxLayer = INIDATA->loadDataInterger(mapName, "imageTotal", "maxNum");
		int maxTile = INIDATA->loadDataInterger(mapName, "tileTotal", "maxNum");
		int maxTransition = INIDATA->loadDataInterger(mapName, "transitionTotal", "maxNum");
		_maxFrameImage = INIDATA->loadDataInterger(mapName, "frameIamgeTotal", "maxNum");

		if (_maxLayer > 0)
		{
			for (int i = 0; i < _maxLayer; ++i)
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
		}

		char mapImage[128];
		wsprintf(mapImage, "mapImage");
		GetPrivateProfileString(_T(mapImage), _T("key"), NULL, key, 255, _T(iniDir));
		GetPrivateProfileString(_T(mapImage), _T("directory"), NULL, directory, 255, _T(iniDir));
		_transverseTileNum = INIDATA->loadDataInterger(mapName, mapImage, "transverseNum");
		_verticalTileNum = INIDATA->loadDataInterger(mapName, mapImage, "verticalNum");
		_currentMapWidth = INIDATA->loadDataInterger(mapName, mapImage, "width");
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

		for (int i = 0; i < _maxFrameImage; ++i)
		{
			KEYANIMANAGER->deleteOne("frameBG");
			char frameImage[128];
			wsprintf(frameImage, "frameImage%d", i + 1);
			GetPrivateProfileString(_T(frameImage), _T("key"), NULL, key, 255, _T(iniDir));
			GetPrivateProfileString(_T(frameImage), _T("directory"), NULL, directory, 255, _T(iniDir));
			if (IMAGEMANAGER->findImage(key)) IMAGEMANAGER->deleteImage(key);

			_frameImage = IMAGEMANAGER->addFrameImage("frameImage1", ".\\image\\stage\\shopFrameImageMiddle.bmp", 3200, 480, 4, 1, true, RGB(255, 0, 255), false);
			int arr[] = { 0, 1, 2, 3 };
			KEYANIMANAGER->addArrayFrameAnimation("frameBG", "frameImage1", arr, 4, 5, true);
			KEYANIMANAGER->start("frameBG");
		}

		for (int j = 0; j < 4; ++j)
		{
			_mapTransition[j].rc.left = 0;
			_mapTransition[j].rc.top = 0;
			_mapTransition[j].rc.right = 0;
			_mapTransition[j].rc.bottom = 0;
		}
		for (int i = 0; i < maxTransition; ++i)
		{
			char transit[128];
			wsprintf(transit, "transition%d", i + 1);
			_mapTransition[i].rc.left = INIDATA->loadDataInterger(mapName, transit, "left");
			_mapTransition[i].rc.top = INIDATA->loadDataInterger(mapName, transit, "top");
			_mapTransition[i].rc.right = INIDATA->loadDataInterger(mapName, transit, "right");
			_mapTransition[i].rc.bottom = INIDATA->loadDataInterger(mapName, transit, "bottom");
			_mapTransition[i].mapNum = INIDATA->loadDataInterger(mapName, transit, "mapNum");
			_mapTransition[i].direction = INIDATA->loadDataInterger(mapName, transit, "direction");
			_x = INIDATA->loadDataInterger(mapName, transit, "playerX");
			_y = INIDATA->loadDataInterger(mapName, transit, "playerY");
		}

		_vTileNum.clear();
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

void stageManager::transition()
{
	if (_mapTransition[_transitionNum].direction == 0)
	{
		_mapNum = _mapTransition[_transitionNum].mapNum;
		_mapLoaded = false;
		_PM->setX(_x);
		_PM->setY(_y);
	}
	else// if (_transition == true)
	{
		_mapNum = _mapTransition[_transitionNum].mapNum;
		TCHAR key[255];
		TCHAR directory[255];
		char mapName[128];
		wsprintf(mapName, "map00%d", _mapTransition[_transitionNum].mapNum);
		char iniDir[128];
		wsprintf(iniDir, ".\\map00%d.ini", _mapTransition[_transitionNum].mapNum);
		char txtDir[128];
		wsprintf(txtDir, "map00%d.txt", _mapTransition[_transitionNum].mapNum);
		int maxLayer = INIDATA->loadDataInterger(mapName, "imageTotal", "maxNum");
		int maxTile = INIDATA->loadDataInterger(mapName, "tileTotal", "maxNum");
		_maxFrameImage = INIDATA->loadDataInterger(mapName, "frameIamgeTotal", "maxNum");
		_nextMapWidth = INIDATA->loadDataInterger(mapName, "mapImage", "width");

		for (int i = 0; i < maxLayer; ++i)
		{
			char bgImage[128];
			wsprintf(bgImage, "bgImage%d", i + 1);
			char tempLayer[128];
			wsprintf(tempLayer, "tempLayer%d", i + 1);
			GetPrivateProfileString(_T(bgImage), _T("directory"), NULL, directory, 255, _T(iniDir));
			if (IMAGEMANAGER->findImage(tempLayer)) IMAGEMANAGER->deleteImage(tempLayer);
			IMAGEMANAGER->addImage(tempLayer, directory,
				INIDATA->loadDataInterger(mapName, bgImage, "width"),
				INIDATA->loadDataInterger(mapName, bgImage, "height"),
				true, RGB(255, 0, 255), false);
		}

		IMAGEMANAGER->deleteImage("bgMap");
		IMAGEMANAGER->addImage("bgMap", ".\\image\\stage\\transitionMap2.bmp", 800, 240, true, RGB(255, 0, 255), false);

		for (int i = 0; i < maxTile; ++i)
		{
			char tile[128];
			wsprintf(tile, "tile%d", i + 1);
			char tempTile[128];
			wsprintf(tempTile, "tempTile%d", i + 1);
			GetPrivateProfileString(_T(tile), _T("directory"), NULL, directory, 255, _T(iniDir));
			if (IMAGEMANAGER->findImage(tempTile)) IMAGEMANAGER->deleteImage(tempTile);
			IMAGEMANAGER->addImage(tempTile, directory,
				INIDATA->loadDataInterger(mapName, tile, "width"),
				INIDATA->loadDataInterger(mapName, tile, "height"),
				true, RGB(255, 0, 255), false);
		}

		for (int i = 0; i < _maxFrameImage; ++i)
		{
			KEYANIMANAGER->deleteOne("frameBG");
			char frameImage[128];
			wsprintf(frameImage, "frameImage%d", i + 1);
			GetPrivateProfileString(_T(frameImage), _T("key"), NULL, key, 255, _T(iniDir));
			GetPrivateProfileString(_T(frameImage), _T("directory"), NULL, directory, 255, _T(iniDir));
			if (IMAGEMANAGER->findImage(key)) IMAGEMANAGER->deleteImage(key);

			_frameImage = IMAGEMANAGER->addFrameImage("frameImage1", ".\\image\\stage\\shopFrameImageMiddle.bmp", 3200, 480, 4, 1, true, RGB(255, 0, 255), false);
			int arr[] = { 0, 1, 2, 3 };
			KEYANIMANAGER->addArrayFrameAnimation("frameBG", "frameImage1", arr, 4, 5, true);
			KEYANIMANAGER->start("frameBG");
		}
		
		_vTransitionTileNum.clear();
		arrElements vTemp = TXTDATA->txtLoad(txtDir);
		for (int i = 0; i < vTemp.size(); ++i)
		{
			_vTransitionTileNum.push_back(atoi(vTemp[i].c_str()));
		}
	}
}

void stageManager::renderTransitionTiles()
{
	if (_mapTransition[_transitionNum].direction == 1)
	{
		for (int i = _transverseTileNum - 25; i < _transverseTileNum; ++i)
		{
			for (int j = 0; j < _verticalTileNum; ++j)
			{
				if (_vTileNum[(i * _verticalTileNum) + j] == 0) continue;
				if ((_vTileNum[(i * _verticalTileNum) + j] / 10000) == 1)
				{
					CAMERAMANAGER->renderTile(getMemDC(), IMAGEMANAGER->findImage("tile1"), i - (_transverseTileNum - 25), j,
						(_vTileNum[(i * _verticalTileNum) + j] / 100) % 100,
						_vTileNum[(i * _verticalTileNum) + j] % 100, 16);
				}
			}
		}
		for (int i = 0; i < 25; ++i)
		{
			for (int j = 0; j < 15; ++j)
			{
				if (_vTransitionTileNum[(i * _verticalTileNum) + j] == 0) continue;
				if ((_vTransitionTileNum[(i * _verticalTileNum) + j] / 10000) == 1)
				{
					CAMERAMANAGER->renderTile(getMemDC(), IMAGEMANAGER->findImage("tempTile1"), i + 25, j,
						(_vTileNum[(i * _verticalTileNum) + j] / 100) % 100,
						_vTileNum[(i * _verticalTileNum) + j] % 100, 16);
				}
			}
		}
	}
	
}