#include "stdafx.h"
#include "playGround.h"




void playGround::addSound()
{
	SOUNDMANAGER->addSound("GamePlayBGM", "./sound/ost/Shovel Knight Soundtrack - 04 - Strike the Earth! (Plains of Passage).mp3", true, true);
	SOUNDMANAGER->addSound("BardKnightChange1", "./sound/ost/Shovel Knight Soundtrack - 05 - The Rival (Black Knight - First Battle).mp3", true, true);
	SOUNDMANAGER->addSound("BardKnightChange2", "./sound/ost/Shovel Knight Soundtrack - 06 - For Shovelry! (Boss Victory).mp3", true, true);
	SOUNDMANAGER->addSound("BardKnightChange3", "./sound/ost/Shovel Knight Soundtrack - 17 - The Local Happenstance (Village Basement).mp3", true, true);

	//==========================이펙트 사운드 선언==============================================/

	//========흑기사 관련사운드=========//
	SOUNDMANAGER->addSound("흑기사공중삽공격", "./sound/EFFECTSOUND/blackKnightAirAttackSound.mp3", false, false);
	SOUNDMANAGER->addSound("흑기사대사", "./sound/EFFECTSOUND/blackKnightDialogSound.mp3", false, false);
	SOUNDMANAGER->addSound("흑기사장풍", "./sound/EFFECTSOUND/blackKnightJangPung.mp3", false, false);
	SOUNDMANAGER->addSound("흑기사웃음", "./sound/EFFECTSOUND/blackKnightJangPung.mp3", false, false);
	SOUNDMANAGER->addSound("삽기사가흑기사이긴후", "./sound/EFFECTSOUND/defeatSound.mp3", false, false);
	SOUNDMANAGER->addSound("장풍반사", "./sound/EFFECTSOUND/reflectJangPung.mp3", false, false);
	SOUNDMANAGER->addSound("흑기사도망텨텨텨", "./sound/EFFECTSOUND/runawaySound.mp3", false, false);
	SOUNDMANAGER->addSound("흑기사등장피차는소리", "./sound/EFFECTSOUND/setBlackKnightHealthSound.mp3", false, false);
	SOUNDMANAGER->addSound("삽기사대화", "./sound/EFFECTSOUND/shovelKnightDialogSound.mp3", false, false);

	//========에너미 관련 사운드========//

	SOUNDMANAGER->addSound("용거품뿜뿜", "./sound/EFFECTSOUND/dragonBubbleShootSound.mp3", false, false);
	SOUNDMANAGER->addSound("용이동", "./sound/EFFECTSOUND/dragonMove.mp3", false, false);
	SOUNDMANAGER->addSound("용피격시", "./sound/EFFECTSOUND/dragonUnderAttacked.mp3", false, false);
	SOUNDMANAGER->addSound("용이떨군보석먹을때", "./sound/EFFECTSOUND/DropJewelEatSound.mp3", false, false);
	SOUNDMANAGER->addSound("방울터지는소리", "./sound/EFFECTSOUND/blackKnightJangPung.mp3", false, false);
	SOUNDMANAGER->addSound("몬스터피격시", "./sound/EFFECTSOUND/monsterAttackedSound.mp3", false, false);
	SOUNDMANAGER->addSound("몬스터폭발", "./sound/EFFECTSOUND/monsterExplosionSound.mp3", false, false);
	SOUNDMANAGER->addSound("바닥해골", "./sound/EFFECTSOUND/skeletonThrowSound.mp3", false, false);
	SOUNDMANAGER->addSound("슬라임점프", "./sound/EFFECTSOUND/slimeJumpSound.mp3", false, false);

	//=========삽기사 관련 사운드===========//
	SOUNDMANAGER->addSound("체력풀찰때", "./sound/EFFECTSOUND/fullHeartSound.mp3", false, false);
	SOUNDMANAGER->addSound("삽기사죽음", "./sound/EFFECTSOUND/DieSound.mp3", false, false);
	SOUNDMANAGER->addSound("삽기사공중삽찍기", "./sound/EFFECTSOUND/ShovelAirAttackSound.mp3", false, false);
	SOUNDMANAGER->addSound("삽기사일반공격", "./sound/EFFECTSOUND/shovelAttSound.mp3", false, false);
	SOUNDMANAGER->addSound("삽기사보석무더기", "./sound/EFFECTSOUND/shovelingSound.mp3", false, false);
	SOUNDMANAGER->addSound("삽기사피격", "./sound/EFFECTSOUND/underAttack.mp3", false, false);
	SOUNDMANAGER->addSound("삽기사점프후착지까지", "./sound/EFFECTSOUND/jumpSound.mp3", false, false);
	SOUNDMANAGER->addSound("삽기사등장", "./sound/EFFECTSOUND/knightEnter.mp3", false, false);


	//=========인게임 이펙트사운드=========//
	SOUNDMANAGER->addSound("공중보석먹을때", "./sound/EFFECTSOUND/jewelEatSound.mp3", false, false);
	SOUNDMANAGER->addSound("몬스터드랍보석먹을때", "./sound/EFFECTSOUND/jewelMonsterDropSound.mp3", false, false);
	SOUNDMANAGER->addSound("보석여러개먹을때", "./sound/EFFECTSOUND/jewelsSound.mp3", false, false);
	SOUNDMANAGER->addSound("죽고나서날개달린돈주머니등장", "./sound/EFFECTSOUND/DieAfterSound(되찾아라사운드).mp3", false, false);
	SOUNDMANAGER->addSound("폭발", "./sound/EFFECTSOUND/explosion.mp3", false, false);
	SOUNDMANAGER->addSound("세이브", "./sound/EFFECTSOUND/SaveSound.mp3", false, false);
	
	
	
	//==========옵션창 이펙트사운드===========//
	
	SOUNDMANAGER->addSound("이펙트사운드선택", "./sound/EFFECTSOUND/effectSoundSelect.mp3", false, false);
	SOUNDMANAGER->addSound("옵션닫기", "./sound/EFFECTSOUND/optionClose.mp3", false, false);
	SOUNDMANAGER->addSound("옵션움직이기", "./sound/EFFECTSOUND/optionMove.mp3", false, false);
	SOUNDMANAGER->addSound("옵션열기", "./sound/EFFECTSOUND/optionOpen.mp3", false, false);
	SOUNDMANAGER->addSound("옵션선택", "./sound/EFFECTSOUND/optionSelect.mp3", false, false);
	SOUNDMANAGER->addSound("타이틀셀렉트", "./sound/EFFECTSOUND/selectSound.mp3", false, false);
	SOUNDMANAGER->addSound("노란사각벽돌깨짐", "./sound/EFFECTSOUND/strawCrashSound.mp3", false, false);
	
	
	
	
}