#include "stdafx.h"
#include "collision.h"

namespace HEPTA_UTIL
{
	bool isCollisionReaction(const RECT& rcHold, RECT& rcMove)
	{
		//렉트끼리 충돌했을때 안에 생성되는 렉트 
		RECT rcInter;

		//충돌하지 않았다면 검출이 불필요하다!
		if (!IntersectRect(&rcInter, &rcHold, &rcMove)) return false;

		int interSectorW = rcInter.right - rcInter.left;
		int interSectorH = rcInter.bottom - rcInter.top;
		//수직으로 부딪혔다면~~~
		if (interSectorW > interSectorH)
		{
			//위에서 박았으면
			if (rcInter.top == rcHold.top)
			{
				OffsetRect(&rcMove, 0, -interSectorH);
			}
			else if (rcInter.bottom == rcHold.bottom)//아래에서 부딪혔다면
			{
				OffsetRect(&rcMove, 0, interSectorH);
			}
		}
		else
		{
			//오른쪽에서 가다 박으면
			if (rcInter.left == rcHold.left)
			{
				OffsetRect(&rcMove, -interSectorW, 0);
			}
			else if (rcInter.right == rcHold.right)
			{
				OffsetRect(&rcMove, interSectorW, 0);
			}
		}
	}

}