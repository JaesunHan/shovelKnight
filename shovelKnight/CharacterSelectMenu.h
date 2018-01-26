#pragma once
class CharacterSelectMenu
{
public:

	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);
	void draw(HDC hdc);

	CharacterSelectMenu();
	~CharacterSelectMenu();
};

