#include "stdafx.h"
#include "playGround.h"




void playGround::addSound()
{
	SOUNDMANAGER->addSound("GamePlayBGM", "./sound/ost/Shovel Knight Soundtrack - 04 - Strike the Earth! (Plains of Passage).mp3", true, true);
	SOUNDMANAGER->addSound("BardKnightChange1", "./sound/ost/Shovel Knight Soundtrack - 05 - The Rival (Black Knight - First Battle).mp3", true, true);
	SOUNDMANAGER->addSound("BardKnightChange2", "./sound/ost/Shovel Knight Soundtrack - 06 - For Shovelry! (Boss Victory).mp3", true, true);
	SOUNDMANAGER->addSound("BardKnightChange3", "./sound/ost/Shovel Knight Soundtrack - 17 - The Local Happenstance (Village Basement).mp3", true, true);
}