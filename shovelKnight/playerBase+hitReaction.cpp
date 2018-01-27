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
	case CP_NULL:						//충돌한 대상이 없다
		_state = INAIR;					// 충돌한 대상이 없으면 공중에 있는거
		break;
	case CP_OBJECT:						//오브젝트와 충돌했을때(오브젝트와 캐릭터)
	{
		switch (_cLR)					//좌우 방향
		{
		case LR_LEFT:				//대상의 왼쪽에서 충돌했을떄
			_rtBlock = true;			//플레이어의 오른쪽은 막혔다(플레이어는 오른쪽으로 갈수없다)
			break;
		case LR_RIGHT:				//대상의 오른쪽에서 충돌했을떄
			_ltBlock = true;			//플레이어의 왼쪽은 막혔다
			break;
		}
		switch (_cTB)					//상하방향
		{
		case TB_TOP:				//대상의 위쪽에서 충돌했을떄
			_jumpPower = JUMPPOWER;		//점프파워는 복구시킨다
			_state = ONLAND;			//플레이어의 위치는 땅을밟고있다
			if (_action == PR_JUMP) PR_IDLE;		//플레이어가 점프하고있으면 기본상태로 돌린다
			break;
		case TB_BOTTOM:				//대상의 아래쪽에서 충돌했을떄
			_jumpPower = 0;				//점프파워를 0으로 해서 더이상 위로 올라가지 못하게한다.
			break;
		}
	}
	break;
	case CP_ENEMY:						//적과 충돌했을떄
										//
		break;								//
	case CP_GROUND:						//땅과 충돌했을떄
	{									//
		switch (_cLR)					//땅의 좌우
		{								//
		case LR_NULL:				//좌우가 뚫려있을경우
			_rtBlock = false;			//
			_ltBlock = false;			//
			break;						//
		case LR_LEFT:				//오른쪽이 막혀있을때
			_rtBlock = true;			//
			break;						//
		case LR_RIGHT:				//왼쪽이 막혀있을떄
			_ltBlock = true;			//
			break;						//
		}								//
		switch (_cTB)					//위아래 충돌
		{								//
		case TB_TOP:				//땅의 탑과 충돌했을떄
			_jumpPower = JUMPPOWER;		//점프파워를 복구시킨다
			_state = ONLAND;
			_y = probeY;
			if (_action == PR_JUMP) _action = PR_IDLE;
			break;						//
		case TB_BOTTOM:				//
			_jumpPower = 0;				//
			break;						//
		}								//
	}
	case CP_SHOVEL_OBJ:					//
	{									//
		switch (_cTB)					//
		{								//
		case TB_TOP:					//
			_jumpPower = JUMPPOWER / 2;	//
			break;						//
		}								//
	}									//
	break;							//
	case CP_SHOVEL_ENEMY:				//
	{									//
		switch (_cTB)					//
		{								//
		case TB_TOP:				//
			_jumpPower = JUMPPOWER / 2;	//
			break;						//
		}								//
		switch (_cLR)					//
		{								//
		case LR_LEFT:					//
			break;						//
		case LR_RIGHT:					//
			break;						//
		}								//
	}									//
	break;							//
									//
	}										//
}											//

