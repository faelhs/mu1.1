#include "StdAfx.h"
#include "protocol.h"

CHealthBar gHealthBar;

void CHealthBar::Info(LPOBJ lpObj)
{
	int tObjNum		= 0;
	LPOBJ lpTarget	= NULL;
	
	for(int i = 0;i < MAX_VIEWPORT;i++)
	{
		if(lpObj->VpPlayer[i].state)
		{
			tObjNum		= lpObj->VpPlayer2[i].number;
			lpTarget	= &gObj[tObjNum];

			if(tObjNum > 0)
			{
				if(lpTarget->Live && (lpTarget->Type == OBJ_MONSTER))
				{
					if((gObjCalDistance(lpObj,lpTarget) <= 10) && (gObjCheckAttackArea(lpObj->m_Index,lpTarget->m_Index) == false))
					{
						this->Send(lpObj->m_Index,lpTarget->m_Index);
					}
				}
			}
		}
	}
}

void CHealthBar::Send(int aIndex,int tIndex)
{
	if(gObj[aIndex].Type == OBJ_USER)
	{
		MSG_ANS_LIFEBAR_SEND pMsg = {0};
		pMsg.h.set((LPBYTE)&pMsg, 0xF3, 0x02, sizeof(MSG_ANS_LIFEBAR_SEND));

		pMsg.NumberH	= SET_NUMBERH(tIndex);
		pMsg.NumberL	= SET_NUMBERL(tIndex);

		pMsg.Life		= gObj[tIndex].Life;
		pMsg.MaxLife	= gObj[tIndex].MaxLife;
		pMsg.Class		= gObj[tIndex].Class;
		pMsg.Level		= gObj[tIndex].Level;

		DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
	}
}