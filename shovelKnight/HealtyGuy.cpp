#include "stdafx.h"
#include "HealtyGuy.h"


HealtyGuy::HealtyGuy()
{

	//ª˝º∫¿⁄ø° √ ±‚»≠
	//==========∞°∞› ºº∆√ ∫Øºˆ===========//
	_chicken = 1000;								//ØÉ»˘ ∞°∞›
	_drgonTail = 4500;								//øÎ≤ø∏Æ ∞°∞›


	//==========∆»∑»¥¬¡ˆ »Æ¿ŒøÎ ∫ØºˆµÈ==========//
	_stock = 0;										//∏Óπ¯¿Ã≥™ ªÛ¡°ø°º≠ ±∏∏≈«ﬂ¥¬¡ˆ »Æ¿Œ ∫Øºˆ
	_isSellChicken = false;							//ØÉ»˘ ∆»∑»¥¬¡ˆ
	_isSellDragonTail = false;						//øÎ≤ø∏Æ ∆»∑»¥¬¡ˆ
	

	//=========∏∂¥ı≈¨∑°Ω∫∑Œ∫Œ≈Õ ∞°¡Æø¬ ∫ØºˆµÈ √ ±‚»≠ ==============//

	_imgKeyString = "HealtyGuyIdle";				//¿ÃπÃ¡ˆ ∏≈¥œ¿˙ø° µÓ∑œ«“ ¿ÃπÃ¡ˆ ≈∞∞©
	_imgFileName = ". / npc / healthGuyStand.bmp";		//¿ÃπÃ¡ˆ ∆ƒ¿œ ¿Ã∏ß(∞Ê∑Œ ∆˜«‘)`

	_img = IMAGEMANAGER->addFrameImage(_imgKeyString, _imgFileName, 70, 47, 2, 1, true, RGB(255, 0, 255), false);											// NPC ¿ÃπÃ¡ˆ

	_img->setCenter(_x, _y);						//¿ÃπÃ¡ˆ ¡ﬂ¡°¡¬«•∑Œ ¡ﬂ¡°¡¬«• ¿‚¥¬¥Ÿ. 
	_width = _img->getFrameWidth();					//∞°∑Œ≈©±‚
	_height = _img->getFrameHeight();				//ºº∑Œ≈©±‚
	_rc = RectMakeCenter(_x, _y, _width, _height);	//ªÛ¡°NPC ∑∫∆Æ
	_npcType = HEALTYGUY;							//NPC≈∏¿‘

	_isCollision = false;							//«√∑π¿ÃæÓøÕ √Êµπ«ﬂ¥¬∞°? true : ±◊∑∏¥Ÿ, false : æ∆¥œ¥Ÿ

	int arrIDLE1[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("«ÔΩ∫∞°¿Ãæ∆¿ÃµÈ", "HealtyGuyIdle", arrIDLE1, 2, 5, true);


	_anim = KEYANIMANAGER->findAnimation("«ÔΩ∫∞°¿Ãæ∆¿ÃµÈ");		//NPC æ÷¥œ∏ﬁ¿Ãº«
}


HealtyGuy::~HealtyGuy()
{
}

void HealtyGuy::sellHpItem()
{
}
