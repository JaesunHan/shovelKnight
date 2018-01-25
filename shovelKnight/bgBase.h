#pragma once
class bgBase
{
public:
	bgBase();
	~bgBase();

	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

