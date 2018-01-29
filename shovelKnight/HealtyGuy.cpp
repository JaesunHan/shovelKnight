#include "stdafx.h"
#include "HealtyGuy.h"


HealtyGuy::HealtyGuy()
{

	
}


HealtyGuy::~HealtyGuy()
{
}

HRESULT HealtyGuy::init()
{
	npcBase::init();
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
	_imgFileName = "./image/npc/healthGuyStand.bmp";		//ÀÌ¹ÌÁö ÆÄÀÏ ÀÌ¸§(°æ·Î Æ÷ÇÔ)`

	//NPC ÀÌ¹ÌÁö
	_img = IMAGEMANAGER->addFrameImage(_imgKeyString, _imgFileName, 70, 47, 2, 1, true, RGB(255, 0, 255), false);											// NPC ÀÌ¹ÌÁö
	IMAGEMANAGER->addFrameImage("HealtyGuyGood", "./image/npc/healthGuyGood.bmp", 168, 67, 4, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("HealtyGuyCook", "./image/npc/healthGuyBackCook.bmp", 897, 43, 23, 1, true, RGB(255, 0, 255), false);



	_x = 220/2;
	_y = 280/2;


	_img->setCenter(_x, _y);						//ÀÌ¹ÌÁö ÁßÁ¡ÁÂÇ¥·Î ÁßÁ¡ÁÂÇ¥ Àâ´Â´Ù. 
	_width = _img->getFrameWidth();					//°¡·ÎÅ©±â
	_height = _img->getFrameHeight();				//¼¼·ÎÅ©±â
	_rc = RectMakeCenter(_x, _y, _width, _height);	//»óÁ¡NPC ·ºÆ®
	_npcType = HEALTYGUY;							//NPCÅ¸ÀÔ



	_isCollisionNpc = false;							//ÇÃ·¹ÀÌ¾î¿Í Ãæµ¹Çß´Â°¡? true : ±×·¸´Ù, false : ¾Æ´Ï´Ù
	_isAppear = true;									//±âº»»óÅÂ·Î ¸Ê¿¡¼­ µîÀåÇÏÁö ¾Ê´Â´Ù.
	_textOut = false;

	int arrIDLE1[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("Çï½º°¡ÀÌ¾ÆÀÌµé", "HealtyGuyIdle", arrIDLE1, 2, 2, true);
	KEYANIMANAGER->start("Çï½º°¡ÀÌ¾ÆÀÌµé");

	_anim = KEYANIMANAGER->findAnimation("Çï½º°¡ÀÌ¾ÆÀÌµé");		//NPC ¾Ö´Ï¸ÞÀÌ¼Ç

	return S_OK;
}

void HealtyGuy::sellHpItem()
{
}

void HealtyGuy::render()
{
	if (_isAppear == true)
	{
		draw();

		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			Rectangle(getMemDC(), CAMERAMANAGER->getX(_rc.left),
				CAMERAMANAGER->getY(_rc.top),
				CAMERAMANAGER->getX(_rc.right),
				CAMERAMANAGER->getY(_rc.bottom));
		}
	}
	if (_textOut)
	{
		TTTextOut(500, 300, "ÇÃ·¹ÀÌ¾îµ·", _money);
		TTTextOut(500, 200, "ÇÃ·¹ÀÌ¾îÃÖ´ëÃ¼·Â",_setMaxHp);
	}
}

void HealtyGuy::draw()
{
	//_img->aniRender(getMemDC(), _rc.left, _rc.top, _anim);
	CAMERAMANAGER->aniRenderObject(getMemDC(), _img, _anim, _rc.left, _rc.top);
}

void HealtyGuy::update()
{
	npcBase::update();
}

void HealtyGuy::isCollision(bool collision)
{
	if (_isAppear)
	{
		if (collision)
		{
			//ÅØ½ºÆ® ¾Æ¿ôÀ¸·Î "³Ê ÀÌ°Å »ì·¡? Yes or No(bool°ª<-º¯¼ö ÇÏ³ª Ãß°¡ÇØ¾ßÇÔ 1.25)
			//¾Æ·¡´Â Yes ¼±ÅÃÇßÀ»¶§ÀÇ ÇÔ¼ö
			char* str1 = "Welcome, Welcome My friend";
			char* str2 = "you wanna buy some weed?:P";
			char* str3 = "if u OK press 'O', or not press 'P'";
			char* str4 = "get the fuck off!!!!";

			////init
			//int stats = 0;
			//
			//char* str = str1;
			//if(strlen(str)==strlen(str1) && stats = 0) str = str2;
			////

			_textOut = true;
			TTTextOut(500, 300, "Çï½º°¡ÀÌ¿¡¼­ÇÃ·¹ÀÌ¾îµ·", _money);

			if (KEYMANAGER->isOnceKeyDown('O'))				//O´­·¶À»¶§
			{
				//TTTextOut(300, 300, "À¸¾ÓÃæµ¹", 0);
				if (!_stock)					//ÇÑ¹øµµ »óÁ¡¿¡¼­ ±¸¸Å¸¦ ÇÏÁö ¾Ê¾ÒÀ¸¸é(stock =0)
				{
					if (_money >= 1000)				//1000¿øº¸´Ù µ·ÀÌ ¸¹´Ù¸é
					{
						_minusMoney -= 1000;						//ÇÃ·¹ÀÌ¾î °ñµå¿¡¼­ 1000¿øÀ» °¨¼ÒÇÏ°í
						_setMaxHp += 2;
						_stock = 1;						//ÇÑ¹ø ±¸¸ÅÇßÀ¸´Ï±î stockÀ» 1·Î ¹ÝÈ¯ÇØÁØ´Ù.
					}
					if (_money < 1000)						//ÇÃ·¹ÀÌ¾î °ñµå°¡ 1000¿øº¸´Ù ÀÛ´Ù¸é
					{
						//str = str4;
					}


				}

				if (_stock == 1)							//ÇÑ¹øµµ »óÁ¡¿¡¼­ ±¸¸Å¸¦ ÇÏÁö ¾Ê¾ÒÀ¸¸é
				{
					if (_money >= 3000)						//3000¿øº¸´Ù µ·ÀÌ ¸¹´Ù¸é
					{

						_minusMoney -= 3000;				//ÇÃ·¹ÀÌ¾î °ñµå¿¡¼­ 1000¿øÀ» °¨¼ÒÇÏ°í
						_setMaxHp += 2;
						_stock = 2;							//ÇÑ¹ø ±¸¸ÅÇßÀ¸´Ï±î stockÀ» 1·Î ¹ÝÈ¯ÇØÁØ´Ù.
					}
					if (_money < 3000)						//ÇÃ·¹ÀÌ¾î °ñµå°¡ 1000¿øº¸´Ù ÀÛ´Ù¸é
					{
						//str = str4;
					}

				}
			}

			if (KEYMANAGER->isOnceKeyDown('P'))
			{

			}
			//NOÇßÀ»¶§´Â ÅØ½ºÆ® ¾Æ¿ôÀ¸·Î
			//"¾î ±×...±×·¡? ¾È³ç ¤³¤³ " ´ÙÀÌ¾ó·Î±× Ãâ·Â ¤³¤³
			//_isCollisionNpc == false;

		}
	}
}
