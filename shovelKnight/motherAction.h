#pragma once

class motherAction
{
public:
	motherAction();
	~motherAction();

	virtual void Move() = 0;
	virtual void Jump() = 0;
	virtual void SetPosion(string imageName, float x, float y) = 0;

};

