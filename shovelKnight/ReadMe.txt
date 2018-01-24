
asd라는 클래스의 구조의 작동방식을 설명하자면

asdBase에서 공통적인 변수를 추가시켜주고

예시로 asd1을 asdBase로 상속시켜주고, 개인적으로 넣고싶은 속성이 있다면 그런 것들을 넣어준다

그리고 asdManager에서 #include "asd1.h"를 추가시켜주고,
뭔가 생성을 시킨다면 벡터안에 담아주고 벡터를 전부 랜더하는 구조이다

요약하자면
공통적인 속성은 asdBase
개인적인 속성들은 asd1, asd2 등등
생성된 것들은 asdManager에서 벡터에 담아주고 백터를 전부 init, release, update, render해준다.

asd1에서 열심히 작업하다가 필요한 변수가 있다면 asdBase에 추가 해주면 된다.

asd1같은것은 임의로 정한거라 구조가 이해된다면 삭제시키고 원하는 이름으로 적으면 된다


//================================해야할 일====================================
MotherAction을 모든 Base에 연결시키기


//===============================만들다 만거===================================

																				enemyBase.h
#pragma once

class enemyBase
{
protected:
	int _hp;
	float _x;
	float _y;

public:
	enemyBase();
	~enemyBase();


	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void CreateMinion(float x, float y) = 0;
};

																				enemyBase.cpp
#include "stdafx.h"
#include "enemyBase.h"


enemyBase::enemyBase()
{
}


enemyBase::~enemyBase()
{
}

HRESULT enemyBase::init()
{
	return S_OK;
}

void enemyBase::release()
{
}

void enemyBase::update()
{
}

void enemyBase::render()
{
}

																				enemy1.h
#pragma once
#include "enemyBase.h"

class enemy1 : public enemyBase
{
public:
	enemy1();
	~enemy1();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void CreateMinion(float x, float y);
};

																				enemy1.cpp
#include "stdafx.h"
#include "enemy1.h"


enemy1::enemy1()
{
}


enemy1::~enemy1()
{
}

HRESULT enemy1::init()
{
	return S_OK;
}

void enemy1::release()
{
}

void enemy1::update()
{
}

void enemy1::render()
{
}

void enemy1::CreateMinion(float x, float y)
{
	_x = x;
	_y = y;
}

																				enemyManager.h
#pragma once
#include "enemy1.h"

#define MINIONMAX 2;

enum RETURN_ENEMY
{
	NONE,
	COLLISION_FIRE,
};

class enemyManager
{
private:
	typedef vector<enemyBase*> vEnemy;
	typedef vector<enemyBase*> viEnemy;

private:
	vEnemy _vEnemy;

	RETURN_ENEMY _return;

public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void createMinion(RETURN_ENEMY re);
};


																				enemyManager.cpp
#include "stdafx.h"
#include "enemyManager.h"


enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	_return = NONE;


	for (int i = 0; i < MINIONMAX; ++i)
	{
		enemyBase* em;
		switch (i)
		{
		case 0:
			em = new enemy1;
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		}
		em->init();
	}

	return S_OK;
}

void enemyManager::release()
{
	if(_vMinion.size())
	{
		_vMinion[0].release();
	}
}

void enemyManager::update()
{
	if(_vMinion.size())
	{
		_vMinion[0].release();
	}
}

void enemyManager::render()
{
}

void enemyManager::createMinion(RETURN_ENEMY re)
{
	enemyBase* em;
	switch (re)
	{
	case NONE:
		break;
	case COLLISION_FIRE:
		em = new enemy1;
		em->CreateMinion(10, 10);
		break;
	default:
		break;
	}
	_vEnemy.push_back(em);
}
