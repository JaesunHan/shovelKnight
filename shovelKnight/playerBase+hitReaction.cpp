#include "stdafx.h"
#include "playerBase.h"

void playerBase::hitReAction()
{
	//플레이어와 맵의 충돌을 확인해서 충돌 방향, 충돌대상을 설정한다
	//switch ()			
	//{										
	//case CT_NULL:							//충돌하지 않았을떄
	//	_cPlayerTarget = CP_NULL;			//플레이어는 충돌하지 않았다
	//	break;								//
	//case CT_TOP:							//플레이어의 탑과 그라운드의 바텀 충돌
	//	_cPlayerTarget = CP_GROUND;			//충돌대상은 그라운드
	//	_cLR = LR_NULL;						//충돌방향(좌우) 없음
	//	_cTB = TB_BOTTOM;					//충돌방향(상하) 대상의 아래쪽
	//	break;								//
	//case CT_BOTTOM:							//플레이어의 바텀과 그라운드의 탑 충돌
	//	_cPlayerTarget = CP_GROUND;			//충돌대상은 그라운드
	//	_cLR = LR_NULL;						//충돌방향(좌우) 없음
	//	_cTB = TB_TOP;						//충돌방향(상하) 대상의 위쪽
	//	break;								//
	//case CT_LEFT:							//플레이어의 왼쪽과 그라운드의 오른쪽 충돌
	//	_cPlayerTarget = CP_GROUND;			//충돌대상은 그라운드
	//	_cLR = LR_RIGHT;					//충돌방향(좌우) 대상의 오른쪽
	//	_cTB = TB_NULL;						//충돌방향(상하) 없음
	//	break;								//
	//case CT_RIGHT:							//플레이어의 오른쪽과 그라운드의 왼쪽 충돌
	//	_cPlayerTarget = CP_GROUND;			//충돌대상은 그라운드
	//	_cLR = LR_LEFT;						//충돌방향(좌우) 
	//	_cTB = TB_NULL;						//충돌방향(상하) 
	//	break;								//
	//case CT_LEFT_BOTTOM:					//플레이어의 왼쪽아래와 그라운드 충돌
	//	_cPlayerTarget = CP_GROUND;			//충돌대상은 그라운드
	//	_cLR = LR_RIGHT;					//충돌방향(좌우) 대상의 오른쪽
	//	_cTB = TB_TOP;						//충돌방향(상하) 
	//	break;								//
	//case CT_RIGHT_BOTTOM:					//플레이어의 오른쪽아래와 그라운드 충돌
	//	_cPlayerTarget = CP_GROUND;			//충돌대상은 그라운드
	//	_cLR = LR_LEFT;						//충돌방향(좌우) 
	//	_cTB = TB_BOTTOM;					//충돌방향(상하) 
	//	break;								//
	//}

	//설정한 대상, 방향에 따른 물리값을 수정한다

	

	switch (_cPlayerTarget)
	{
	case COLLISION_PLAYER_NULL:							//충돌한 대상이 없다
		break;
	case COLLISION_PLAYER_OBJECT:						//오브젝트와 충돌했을때(오브젝트와 캐릭터)
	break;
	case COLLISION_PLAYER_ENEMY:						//적과 충돌했을떄
		break;						
	case COLLISION_PLAYER_GROUND:						//땅과 충돌했을떄
		_state = PLAYERSTATE_ONLAND;
		_action = PLAYERACTION_IDLE;
		break;
	case COLLISION_PLAYER_SHOVEL_OBJ:					//
	break;						
	case COLLISION_PLAYER_SHOVEL_ENEMY:				//
	break;							
	}										
}											

