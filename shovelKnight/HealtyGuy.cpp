#include "stdafx.h"
#include "HealtyGuy.h"


HealtyGuy::HealtyGuy()
{

	//»ý¼ºÀÚ¿¡ ÃÊ±âÈ­
	//==========°¡°Ý ¼¼ÆÃ º¯¼ö===========//
	_chicken = 1000;								//¯ƒÈù °¡°Ý
	_drgonTail = 4500;								//¿ë²¿¸® °¡°Ý


	//==========ÆÈ·È´ÂÁö È®ÀÎ¿ë º¯¼öµé==========//
	_stock = 0;										//¸î¹øÀÌ³ª »óÁ¡¿¡¼­ ±¸¸ÅÇß´ÂÁö È®ÀÎ º¯¼ö
	_isSellChicken = false;							//¯ƒÈù ÆÈ·È´ÂÁö
	_isSellDragonTail = false;						//¿ë²¿¸® ÆÈ·È´ÂÁö
	

	//=========¸¶´õÅ¬·¡½º·ÎºÎÅÍ °¡Á®¿Â º¯¼öµé ÃÊ±âÈ­ ==============//

	_imgKeyString = "HealtyGuyIdle";				//ÀÌ¹ÌÁö ¸Å´ÏÀú¿¡ µî·ÏÇÒ ÀÌ¹ÌÁö Å°°©
	_imgFileName = ". / npc / healthGuyStand.bmp";		//ÀÌ¹ÌÁö ÆÄÀÏ ÀÌ¸§(°æ·Î Æ÷ÇÔ)`

	_img = IMAGEMANAGER->addFrameImage(_imgKeyString, _imgFileName, 70, 47, 2, 1, true, RGB(255, 0, 255), false);											// NPC ÀÌ¹ÌÁö

	_x = 220;
	_y = 280;


	_img->setCenter(_x, _y);						//ÀÌ¹ÌÁö ÁßÁ¡ÁÂÇ¥·Î ÁßÁ¡ÁÂÇ¥ Àâ´Â´Ù. 
	_width = _img->getFrameWidth();					//°¡·ÎÅ©±â
	_height = _img->getFrameHeight();				//¼¼·ÎÅ©±â
	_rc = RectMakeCenter(_x, _y, _width, _height);	//»óÁ¡NPC ·ºÆ®
	_npcType = HEALTYGUY;							//NPCÅ¸ÀÔ



	_isCollision = false;							//ÇÃ·¹ÀÌ¾î¿Í Ãæµ¹Çß´Â°¡? true : ±×·¸´Ù, false : ¾Æ´Ï´Ù
	_isAppear = false;								//±âº»»óÅÂ·Î ¸Ê¿¡¼­ µîÀåÇÏÁö ¾Ê´Â´Ù.

	int arrIDLE1[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("Çï½º°¡ÀÌ¾ÆÀÌµé", "HealtyGuyIdle", arrIDLE1, 2, 5, true);


	_anim = KEYANIMANAGER->findAnimation("Çï½º°¡ÀÌ¾ÆÀÌµé");		//NPC ¾Ö´Ï¸ÞÀÌ¼Ç
}


HealtyGuy::~HealtyGuy()
{
}

void HealtyGuy::sellHpItem()
{
}

void HealtyGuy::render()
{
	if (_isAppear)
	{
		draw();
	}
}

void HealtyGuy::draw()
{
	_img->aniRender(getMemDC(), _rc.left, _rc.top, _anim);
}
