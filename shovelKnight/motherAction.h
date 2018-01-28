#pragma once

class motherAction
{
public:
	motherAction();
	~motherAction();

	virtual void Move() = 0;
	virtual void Jump() = 0;
	virtual void SetPosition(string imageName, float x, float y) = 0;

};

